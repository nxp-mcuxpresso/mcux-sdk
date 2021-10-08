[上一页](../README_CN.md)
# 使用 MCUXpresso SDK
本节帮助您了解当前基石项目内容，并指导您如何编译和运行基于当前基石项目的示例项目。

## 基石（中央）项目
基石项目，又可以称为 west 工作仓库中的中央项目。用户通过west方式获取MCUXpresso SDK所有项目时，该项目的内容会被拉取到工作仓库文件夹 `core` 中。基石项目包含所有的处理器支持、板级支持、开源的处理器外设驱动程序和一些板级外设驱动的支持。

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

## 示例项目

我们把MCUXpresso SDK软件包中板级示范例程发布到示例项目[mcux-sdk-examples](https://github.com/NXPmicro/mcux-sdk-examples)代码仓库。通过west方式获取SDK所有项目时示例项目会被拉取到west工作仓库的`examples`文件夹中。

在文件夹 `examples` 中，可以找到支持MCUXpresso SDK 2.9.0以上版本的所有开发板的示范例程，每个开发板的示例放在对应开发板名称的文件夹下。这些示例包括（但不限于）：

* demo_apps：快速上手把开发板驱动起来的示范程序，包括hello_world和led_blinky等示例。
* driver_examples：展示如何使用外设驱动程序进行外设配置，实现特定外设功能或数据传输的外设示例。一般只针对单一外设，但也有使用多个外设的情况（例如，使用 DMA 的 SPI 传输。

### 示例结构

下面我们使用hello_world示例（位于demo_apps文件夹）来说明示例组织结构，其他示例也有类似的结构。

![示范例程结构](Getting_Started/images/example_structure.png)

### 编译并运行示例应用程序

* [MCUXpresso IDE 编译和运行示例](run_a_project_using_mcux_CN.md)
* [ARMGCC 编译和运行示例](run_a_project_using_armgcc_CN.md)