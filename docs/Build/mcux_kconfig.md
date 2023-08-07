MCUX SDK provides plentiful drivers, the MCUX SDK Kconfig framework can:
1. Show what drivers are available for one board or one SOC.
1. Analyze the drivers dependency, pick the required drivers automatically when you adding some drivers to your project.

## File structure

There are Kconfig files for drivers, SOCs, and boards. The structure is like:
```
mcux-sdk
+-- Kconfig
+-- arch
|   +-- Kconfig
|   +-- arm
|       +-- Kconfig
|
+-- boards
|   +-- Kconfig
|   +-- evkbimxrt1050
|   |   +-- Kconfig
|   |   +-- Kconfig.board
|   +-- evkmimxrt1060
|   |   +-- Kconfig
|   |   +-- Kconfig.board
|   +-- ...
|
+-- devices
|   +-- Kconfig
|   +-- MIMXRT1052
|   |   +-- Kconfig
|   |   +-- drivers
|   |       +-- Kconfig
|   +-- MIMXRT1062
|   |   +-- Kconfig
|   |   +-- drivers
|   |       +-- Kconfig
|   +-- ...
|
+-- drivers
|   +-- Kconfig
|   +-- adc
|   |   +-- Kconfig
|   +-- uart
|   |   +-- Kconfig
|   +-- ...
|
+-- components
|   +-- Kconfig
|   +-- serial_manager
|   |   +-- Kconfig
|   +-- lists
|   |   +-- Kconfig
|   +-- ...
|
+-- utilities
|   +-- Kconfig
|
+-- CMSIS
|   +-- Kconfig
|
+-- cmsis_drivers
    +-- Kconfig
    +-- i2c
    |   +-- Kconfig
    +-- uart
    |   +-- Kconfig
    +-- ...

```

### Root folder Kconfig file

The Kconfig file in *mcux-sdk* root folder is the MCUX SDK Kconfig's entry, it reads the other Kconfig files in each folder.
```
mainmenu "MCUX SDK Configuration"

rsource "./boards/Kconfig"
rsource "./arch/Kconfig"
rsource "./devices/Kconfig"
rsource "./drivers/Kconfig"
rsource "./components/Kconfig"
rsource "./utilities/Kconfig"
```

### Driver components Kconfig file

Kconfig files in *drivers*, *components*, *cmsis_drivers*, *utilities* and so on.

In MCUX SDK, each software entity is a building block, or a software component. For example, LPUART driver, serial manager, and CMSIS USART driver's implementation on LPUART driver are all software components. Each software component has two Kconfig variables: `MCUX_HAS_foo` and `MCUX_USE_foo`. Variable `MCUX_HAS_foo` indicates whether the component `foo` is available, variable `MCUX_USE_foo` indicates whether the component `foo` will be used in the project. Obviously, `MCUX_USE_foo` depends on `MCUX_HAS_foo`. Meanwhile, the Kconfig file specifies the components which are required by component `foo`.

Take driver lpuart and driver lpuart_edma as example (in file *mcux-sdk/drivers/lpuart/Kconfig*)
```
# driver_lpuart
config MCUX_HAS_driver_lpuart
    bool

config MCUX_USE_driver_lpuart
    depends on MCUX_HAS_driver_lpuart
    bool "LPUART Driver"
    select MCUX_USE_driver_common

# driver_lpuart_edma
config MCUX_HAS_driver_lpuart_edma
    bool

config MCUX_USE_driver_lpuart_edma
    depends on MCUX_HAS_driver_lpuart_edma
    bool "LPUART Edma Driver"
    select MCUX_USE_driver_lpuart
```
In the example, driver_lpuart requires driver_common; driver_lpuart_edma requires driver_lpuart. When driver_lpuart_edma is selected, then driver_lpuart will be selected automatically. Why `MCUX_USE_driver_lpuart_edma` doesn't select `MCUX_USE_driver_edma` is explained in section [SOC Kconfig file](#soc-kconfig-file)


### SOC Kconfig file

Kconfig file in folder *devices*. It contains such information:
1. SOC information, such as core architecture, part number, device name, device ID.

        config MCUX_USE_SOC_MIMXRT1052
            bool
            select MCUX_CPU_ARCH_ARM_CM7F
            select MCUX_CPU_HAS_DP_FPU

        if MCUX_USE_SOC_MIMXRT1052

        config MCUX_SOC_PART_MIMXRT1052xxxxB
            bool

        config MCUX_DEVICE
            default "MIMXRT1052"

        config MCUX_DEVICE_ID
            default "MIMXRT1052xxxxB" if MCUX_SOC_PART_MIMXRT1052xxxxB

        endif
    
2. The software component availability. For example RT1052 support lpuart driver, then `MCUX_HAS_driver_lpuart` will be selected by *devices/MIMXRT1052/Kconfig*:

        config MCUX_USE_SOC_MIMXRT1052
            select MCUX_HAS_driver_lpuart

3. SOC specific component dependency. In previous driver_lpuart_edma example, driver_lpuart_edma can select driver_edma or driver_dma3. Which one will finally be selcted depends on SOC feature. RT1052 has driver_edma, but not driver_dma3, so *devices/MIMXRT1052/Kconfig* define the dependency like:

        config MCUX_USE_driver_lpuart_edma
            bool
            select MCUX_USE_driver_edma

4. SOC specific drivers, such as clock driver, iomuxc driver.

To use a specific SOC, SOC name and part number shall be specified by selecting Kconfig variables `MCUX_USE_SOC_<SOC>` and `MCUX_SOC_PART_<PART_NUMBER>`. 


### Board Kconfig file

Kconfig file in folder *boards*. There are two types files:
1. *Kconfig.board* which selects SOC and part number
2. *Kconfig* which defines board name, and board level software components.

### Arch Kconfig file

The Kconfig files in folder *arch*. They define the core architecture information, such as architecture name, FPU, DSP features.


## Integration with your Kconfig

MCUX SDK Kconfig files are modularized so you can pick what you want. There are some examples:


### Only use the low level drivers

If only low level drivers needed, and `boards`, `components`, `cmsis_drivers`, and `utilities` are not needed, your project Kconfig file can be like this:
```
# your project Kconfig file (example for MIMXRT1052)

# Select the SOC and part number
config USE_MIMXRT1052
    select MCUX_USE_SOC_MIMXRT1052
    select MCUX_SOC_PART_MIMXRT1052xxxxB

rsource "./mcux-sdk/arch/Kconfig"
rsource "./mcux-sdk/devices/Kconfig"
rsource "./mcux-sdk/drivers/Kconfig"
rsource "./CMSIS/Kconfig"
```

### Use your own CMSIS copy

ARM CMSIS repository is a fundamental part for ARM projects, so your project may have its own CMSIS copy, and MCUX SDK's CMSIS is not needed. Then in your project Kconfig file, *./CMSIS/Kconfig* is not needed, like this:
```
# your project Kconfig file (example for MIMXRT1052)

# Select the SOC and part number
config USE_MIMXRT1052
    select MCUX_USE_SOC_MIMXRT1052
    select MCUX_SOC_PART_MIMXRT1052xxxxB

rsource "./mcux-sdk/arch/Kconfig"
rsource "./mcux-sdk/devices/Kconfig"
rsource "./mcux-sdk/drivers/Kconfig"
```

