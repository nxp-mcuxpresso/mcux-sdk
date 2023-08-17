# Leveraging MCUXpresso SDK Power Manager for MCU class of devices

## Table of content
1. [Introduction](#introduction)
2. [Glossary](#glossary)
3. [SDK Power Manager](#sdkpm)
    1. [Features](#features)
    2. [Architecture](#architecture)
4. [Application Example](#appex)
5. [APIs references](#apiref)
6. [Conclusion](#conclusion)


## 1. Introduction <a id="introduction"></a>

MCUs feature different low-power states for static power optimizations. Multiple states such as ON, retention (for memories) or OFF can be defined for each MCU low-power state, peripheral, memory or clock.  Each of these states can be specific to a device.

The Power Manager component included in NXP’s MCUXpresso SDK is a software framework available for bare-metal code and FreeRTOS applications, aiming at facilitating its development. By abstracting the SoC architecture, the developer can easily integrate the management of low-power states in the application and speed up the time-to-market. The SDK Power Manager uses low-level drivers, offloads the full comprehension of the device by providing a resources and operating modes constraints mechanism, and optimizes the power consumption by shutting down the resources not required by the user.

<br/>

## 2. Glossary <a id="glossary"></a>

- Bare-Metal – application/driver code without an Operating System.  
- EVK – Evaluation Kit / Evaluation Board.  
- MCU – Microcontroller Unit.  
- SDK – Software Development Kit.  
- SoC – System-on-Chip.  

<br/>

## 3. SDK Power Manager <a id="sdkpm"></a>

### 1. Features <a id="features"></a>   

<br/>

Features of the SDK Power Manager are:  
- Manage the transition for the different operating modes by seamlessly modifying the registers based on resource constraints:  
    - SDK Power Manager turns all resources OFF by default, except the ones required by the user.
- Ease the management of wakeup sources.  
- Notify upper layer (for example the application) about power transitions or wakeup events.  
- Gather constraints and/or find the lowest-power state achievable depending on user constraints or timing (if declared):  
    - The user can specify the low-power state to enter and the resource constraints. If the resource constraints or timing do not match the constraints of the low-power state, the SDK Power Manager will find a lighter low-power state that satisfies the required resource constraints and timing.  
    - The user is only required to specify the low-power state to enter. All the possible resources satisfying the low-power states will be turned off by the SDK Power Manager.  
    - The user is only required to specify the resource constraints. The SDK Power Manager will find the deepest low-power state to enter that satisfies the resource constraints.  

<br/>

### 2. Architecture <a id="architecture"></a>  

<br/>

The SDK power manager is composed of two parts.  
Firstly the “core” part, is generic across devices and provides APIs to be called in the application. This part is composed of different sub-modules:  
- The policy module: gathers all constraints and finds the deepest power state allowed.  
- The wakeup-source manager module: configures the wakeup sources and processes registered wakeup-source handler callbacks.  
- The notification module: Notifies the upper layer of specific power transitions and events.  

Then the “device” part, is specific for each device and describes the entry/exit sequences of the power modes, called the sequencer. There is also the description of all the resource constraints available: the pre-defined constraints for the low-power states. This part is not intended to be modified by the user.  Instead, the application defines the resource constraints to keep enabled for a given low-power state.

<br/>

![SDK Power Manager Architecture Diagram](images/SDK_PM_architecture.png "SDK Power Manager Architecture Diagram")  

<br/>

The framework is defined and developed by NXP, exposing the pre-defined constraints and easy-to-use APIs to the user for application development.  
Here are examples of APIs to call in the application to leverage the SDK power manager: 
- **PM_CreateHandle** --> MANDATORY ; Initializes the power manager handler, to be called before using other Power Manager APIs.  

- **PM_RegisterNotify** --> OPTIONAL ; Registers a notify element into the selected group. The callback of the group will be called just before the entry to low-power state and just after the exit from the low-power state.  

- **PM_InitWakeupSource** --> OPTIONAL ; Initialize the wakeup source.  

- **PM_RegisterTimerController** --> OPTIONAL ; Register a timer as a wakeup source, to be called with **PM_InitWakeupSource**.  

- **PM_SetConstraints** --> MANDATORY ; Set constraints to Power Manager defined by the user, and/or for a low-power state. To easily define constraints, the user can define a macro.  

- **PM_EnablePowerManager** --> MANDATORY ; Enable/Disable Power Manager functions.  

- **PM_EnterLowPower** --> MANDATORY ; Find the ideal low-power state available, based on registered constraints, then notifies groups, and enters/exits the low-power state.  

<br/>

There is also macros that the user can modify depending on the need, located in *fsl_pm_device_config.h*:  

- **FSL_PM_SUPPORT_NOTIFICATION** --> Allows the Power Manager to notify created notification groups of power transitions, i.e entry/exit of a state. It can be useful to re-enable a peripheral just after exiting the low-power state.  

- **FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER** --> Allows the Power Manager to fully manage (create, disable, handle, trigger) wakeup sources.  

- **FSL_PM_SUPPORT_LP_TIMER_CONTROLLER** --> Allows the Power Manager to control timers.  

- **FSL_PM_SUPPORT_ALAWAYS_ON_SECTION** --> Allows to store variables in an always-on RAM.  

For more details on APIs available and description, please refer to the *fsl_pm_core* files.

<br/>

## 4. Application Example <a id="appex"></a>

<br/>

This example is a bare-metal application based on the [i.MX RT500 EVK](https://www.nxp.com/design/development-boards/i-mx-evaluation-and-development-boards/i-mx-rt595-evaluation-kit:MIMXRT595-EVK). This example demonstrates low-power transition by leveraging the SDK Power Manager. In this application, the code is running in SRAM partition 16 (0x2010 0000) with a size of 256kB (0x40000) and stored in Octal flash using FlexSPI0.  

![iMXRT500 memory used](images/memory_example.png "iMXRT500 memory used")  

The first step defines the resources the user wants to keep ON/retain for a given low-power state. Each resource-constraint definition can be found in the file *fsl_pm_device.h*.  

`#define PM_RESC_ACMP_ACTIVE PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_ACMP)`  
`#define PM_RESC_PQ_SRAM_ACTIVE PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_PQ)`  
`#define PM_RESC_FLEXSPI0_SRAM_ACTIVE PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_FLEXSPI0)`  
`#define PM_RESC_FLEXSPI0_SRAM_RETENTION PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_FLEXSPI0)`  
<br/>

For example, defining **PM_RESC_ACMP_ACTIVE** will keep the resource ACMP active for a low-power state, if it matches with the system pre-defined constraints.  

<br/>

In this example, only the mandatory resources are kept ON for deep sleep that will be specified later as a power mode constraint, thus the declaration is as follow:  
`#define APP_DEEP_SLEEP_CONSTRAINTS        \`  
`2U, PM_RESC_SRAM16_256KB_RETENTION, PM_RESC_FLEXSPI0_SRAM_RETENTION`

In deep sleep, only the defined SRAM partition and the FLEXSPI0 SRAM are retained, i.e., the memory is retained but not accessible. All the other resources are turned OFF.  

<br/>

For sleep low-power state, the following resources are kept ON:  
`#define APP_SLEEP_CONSTRAINTS`  
`7U, PM_RESC_MAIN_CLK_ON, PM_RESC_SYSXTAL_ON, PM_RESC_LPOSC_ON, PM_RESC_SYSPLLLDO_ON,` `PM_RESC_SYSPLLANA_ON, PM_RESC_FLEXSPI0_SRAM_ACTIVE, \ PM_RESC_SRAM16_256KB_ACTIVE`  

<br/>

In the application, the user must first create the PM handle:  
`PM_CreateHandle(&g_pmHndle);`  

<br/>

The user can declare wakeup sources, first by calling the PM API, and then by declaring the wakeup-source parameter in the application. In this example, the button SW2 will be used as wakeup source.  
The user must call the PM API with the corresponding parameter:  
`PM_InitWakeupSource(&g_UserkeyWakeupSource, (uint32_t)PIN_INT0_IRQn, NULL, true);`  

<br/>

And then the user defines the GPIO parameter using the MCUXpresso SDK driver APIs:  
`gpio_pin_config_t gpioPinConfigStruct;`  

`/* Set SW pin as GPIO input. */`  
`gpioPinConfigStruct.pinDirection = kGPIO_DigitalInput;`  
`GPIO_PinInit(APP_USER_WAKEUP_KEY_GPIO, APP_USER_WAKEUP_KEY_PORT,APP_USER_WAKEUP_KEY_PIN, &gpioPinConfigStruct);`

`/* Configure the Input Mux block and connect the trigger source to PinInt channel. */`  
`INPUTMUX_Init(INPUTMUX);`  
`INPUTMUX_AttachSignal(INPUTMUX, kPINT_PinInt0, APP_USER_WAKEUP_KEY_INPUTMUX_SEL); /*` 

`Using channel 0. */`  
`INPUTMUX_Deinit(INPUTMUX); /* Turnoff clock to inputmux to save power. Clock is only needed to make changes */`

`/* Configure the interrupt for SW pin. */`  
`PINT_Init(PINT);`  
`PINT_PinInterruptConfig(PINT, kPINT_PinInt0, kPINT_PinIntEnableFallEdge,pint_intr_callback);`  
`PINT_EnableCallback(PINT); /* Enable callbacks for PINT */`  

<br/>

Then, the user must set the defined constraints, with the following functions:  
`PM_SetConstraints(PM_LP_STATE_DEEP_SLEEP, APP_DEEP_SLEEP_CONSTRAINTS);`  

There is two types of constraints that can be set:  
- Constraints on the low power mode,
- Constraints on the resources.  

For example:  
`PM_SetConstraints(PM_LP_STATE_NO_CONSTRAINT, APP_DEEP_SLEEP_CONSTRAINTS);`  

The Power Manager will find the deepest power state that satisfies the resources constraints in *APP_DEEP_SLEEP_CONSTRAINTS.*  

<br/>

`PM_SetConstraints(PM_LP_STATE_DEEP_SLEEP, APP_DEEP_SLEEP_CONSTRAINTS);`  

Here, a constraint is set on the low power mode, and on the resources. The Power Manager will check if the resource constraints matches with the ones pre-defined for the low power mode. If there is an incompatibility, the Power Manager will find a lighter low power mode that satisfies the resource constraints set by the user. In the other case in that example, deep sleep mode will be reached with resources specified in *APP_DEEP_SLEEP_CONSTRAINTS* will be ON.  

<br/>

`PM_SetConstraints(PM_LP_STATE_DEEP_SLEEP, 0);`  

Here, only a low power mode constraint is set, without resources constraints. Thus the Power Manager will turn everything off in this state, except the pre-defined resources constraints for this low power mode. This case is rarely used, as resources are often always requiring as RAM retention to properly wakeup the device in sleep and deep sleep. For lower low power states where a reset is required, this type of constraint can be used.  
Constraints on the low power mode are priority, i.e. if there is two constraints on the low power, the Power Manager will selects the lighter one.  

<br/>

The user can enable the SDK Power Manager framework and enter the low-power mode.  
`PM_EnablePowerManager(true);`  

<br/>

To enter in a low power mode, the following Power Manager function must be used:  
`PM_EnterLowPower(durationTicks);`  

The *durationTicks* parameter can be useful and leveraged when an exit latency is declared for a low-power state. It will influence the low-power state entered if the specified duration is less than the exit latency of the low-power state.  

The exit latency is declared by the developer for a low-power state. For example if the deep-sleep state has an exit latency of 250us, the declaration is as follow in *fsl_pm_device.c*:

`/* Deep Sleep */`  
&emsp;&emsp;`{`  
&emsp;&emsp;&emsp;`.exitHwLatency = 250U, /* 250 us */`  
&emsp;&emsp;&emsp;`.fixConstraintsMask =`  
&emsp;&emsp;&emsp;&emsp;`{`  
&emsp;&emsp;&emsp;&emsp;&emsp;`.rescMask[0U] = 0x00000000UL,`  
&emsp;&emsp;&emsp;&emsp;&emsp;`.rescMask[1U] = 0x00000000UL,`  
&emsp;&emsp;&emsp;&emsp;&emsp;`.rescMask[2U] = 0x0UL,`  
&emsp;&emsp;&emsp;&emsp;`},`  
&emsp;&emsp;&emsp;`.varConstraintsMask =`  
&emsp;&emsp;&emsp;&emsp;`{`  
&emsp;&emsp;&emsp;&emsp;&emsp;`.rescMask[0U] = 0xFFFFFFFFUL,`  
&emsp;&emsp;&emsp;&emsp;&emsp;`.rescMask[1U] = 0xFFFFFFFFUL,`  
&emsp;&emsp;&emsp;&emsp;&emsp;`.rescMask[2U] = 0x3UL,`   
&emsp;&emsp;&emsp;&emsp;`},`  

When the Power Manager tries to find the deepest state reachable, it will compare the exit latency of the low power state *exitHwLatency* with the duration tick specified by the user. In that case, if *durationTicks* variable is less or equal to 250 us, then the deep sleep state is unreachable, even if the resources constraints matches. A lighter low power state will be reach satisfying resources constraints and *durationTicks*.  

<br/>

The user can set constraints on resources and low power mode, following the same mechanism, for sleep state for example:  
`PM_SetConstraints(PM_LP_STATE_SLEEP, APP_SLEEP_CONSTRAINTS);`  

By having two low power mode constraints, i.e sleep and deep-sleep, the Power Manager will go into the lightest low power mode. In this case, as there is not exit latency for the sleep state, sleep state will be reached. The resources constraints to keep will be the sum of the previous ones with the new defined, i.e *APP_DEEP_SLEEP_CONSTRAINTS + APP_SLEEP_CONSTRAINTS*.  

<br/>

To unset resource constraint and/or low power mode constraint, the following function must be used:  
`PM_ReleaseConstraints(PM_LP_STATE _SLEEP, APP_DEEP_SLEEP_CONSTRAINTS);`  

Here, the sleep state is not registered anymore in the Power Manager, thus deep sleep state will be reached with the corresponding constraints, if the *durationTicks* exceeds the exit latency of the deep sleep state. The *APP_DEEP_SLEEP_CONSTRAINTS* resources constraints are also unregistered, thus the resources constraints to keep are *APP_SLEEP_CONSTRAINTS*.  

<br/>

**Note:** If a low power mode constraint or resource constraints has been set multiple times through *PM_SetConstraints*, one should call the *PM_ReleaseConstraints* function as many time as required to fully remove the constraint from the SDK Power Manager. This behavior can be useful in the case where multiple peripherals sets a constraint in a low power mode for example.  

<br/>

Finally, when the Power Manager is not required anymore in the application, it must be disabled with:  
` PM_EnablePowerManager(false);`  

<br/>

## 5. APIs references <a id="apiref"></a>

<br/>

**void PM_CreateHandle (pm_handle_t *  handle)**  
Initialize the power manager handle, this function should be invoked before using other power manager APIs.  

*Note:* By default, the power manager is disabled.  

*Parameter:* handle : Pointer to the pm_handle_t structure, upper layer software should pre-allocate the handle global variable.  

<br/>

**void PM_EnablePowerManager (bool  enable)**  
Enable/disable power manager functions.   

*Parameter:* enable : Used to enable/disable power manager functions.  

<br/>

**void PM_EnterLowPower (uint64_t  duration)**  
Power manager core API, this API should be used on RTOS's IDLE task.  
This function contains several steps:  
1. Compute target power state based on the policy module.
2. Notify upper layer software of the power mode transitions.
3. Enter into targeted power state.
4. Exit from low power state, if wakeup event occurred.
5. Notify upper layer software of the power mode exiting.  

The target power state is determined based on two factors: a. The input parameter should be larger than state's exitHwLatency attribution. b. resConstraintsMask logical AND state's lossFeature should equal to 0, because constraint can be understood as some features cannot loss.
 
*Parameter:* duration : The time in low power mode, this value is calculated from RTOS API.    

<br/>

**void PM_RegisterTimerController (pm_handle_t *  handle, pm_low_power_timer_start_func_t  timerStart, pm_low_power_timer_stop_func_t  timerStop, pm_low_power_timer_get_timestamp_func_t  getTimestamp, pm_low_power_timer_get_duration_func_t getTimerDuration)**  
Register timer controller related functions to power manager. 
If low power timer is the wakeup source, please remember to register it into power manager by using PM_EnableWakeupSource () function.  

*Parameters:*  
handle : Pointer to the pm_handle_t structure.    
timerStart : Low power timer start function, this parameter can be NULL, and it means low power timer is not set as the wakeup source.  
timerStop  : Low power timer stop function, this parameter can also be set as NULL.  
getTimestamp : Low power timestamp function, this parameter can also be set as NULL.  
getTimerDuration : Get timer duration function. this parameter can also be set as NULL.  

<br/>

**uint64_t PM_GetLastLowPowerDuration(void)**  
Get the actual low power state duration.

<br/>

**void PM_RegisterCriticalRegionController (pm_handle_t *  handle, pm_enter_critical  criticalEntry, pm_exit_critical  criticalExit)**  
Register critical region related functions to power manager.  

*Note:* There are multiple-methods to implement critical region(E.g. interrupt controller, locker, semaphore).  

*Parameters:*  
handle : Pointer to the pm_handle_t structure.    
criticalEntry : Enter critical function to register.   
criticalExit : Exit critical function to register.   

<br/>

**status_t PM_RegisterNotify (pm_notify_group_t  groupId, const pm_notify_element_t *  notifyElement)**  
Register notify element into the selected group.   

*Parameters:*  
groupId : The group of the notify list, this will affect the execution sequence.  
notifyElement : The pointer to pm_notify_element_t.   

*Returns:* status_t The status of register notify object behavior.   

<br/>

**void PM_UpdateNotify (void *  notifyElement, pm_notify_callback_func_t  callback, void *  data)**  
Update notify element's callback function and application data.    

*Parameters:*  
notifyElement : The pointer to the notify element to update.    
callback : The callback function to be updated. 
data : Pointer to the callback function private data.   

<br/>

**status_t PM_UnregisterNotify (void *  notifyElement)**  
Remove notify element from its notify group.     

*Parameter:* notifyElement : The pointer to the notify element to remove.    
  
<br/>

**void PM_InitWakeupSource (pm_wakeup_source_t *  ws, uint32_t  wsId, pm_wake_up_source_service_func_t  service, bool  enable)**  
Initialize the wakeup source object.     

*Parameters:*  
ws : Pointer to the pm_wakeup_source_t variable.  
wsId : Used to select the wakeup source, the wsId of each wakeup source can be found in fsl_pm_device.h or device description file.  
service : The function to be invoked when wake up source asserted.  
enable : Used to enable/disable the selected wakeup source.   

<br/>

**status_t PM_EnableWakeupSource (pm_wakeup_source_t *  ws)**  
Enable wakeup source.   

*Parameter:* ws : Pointer to the wakeup source object to be enabled.  

*Returns:* status_t The status of enable wakeup source behavior.  

<br/>

**status_t PM_DisableWakeupSource (pm_wakeup_source_t *  ws)**  
Disable wakeup source.  

*Parameter:* ws : Pointer to the wakeup source object to be disabled.  

*Returns:* status_t The status of disable wakeup source behavior.  

<br/>

**status_t PM_HandleWakeUpEvent (void)**  
Checks if any enabled wake up source is responsible for last wake up event. In such case, it will call the wake-up source callback if it has been registered. Likely to be called from Wake-Up Unit IRQ Handler.      

*Returns:* status_t The status of handling the wake-up event.   

<br/>

**status_t PM_TriggerWakeSourceService (pm_wakeup_source_t *  ws)**  
If the specific wakeup event occurs, invoke this API to execute its service function.   

*Parameter:* ws : Pointer to the wakeup source object.   

*Returns:* status_t The status of trigger wakeup source behavior.    

<br/>

**status_t PM_SetConstraints (uint8_t  powerModeConstraint, int32_t  rescNum,   ...)**  
Used to set constraints(including power mode constraint and resource constraints) 
For example, if the device support 3 resource constraints: PM_RESC_1, PM_RESC_2, PM_RESC3. PM_SetConstraints(Sleep_Mode, 3, PM_RESC_1, PM_RESC_2, PM_RESC_3);  

*Parameters:*  
powerModeConstraint : The lowest power mode allowed, the power mode constraint macros can be found in fsl_pm_device.h.  
rescNum : The number of resource constraints to be set.   

*Returns:* status_t The status of set constraints behavior.  

<br/>

**status_t PM_ReleaseConstraints (uint8_t  powerModeConstraint, int32_t  rescNum,   ...)**  
Used to release constraints(including power mode constraint and resource constraints) 
For example, if the device support 3 resource constraints: PM_RESC_1, PM_RESC_2, PM_RESC3. PM_ReleaseConstraints(Sleep_Mode, 1, PM_RESC_1);  
 
*Parameters:*  
powerModeConstraint : The lowest power mode allowed, the power mode constraint macros can be found in fsl_pm_device.h.  
rescNum : The number of resource constraints to be released.  

*Returns:* status_t The status of set constraints behavior.  

<br/>

**pm_resc_mask_t PM_GetResourceConstraintsMask (void)**  
Get current system resource constraints.     

*Returns:* Current system constraints.  

<br/>

**uint8_t PM_GetAllowedLowestPowerMode (void)**  
Get current system allowed power mode.     

*Returns:* Allowed lowest power mode.  

<br/>

## 6. Conclusion <a id="conclusion"></a>

<br/>

The Power Manager is a great option to reduce power consumption in low power states by managing all the resources seemlessly for the user. By abstracting the overall power architecture and providing easy-to-use APIs/macros, this framework speedup the time-to-market and application development.
