[上一页](Getting_Started_CN.md)

本节介绍配置 MCUXpresso IDE 以编译、运行和调试示例应用程序所需的步骤。

# :one:设置环境

## 1. 安装 MCUXpresso IDE
1. 从[链接](https://www.nxp.com/design/software/development-software/mcuxpresso-software-and-tools-/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE?tab=Design_Tools_Tab)下载MCUXpresso IDE。

2. 打开 MCUXpresso IDE，选择工作区位置。

    在您首次启用MCUXpresso IDE时，系统会要求选择工作区。工作区只是一个用于存储工程项目和数据的文件系统目录，对于新安装，通常应接受推荐的默认位置。如果您勾选了 **“用此作为默认选项，并且不再询问”** 选项，那么MCUXpresso IDE启动时会始终开启所选的工作区；否则，系统会始终提示您选择一个工作区。
    
    建议工作区的位置放在SDK的west工作区目录之外。

## 2. 将选定的开发板清单文件复制到SDK的west工作仓库目录
将选定的开发板清单文件（manifest）从 `examples/manifests` 目录复制到 west 工作仓库 (mcuxsdk) 目录，是开始探索 MCUXpresso IDE 编译和调试GitHub MCUXpresso SDK开发板示例应用的第一步。

*以EVK-MIMXRT1020为例，将位于west工作仓库`examples/manifests`目录下的EVK-MIMXRT1020_manifest_v3_8.xml文件复制到west工作仓库目录。*

# :two: 编译示例应用程序
要编译示例应用程序，请按照以下步骤操作。
1. 将west工作仓库目录直接拖拽到 **Installed SDKs** 视图开始 MCUXpresso SDK的加载安装。在识别窗口跳出后，单击**OK** 按钮并等待加载完成，安装完成后的EVK-MIMXRT1020开发板SDK会显示在**Installed SDKs** 区域。

    ![安装SDK](Getting_Started/images/mcux_install_a_sdk.png)
2. 在 **Quickstart Panel** 上，单击 **Import SDK example(s)....**来导入开发板SDK。

    ![导入 SDK 示例](Getting_Started/images/mcux_import_project.png)
3. 在出现的窗口中，展开 **MIMXRT1020** 文件夹并选择 **MIMXRT1021xxxxx**。然后，选择 **evkmimxrt1020** 并单击 **下一步** 按钮。此时EVK-MIMXRT1020开发板SDK上所有的示例程序会被展示在**Examples**视图中。

    ![选择EVK-MIMXRT1020板](Getting_Started/images/mcux_select_rt1020_board.png)

4. 展开 demo_apps 文件夹并选择 hello_world。然后，单击**下一步** 按钮。

    ![选择hello_world](Getting_Started/images/mcux_import_example_evkmimxrt1020.png)

    | :exclamation: 注意 | 
    |:-----------------------------------------:|
    |如果要使用semihost方式打印日志，导入工程时先选择Semihost按钮。|

    ![选择Semihost打印](Getting_Started/images/mcux_select_semihost.png)

5. 如果希望示例程序打印浮点数（例如 mmcau_examples mmcau_api），请确保在 Advanced Projects 设置中勾选 **Redlib: Use floating point version of printf** 选项，不需要则无需勾选。单击**完成**按钮。

    ![选择支持浮点数的printf](Getting_Started/images/mcux_select_float_number.png)

6. 选中示例程序evkmimxrt1020_demo_apps_hello_world，在**Quickstart Panel** 单击 **build**。

    ![编译hello world案例](Getting_Started/images/mcux_build.png)

    编译完成后，控制台会显示“build finished”。
# :three:运行示例应用程序
MCUXpresso IDE支持本地LinkServer（包括CMSIS-DAP），P&E Micro， SEGGER J-Link等调试器，更多相关信息可以查看[MCUXpresso IDE用户指南](https://www.nxp.com/docs/zh/user-guide/MCUXpresso_IDE_User_Guide.pdf)。

要下载并运行该应用程序，请执行以下步骤：

| :exclamation: 注意 | 
|:-----------------------------------------:|
|如果您使用的开发板集成的是flashless（无内置NVM）的MCU，请在下载前确保开发板处于 QSPI_Flash 模式。（对于示例中的 EVK-MIMXRT1020，设置 t SW8：0010）。|

1. 选中你要示例程序evkmimxrt1020_demo_apps_hello_world，在**Quickstart Panel** 单击 **Debug**。

    ![调试hello_world案例](Getting_Started/images/mcux_debug.png)

2. 第一次调试项目时，会显示 “Debug Emulator Selection” 对话框，检测当前连接到计算机的调试器。选择使用的调试器，然后单击 **确定** 按钮，下图选择板载的CMSIS-DAP调试器。IDE会为当前调试生成一个调试配置，然后启动调试会话。（选择的调试器将作为调试会话默认使用的配置，除非调试连接过程中发现找不到该调试器。）

    ![调试器选择](Getting_Started/images/mcux_select_debug_emulator_evkmimxrt1020.png)

3. 接下来示例应用程序会被下载到开发板并自动运行到main()处停止，可以根据自己的喜好添加断点进行调试。

    ![运行调试时在 main() 处停止](Getting_Started/images/mcux_debug_stop_main_evkmimxrt1020.png)

4. 单击**继续**按钮启动应用程序。

    ![继续按钮](Getting_Started/images/mcux_debug_go_evkmimxrt1020.png)

hello_world 应用程序现在正在运行，并且在 MCUXpresso IDE 控制台（选择Semihost打印）或者终端（选择UART打印）上显示了“hello world”。 如果不是这种情况，请检查您的终端设置和连接。

![hello_world 演示文本显示](Getting_Started/images/ide_hello_world_result.png)