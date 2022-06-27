[上一页](../README_CN.md)
# 使用 MCUXpresso SDK
本节帮助您了解当前基础代码库内容，并指导您如何编译和运行应用代码库中的示例应用。

## 基础代码库（中央项目）
基础代码库，又可以称为 west 工作仓库中的中央项目。用户通过west方式获取MCUXpresso SDK所有项目时，该项目的内容会被拉取到工作仓库文件夹 `core` 中。基础代码库包含所有的处理器支持、板级支持、开源的处理器外设驱动程序和一些板级外设驱动的支持。

|文件夹 |说明 |
| :--------- | :-------- |
| boards | 板级支持，提供了板级支持需要的clock配置，板级配置文件还有实例工程所需的模板配置文件 |
| CMSIS | ARM CMSIS 标准头文件和库文件 |
| cmsis_drivers | 符合ARM CMSIS 外设驱动标准的NXP外设驱动实现 |
| components | 软件组件和板级外设驱动 |
| devices | 处理器支持，提供处理器头文件、feature文件、启动文件和编译器需要的链接文件，还包括处理器特定的驱动程序 |
| docs | 文档 |
| drivers | 外设驱动程序 |
| middleware | mmcau 驱动库及一些跟示例工程绑定的中间件，后续会移到对应的中间件项目代码仓库中。 |
| tools | 软件工具 |
| utilities | 应用需要的一些文件 |

## 应用代码库

我们把MCUXpresso SDK软件包中的板级应用程序发布到应用代码库[mcux-sdk-examples](https://github.com/NXPmicro/mcux-sdk-examples)。通过west方式获取SDK所有项目时应用代码库会被拉取到west工作仓库的`examples`文件夹中。

在文件夹 `examples` 中，可以找到支持MCUXpresso SDK 2.9.0以上版本的所有开发板的应用程序，每个开发板的应用放在对应开发板名称的文件夹下。这些应用包括（但不限于）：

* demo_apps：快速上手把开发板驱动起来的示例应用，包括hello_world和led_blinky等示例，全功能的示例应用，展示多个外设组合使用。
* driver_examples：展示如何使用外设驱动程序进行外设配置，实现特定外设功能或数据传输的外设示例。一般只针对单一外设，但也有使用多个外设的情况（例如，使用 DMA 的 SPI 传输。

### 应用程序结构

下面我们使用hello_world作为示例应用（位于demo_apps文件夹）来说明板级应用的组织结构，其他示例应用也有类似的结构。

![示例应用结构](Getting_Started/images/example_structure.png)

### 编译并运行应用程序

* [MCUXpresso IDE 编译和运行示例](run_a_project_using_mcux_CN.md)
* [ARMGCC 编译和运行示例](run_a_project_using_armgcc_CN.md)