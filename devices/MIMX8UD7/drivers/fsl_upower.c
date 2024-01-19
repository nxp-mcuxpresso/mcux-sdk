/*
 * Copyright 2020-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_upower.h"
#include "fsl_clock.h"

#ifdef FSL_RTOS_FREE_RTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.upower"
#endif

#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
#define POWERSYS_MUA_RTD_BASE (0x38029000u)
#else
#define POWERSYS_MUA_RTD_BASE (0x28029000u)
#endif

#define POWERSYS_MUA_RTD ((MU_Type *)(POWERSYS_MUA_RTD_BASE))

#define UPOWER_MU ((struct MU_tag *)(POWERSYS_MUA_RTD_BASE))

#define PMIC_CONFIG_TAG            0x706D6963 /* Magic number for uPower PMIC driver identify */
#define PMIC_CONFIG_REG_ARRAY_SIZE 8          /* PMIC register access block array size */

/*******************************************************************************
 * Variables
 ******************************************************************************/
static upwr_isr_callb s_muTxRxHandler;
static upwr_isr_callb s_muNmiHandler;

static volatile bool callbackStatus = false;

/* BUCK2 BUCK3 DVS0 output voltage from 0.60V to 2.1875 V in 12.5 mV steps */
static double buck2_buck3_output_voltage_array[BUCK_OUTPUT_TABLE_SIZE] = {0.0};
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* upower pmic register access block. */
struct pmic_reg_addr_data
{
    uint32_t reg;  /* the target configured register of PMIC IC */
    uint32_t data; /* the value of the target configured register */
};

/* upower pmic configuration. */
struct pmic_config_struct
{
    uint32_t cfg_tag;      /* cfg_tag = PMIC_CONFIG_TAG, used to judge if the config data are valid */
    uint32_t cfg_reg_size; /* how many registers shall be configured */
    struct pmic_reg_addr_data reg_addr_data_array[PMIC_CONFIG_REG_ARRAY_SIZE];
};

/*******************************************************************************
 * Code
 ******************************************************************************/
void uPower_IRQHandler(void)
{
    if ((POWERSYS_MUA_RTD->CSSR0 & MU_CSSR0_NMIC_MASK) != 0U)
    {
        /* Clear NMI */
        POWERSYS_MUA_RTD->CSSR0 = MU_CSSR0_NMIC_MASK;
        if (s_muNmiHandler != NULL)
        {
            s_muNmiHandler();
        }
        else
        {
        }
    }
    else
    {
        assert(s_muTxRxHandler);
        s_muTxRxHandler();
    }
}

static void UPOWER_DummyInstallISR(upwr_isr_callb txrx, upwr_isr_callb excp)
{
    s_muTxRxHandler = txrx;
    s_muNmiHandler  = excp;
}

static void UPOWER_LockMuInt(int lock)
{
    if (lock != 0)
    {
        NVIC_DisableIRQ(uPower_IRQn);
    }
    else
    {
        NVIC_EnableIRQ(uPower_IRQn);
    }
}

static void UPOWER_Ready(uint32_t soc, uint32_t vmajor, uint32_t vminor)
{
    callbackStatus = true;

    (void)soc;
    (void)vmajor;
    (void)vminor;
}

static void UPOWER_Callback(upwr_sg_t sg, uint32_t func, upwr_resp_t errCode, int ret)
{
    callbackStatus = true;
}

/*!
 * @brief Check status of current request to uPower.
 *
 * Will block till related callback function has been called
 *
 * @sg Indicate which Service Group that request point to
 * Note: It is replaced by UPOWER_CheckReqWithArgs, pls don't use the api.
 */
void UPOWER_CheckReq(upwr_sg_t sg)
{
    upwr_req_status_t reqStatus;
    upwr_resp_t rsp = UPWR_RESP_COUNT;
    int ret = -1;

    /* wait callback */
    while (!callbackStatus)
    {
    }

    callbackStatus = false;

    /* Get reply from upower */
    reqStatus = upwr_poll_req_status(sg, NULL, &rsp, &ret, 0U);
    if (reqStatus != UPWR_REQ_OK)
    {
        assert(false);
    }
}

/*!
 * @brief Check status of current request to uPower.
 *
 * Will block till related callback function has been called
 *
 * @sg Indicate which Service Group that request point to
 * @sgfptr: pointer to the variable that will hold the function id of the last request completed
 * @errptr: pointer to the variable that will hold the error code
 * @retptr: pointer to the variable that will hold the value returned by the last request completed (invalid if the last
 * request completed didn't return any value)
 * @attempts: maximum number of polling attempts; if attempts > 0 and is reached with no service response received,
 * upwr_poll_req_status returns UPWR_REQ_BUSY and variables pointed by sgfptr, retptr and errptr are not updated; if
 * attempts = 0, upwr_poll_req_status waits "forever".
 */
void UPOWER_CheckReqWithArgs(upwr_sg_t sg, uint32_t *sgfptr, upwr_resp_t *errptr, int *retptr, uint32_t attempts)
{
    upwr_req_status_t reqStatus;

    /* wait callback */
    while (!callbackStatus)
    {
    }

    callbackStatus = false;

    /* Get reply from upower */
    reqStatus = upwr_poll_req_status(sg, sgfptr, errptr, retptr, attempts);
    if (reqStatus != UPWR_REQ_OK)
    {
        assert(false);
    }
}

/*!
 * @brief Initialize MU interface for uPower access.
 *
 * @param pVersion Pointer to the structure to save uPower ROM and RAM versions
 */
void UPOWER_Init(upower_version_t *pVersion)
{
    int status;
    uint32_t soc;
    uint32_t major, minor, fixes;
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    CLOCK_EnableClock(kCLOCK_UpowerMuARtd);

    status = upwr_init(RTD_DOMAIN, UPOWER_MU, NULL, NULL, UPOWER_DummyInstallISR, UPOWER_LockMuInt);
    if (status != 0)
    {
        assert(false);
    }

    NVIC_EnableIRQ(uPower_IRQn); /* fix lost upower interrupt issue(The api will enable upower interrupt and do memory
                                    barrier operation dsb, isb) */

    soc = upwr_rom_version(&major, &minor, &fixes);
    if (soc == 0U)
    {
        assert(false);
    }

    if (pVersion != NULL)
    {
        pVersion->romMajor = major;
        pVersion->romMinor = minor;
        pVersion->romFixes = fixes;
    }

    status = upwr_start(1U, UPOWER_Ready);
    if (status != 0)
    {
        assert(false);
    }

    UPOWER_CheckReqWithArgs(UPWR_SG_EXCEPT, &sgf, &err, &ret, 0);
    assert(err == UPWR_RESP_OK);

    major = upwr_ram_version(&minor, &fixes);

    if (pVersion != NULL)
    {
        pVersion->ramMajor = major;
        pVersion->ramMinor = minor;
        pVersion->ramFixes = fixes;
    }
}

/*!
 * @brief Deinitialize MU interface for Sentinel access.
 */
void UPOWER_Deinit(void)
{
    NVIC_DisableIRQ(uPower_IRQn);
}

/*!
 * @brief Power on certain domain without reset.
 *
 * @param domain Target domain to power on.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_PowerOnDomain(soc_domain_t domain)
{
    int status;
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    status = upwr_pwm_dom_power_on(domain, 0, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_PWRMGMT, &sgf, &err, &ret, 0);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}

/*!
 * @brief Reset and kick off certain domain.
 *
 * @param domain Target domain to boot.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_BootDomain(soc_domain_t domain)
{
    int status;
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    status = upwr_pwm_boot_start(domain, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_PWRMGMT, &sgf, &err, &ret, 0);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}

/*!
 * @brief Power on power switches.
 *
 * @param mask Bits to define which switch should be turned on. The value should be ORed by @ref upower_ps_mask_t.
 *             Bit value 1 means the switch is to be powered on; Value 0 means the switch keeps unchanged.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_PowerOnSwitches(upower_ps_mask_t mask)
{
    int status;
    uint32_t switches = (uint32_t)mask;
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    status = upwr_pwm_power_on(&switches, NULL, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_PWRMGMT, &sgf, &err, &ret, 0);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}

/*!
 * @brief Power off power switches.
 *
 * @param mask Bits to define which switch should be turned off. The value should be ORed by @ref upower_ps_mask_t.
 *             Bit value 1 means the switch is to be powered off; Value 0 means the switch keeps unchanged.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_PowerOffSwitches(upower_ps_mask_t mask)
{
    int status;
    uint32_t switches = (uint32_t)mask;
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    status = upwr_pwm_power_off(&switches, NULL, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_PWRMGMT, &sgf, &err, &ret, 0);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}

/*!
 * @brief Power on memory partitions array/periphery logic. If a memory is requested to turn on, but the
 * power switch that feeds that memory is not, the power switch will be turned on automatically.
 *
 * The parameter mask bits define which memory partition should be turned on. The value should be ORed by
 * upower_mp0_mask_t or upower_mp1_mask_t. Mask bit value 1 means the switch is to be powered on; Value 0
 * means the switch keeps unchanged.
 *
 * @param mask0 memory partition group 0 mask, see @ref upower_mp0_mask_t.
 * @param mask1 memory partition group 1 mask, see @ref upower_mp1_mask_t.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_PowerOnMemPart(uint32_t mask0, uint32_t mask1)
{
    int status;
    uint32_t mem[2] = {mask0, mask1};
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    status = upwr_pwm_power_on(NULL, mem, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_PWRMGMT, &sgf, &err, &ret, 0);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}

/*!
 * @brief Power off memory partitions array/periphery logic.
 *
 * The parameter mask bits define which memory partition should be turned off. The value should be ORed by
 * upower_mp0_mask_t and upower_mp1_mask_t. Mask bit value 1 means the switch is to be powered off; Value 0
 * means the switch keeps unchanged.
 *
 * @param mask0 memory partition group 0 mask, see @ref upower_mp0_mask_t.
 * @param mask1 memory partition group 1 mask, see @ref upower_mp1_mask_t.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_PowerOffMemPart(uint32_t mask0, uint32_t mask1)
{
    int status;
    uint32_t mem[2] = {mask0, mask1};
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    status = upwr_pwm_power_off(NULL, mem, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_PWRMGMT, &sgf, &err, &ret, 0);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}

/*!
 * @brief Power on memory partitions array logic and power off its periphery logic. If a memory array is
 * requested to turn on, but the power switch that feeds that memory is not, the power switch will be turned
 * on automatically.
 *
 * The parameter mask bits define which memory partition should be turned on. The value should be ORed by
 * upower_mp0_mask_t or upower_mp1_mask_t. Mask bit value 1 means the switch is to be powered on; Value 0
 * means the switch keeps unchanged.
 *
 * @param mask0 memory partition group 0 mask, see @ref upower_mp0_mask_t.
 * @param mask1 memory partition group 1 mask, see @ref upower_mp1_mask_t.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_RetainMemPart(uint32_t mask0, uint32_t mask1)
{
    int status;
    uint32_t mem[2] = {mask0, mask1};
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    status = upwr_pwm_mem_retain(mem, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_PWRMGMT, &sgf, &err, &ret, 0);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}

/*!
 * @brief M33 call this API to inform uPower, M33 is using ddr.
 *
 * @param use_ddr not 0, true, means that RTD is using ddr. 0, false, means that, RTD is not using ddr.
 * @return 0 if ok, failure otherwise(-1 if service group is busy, -3 if called in an invalid API state).
 */
int UPOWER_SetRtdUseDdr(bool use_ddr)
{
    int status;
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    status = upwr_xcp_set_rtd_use_ddr(RTD_DOMAIN, (uint32_t)use_ddr, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_EXCEPT, &sgf, &err, &ret, 0);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}
/*!
 * @brief M33 call this API to Power On Application Domain when Application Domain is in Power Down/Deep Power Down
 * mode. After upower get the msg, upower write a flag to registers according to msg. Then upower will get a WUU1
 * interrupt request and upower change Power Down mode/Deep Power mode to Active mode when Application Domain is in
 * Power Down/Deep Power Down mode.
 *
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_PowerOnADInPDMode(void)
{
    int status;
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    status = upwr_xcp_set_rtd_apd_llwu(APD_DOMAIN, (uint32_t)true, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_EXCEPT, &sgf, &err, &ret, 0);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}

/*!
 * @brief Set SG PowerManagement parameters of uPower.
 *
 * Please see upower_soc_defs.h file for struct upwr_pwm_param_t
 *
 * @param pcfg_in User's selection for PowerManagement parameter of uPower
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_SetPwrMgmtParam(upwr_pwm_param_t *pcfg_in)
{
    int status;
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    assert(pcfg_in);
    status = upwr_pwm_param(pcfg_in, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_PWRMGMT, &sgf, &err, &ret, 0);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}

/*!
 * @brief Reduce Buck2 and Buck3 voltage in STANDBY mode.
 *
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_ReduceBuck23VoltInSTBY(void)
{
    int status;
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err_code = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    status = upwr_xcp_i2c_access(0x32, 1, 1, 0x14, 0x7A, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_EXCEPT, &sgf, &err_code, &ret, 0);
        assert(err_code == UPWR_RESP_OK);
    }
    else
    {
        goto err;
    }

    status = upwr_xcp_i2c_access(0x32, 1, 1, 0x13, 0x50, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_EXCEPT, &sgf, &err_code, &ret, 0);
        assert(err_code == UPWR_RESP_OK);
    }
    else
    {
        goto err;
    }

    status = upwr_xcp_i2c_access(0x32, 1, 1, 0x4E, 0x5C, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_EXCEPT, &sgf, &err_code, &ret, 0);
        assert(err_code == UPWR_RESP_OK);
    }
    else
    {
        goto err;
    }

    status = upwr_xcp_i2c_access(0x32, 1, 1, 0x20, 0x04, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_EXCEPT, &sgf, &err_code, &ret, 0);
        assert(err_code == UPWR_RESP_OK);
    }
    else
    {
        goto err;
    }

    status = upwr_xcp_i2c_access(0x32, 1, 1, 0x1D, 0x04, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_EXCEPT, &sgf, &err_code, &ret, 0);
        assert(err_code == UPWR_RESP_OK);
    }
    else
    {
        goto err;
    }

    status = upwr_xcp_i2c_access(0x32, 1, 1, 0x4E, 0x5C, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_EXCEPT, &sgf, &err_code, &ret, 0);
        assert(err_code == UPWR_RESP_OK);
    }
    else
    {
        goto err;
    }

    status = upwr_xcp_i2c_access(0x32, 1, 1, 0x2D, 0x04, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_EXCEPT, &sgf, &err_code, &ret, 0);
        assert(err_code == UPWR_RESP_OK);
    }
    else
    {
        goto err;
    }

    status = upwr_xcp_i2c_access(0x32, 1, 1, 0x2A, 0x04, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_EXCEPT, &sgf, &err_code, &ret, 0);
        assert(err_code == UPWR_RESP_OK);
    }

err:
    return status;
}

/*!
 * @brief Set DDR retention control bit.
 *
 * @param domain Target domain to power on.
 * @param enable true means set ddr retention, false means clear ddr retention.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_SetDDRRetention(soc_domain_t domain, bool enable)
{
    int status;
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    status = upwr_xcp_set_ddr_retention(domain, (uint32_t)enable, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_EXCEPT, &sgf, &err, &ret, 0);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}

/*
 * @brief change PMIC voltage.
 *
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_ChngPmicVoltage(uint32_t rail, int voltage)
{
    int status = -1;
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    status = upwr_vtm_chng_pmic_voltage(rail, (uint32_t)voltage, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_VOLTM, &sgf, &err, &ret, 0);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}

/*!
 * @brief Control LDO1 power supply.
 *
 * @param enable true means turn on power supply, false means off.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_SetLDO1Power(bool enable)
{
    uint32_t size;
    int status;
    struct pmic_config_struct pmic_config_struct_data;
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    pmic_config_struct_data.cfg_tag      = PMIC_CONFIG_TAG;
    pmic_config_struct_data.cfg_reg_size = 1;

    pmic_config_struct_data.reg_addr_data_array[0].reg = 0x30;

    if (enable)
    {
        /* Set LDO1 power to 1.1000V, according to PCA9460 */
        pmic_config_struct_data.reg_addr_data_array[0].data = 0x9d;
    }
    else
    {
        /* Set LDO1 power to 0V, according to PCA9460 */
        pmic_config_struct_data.reg_addr_data_array[0].data = 0x9c;
    }

    size = sizeof(pmic_config_struct_data.cfg_tag) + sizeof(pmic_config_struct_data.cfg_reg_size) +
           pmic_config_struct_data.cfg_reg_size * (sizeof(uint32_t) + sizeof(uint32_t));

    status = upwr_vtm_pmic_config((void *)&pmic_config_struct_data, size, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_VOLTM, &sgf, &err, &ret, 0);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}

/*!
 * @brief Control Buck3 power supply.
 *
 * @param enable true means turn on power supply, false means off.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_SetBuck3Power(bool enable)
{
    uint32_t size;
    int status;
    struct pmic_config_struct pmic_config_struct_data;
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    pmic_config_struct_data.cfg_tag      = PMIC_CONFIG_TAG;
    pmic_config_struct_data.cfg_reg_size = 1;

    pmic_config_struct_data.reg_addr_data_array[0].reg = 0x22;

    if (enable)
    {
        /* Set BUCK3 power to 1.1000V, according to PCA9460 */
        pmic_config_struct_data.reg_addr_data_array[0].data = 0x28;
    }
    else
    {
        /* Set BUCK3 power to 0.7375V, according to PCA9460 */
        pmic_config_struct_data.reg_addr_data_array[0].data = 0xb;
    }

    size = sizeof(pmic_config_struct_data.cfg_tag) + sizeof(pmic_config_struct_data.cfg_reg_size) +
           pmic_config_struct_data.cfg_reg_size * (sizeof(uint32_t) + sizeof(uint32_t));

    status = upwr_vtm_pmic_config((void *)&pmic_config_struct_data, size, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_VOLTM, &sgf, &err, &ret, 0);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}

/*!
 * @brief Write PMIC registers by I2C.
 *
 * @param reg_addr means pmic ic target address.
 * @param reg_val means write data, specific data can be found in PCA9460.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_SetPmicReg(uint32_t reg_addr, uint32_t reg_val)
{
    int status;
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    status = upwr_xcp_i2c_access(PMIC_I2C_ADDR, PMIC_WRITE_DATA_SIZE, PMIC_IC_WRITE_DATA_SIZE, reg_addr, reg_val,
                                 UPOWER_Callback);

    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_EXCEPT, &sgf, &err, &ret, 0);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}

/*!
 * @brief Read PMIC registers by I2C.
 *
 * @param reg_addr means pmic ic pca9460 target address.
 * @param reg_val means value of register.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_ReadPmicReg(uint32_t reg_addr, uint8_t *reg_val)
{
    int status;
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */

    status =
        upwr_xcp_i2c_access(PMIC_I2C_ADDR, PMIC_READ_DATA_SIZE, PMIC_IC_READ_DATA_SIZE, reg_addr, 0, UPOWER_Callback);

    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_EXCEPT, &sgf, &err, &ret, 0);
        assert(err == UPWR_RESP_OK);
    }

    *reg_val = (uint8_t)ret;

    return status;
}

/*!
 * @brief Init BUCK2 BUCK3 output voltage table.
 */
void UPOWER_InitBuck2Buck3Table(void)
{
    int i;

    buck2_buck3_output_voltage_array[0] = 0.6000;
    for (i = 0; i < BUCK_OUTPUT_TABLE_SIZE; i++)
    {
        buck2_buck3_output_voltage_array[i] += BUCK2_BUCK3_VOLTAGE_STEPS;
    }
}

/*
 * @brief get PMIC voltage.
 *
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_GetPmicVoltage(uint32_t rail, int *voltage)
{
    int status = -1;
    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */

    status = upwr_vtm_get_pmic_voltage(rail, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_VOLTM, &sgf, &err, voltage, 0U);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}

/*!
 * @brief Change Bias Configuration(biasing options: NBB, RBB, ARBB, AFBB; Bias Voltage) for RTD Domain
 *
 * @param  drive_mode Drive Mode: UD, ND, OD.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_ChngRTDDomBias(drive_mode_e drive_mode)
{
    // clang-format off
    /*
     * +---------------------------------------------------------------------------------------------------------------------------------------+
     * |  RTD Power Mode |    Biasing Option |  Drive Mode | Max CM33_CORECLK freq/MHz | Max CM33_BUSCLK freq/MHz |  Max CM33_SLOWCLK freq/MHz |
     * -----------------------------------------------------------------------------------------------------------------------------------------
     * |    ACTIVE       |        ARBB       |     UD      |        38.4               |         20               |          12.5              |
     * -----------------------------------------------------------------------------------------------------------------------------------------
     * |    ACTIVE       }        AFBB       |     ND      |        160                |         65               |           20               |
     * -----------------------------------------------------------------------------------------------------------------------------------------
     * |    ACTIVE       |        AFBB       |     OD      |        216                |         108              |           24               |
     * +---------------------------------------------------------------------------------------------------------------------------------------+
     *
     */
    // clang-format on

    uint32_t sgf = 0xFFFFFFFFU; /* the function id of the last request completed*/
    upwr_resp_t err = UPWR_RESP_COUNT; /* the error code */
    int ret = -1; /* the value returned by the last request completed */
    struct upwr_dom_bias_cfg_t *bias = NULL;
    struct upwr_dom_bias_cfg_t ud_bias = {
        .apply = BIAS_APPLY_RTD, /* apply to RTD only */
        .dommode = ARBB_BIAS_MODE,
        .dombias = {
            .rbbn = 1300, /* 1300 mV */
            .rbbp = 1300, /* 1300 mV */
	},
    };
    struct upwr_dom_bias_cfg_t nd_bias = {
        .apply = BIAS_APPLY_RTD, /* apply to RTD only */
        .dommode = AFBB_BIAS_MODE,
        .dombias = {
            .rbbn = 100, /* 100 mV */
            .rbbp = 100, /* 100 mV */
	},
    };
    struct upwr_dom_bias_cfg_t od_bias = {
        .apply = BIAS_APPLY_RTD, /* apply to RTD only */
        .dommode = AFBB_BIAS_MODE,
        .dombias = {
            .rbbn = 100, /* 100 mV */
            .rbbp = 100, /* 100 mV */
	},
    };
    int status;

    switch (drive_mode)
    {
        case DRIVE_MODE_UD:
		bias = &ud_bias;
		break;
        case DRIVE_MODE_ND:
		bias = &nd_bias;
		break;
        case DRIVE_MODE_OD:
		bias = &od_bias;
		break;
        default:
		break;
    }
    status = upwr_pwm_chng_dom_bias(bias, UPOWER_Callback);
    if (status == 0)
    {
        UPOWER_CheckReqWithArgs(UPWR_SG_PWRMGMT, &sgf, &err, &ret, 0U);
        assert(err == UPWR_RESP_OK);
    }

    return status;
}
