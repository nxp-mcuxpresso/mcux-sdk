[上一页](Getting_Started_CN.md)

本节介绍了配置命令行 Arm® GCC 工具来编译、运行和调试 MCUXpresso SDK 中提供的应用程序的步骤。以位于 examples/{board_name}/demos_apps/hello_world/ 中的 hello_world 为例进行演示，但这些步骤适用于所有开发板、演示或示例应用。

# :one:设置工具链
本章节包含利用MCUXpresso SDK支持的ARM GCC工具链编译和运行示例应用程序时安装所需必要组件的步骤。可以通过多种方式使用ARM GCC工具，本示例重点介绍Windows操作系统环境。尽管未在此处讨论，但ARM GCC工具也可在Linux OS和Mac OSX中使用。

## 1. 安装 GCC ARM Embedded 工具链
从launchpad.net/gcc-arm-embedded 处下载和运行安装程序。这是实际的工具箱（即编译器、链接器等）。GCC工具链应与SDK支持的最新版本对应，版本请参考[工具版本](./../README_CN.md#支持的开发工具和硬件)。

## 2. 安装 MinGW（仅在 Windows 操作系统上需要）
Minimalist GNU for Windows (MinGW)开发工具提供了一组独立于第三方C运行时DLL（如Cygwin）的工具。KSDK使用的编译环境不使用MinGW编译工具，但使用MinGW和MSYS的基础安装。MSYS可提供带类Unix接口和工具的基础Shell。
1. 从 sourceforge.net/projects/mingw/files/Installer/ 处下载最新的MinGW mingw-get-setup安装程序。
2. 运行此安装程序。建议的安装路径为：C:\MinGW，但您也可以安装到其他位置。但请注意安装路径不能包含任何空格。
3. 确保在 **“Basic Setup”** 下选择了 **“mingw32-base”** 和 **“msys-base”**。

    ![设置 MinGW 和 MSYS](Getting_Started/images/armgcc_install_mingw_select_component.png)

4. 在**安装**菜单中，单击**“Apply Changes”**并按照剩下的说明完成安装。

    ![完成MinGW和MSYS安装](Getting_Started/images/armgcc_install_mingw_applychange.png)

5. 为Windows操作系统路径环境变量添加相应项。该项可以通过控制面板 -> 系统和安全 -> 系统 -> 高级系统设置“环境变量...”部分获取。路径如下：

   <mingw_install_dir>\bin

   假设默认安装路径为C:\MinGW，示例如下所示。如果路径未设置正确，则工具链不会工作。

    | :exclamation: 注意事项 |
    |:-----------------------------------------:|
    |如果您的 PATH 变量中有 C:\MinGW\msys\x.x\bin（根据 Kinetis SDK 1.0.0 的要求），请将其删除以确保新的 GCC 编译系统正常工作。|

    ![为系统环境添加路径](Getting_Started/images/armgcc_install_mingw_addpath.png)

## 3.为**ARMGCC_DIR**添加一个新的系统环境变量
创建新的系统环境变量并将其命名为ARMGCC_DIR。此变量值应指向ARM GCC Embedded工具链安装路径，对本示例来说为：

C:\Program Files (x86)\GNU Tools ARM Embedded\8 2018-q4-major

请参考GNU ARM GCC Embedded工具的安装文件夹，获取准确的安装路径名称。
    
如果路径中带有空格，需要**使用短路径进行环境设置**，您可以通过在上述路径中运行命令“for %I in (.) do echo %~sI”将带有空格的长路径转换为短路径。

![将路径转换为短路径](Getting_Started/images/armgcc_install_armgcc_cvt_path.png)

![添加ARMGCC_DIR系统变量](Getting_Started/images/armgcc_add_dir.png)

## 4. 安装 CMake
1. 从 www.cmake.org/cmake/resources/software.html 下载 CMake 3.0.x。
2. 安装CMake，确保安装时勾选**Add CMake to system PATH**。将由用户决定是将其安装到供所有用户使用的路径下还是仅供当前用户使用的路径下。在本示例中，假定将其安装到供所有用户使用的路径下。

![安装 CMake](Getting_Started/images/armgcc_install_cmake.png)

3. 请按照安装程序剩下的说明进行操作。
4. 您可能需要重新启动系统以使系统路径更改生效。
5. 请确保 sh.exe 不在环境变量 PATH 中。这是 mingw32-make 的限制。

# :two: 编译示例应用程序

- 打开命令行工具，将目录更改到示例程序的目录：

   <west_workspace>/examples/<board_name>/demos_apps/hello_world/armgcc 文件夹
- 示例工程支持至少两种工程配置（编译目标），以下以debug（调试）和release（发布）为例进行讲解：
   - 调试（debug）– 编译优化设为低，并且将为可执行文件生成调试信息。此目标应被选择用于开发和调试。
   - 发布（Release） – 编译优化设为高，并且不会生成调试信息。此目标应被选择用于最终应用部署。提供的批处理文件用于编译两种配置。
   
   对于本示例，编译的是“Debug”目标，在命令行上键入“build_debug.bat”。如果需要的是“Release”目标，则键入“build_release.bat”。或者，如果无需使用命令行，则您可以在Windows操作系统资源管理器中双击批处理文件。

# :three:运行示例应用程序
本章节介绍了使用J-Link GDB服务器应用运行演示应用的步骤。要执行此练习，必须完成以下两项操作：
  - 安装J-Link软件（驱动程序和实用程序），可从www.segger.com/downloads.html 中下载。
  - 请确保：
    - 已使用J-Link OpenSDA固件将开发板上的OpenSDA接口编程。如果您的开发板不支持OpenSDA，则需要使用单独的J-Link pod。
    - 您需将单独的J-Link pod连接至板的调试接口。

| :exclamation: 注意 | 
|:-----------------------------------------:|
|某些硬件平台需要硬件修改才能使用外部调试接口正常运行。|

配置和连接J-Link接口之后，请按照以下步骤下载和运行演示应用：
1. 使用前请安装SEGGER软件，可从以下网址下载http://www.segger.com。
2. 通过OpenSDA USB连接器（在部分开发板上可能名为OSJTAG）与PC USB连接器之间的USB线缆将开发平台与PC相连。如果使用单独的J-Link调试pod，请同时将其连接至开发板的SWD/JTAG连接器。
3. 打开PC上的终端应用，例如PuTTY或TeraTerm，然后连接至调试串行端口号。将终端配置为以下设置：
    - 115200或9600波特率，具体取决于开发板（请参考board.h文件中的BOARD_DEBUG_UART_BAUD变量）
    - 无校验
    - 8 个数据位
    - 1 个停止位

    ![终端（PuTTY）配置](Getting_Started/images/putty_configuration.png)

4. 打开 J-Link GDB 服务器应用程序。假定已安装J-Link软件，转到 SEGGER 安装文件夹。例如，C:\Program Files (x86)\SEGGER\JLink_Vxxx。
    - 打开命令窗口。
    - 对于debug、release、flash_debug、flash_release等工程配置，运行命令
    ``` JLinkGDBServer.exe```
    - 对于 sdram_debug、sdram_release、flexspi_nor_sdram_debug 和 flexspi_nor_sdram_release 工程配置，运行命令
    ```JLinkGDBServer.exe -scriptfile <west_workspace>/examples/{board_name}/demo_apps/hello_world/{board_name}_sdram_init.jlinkscript```。
5. 为开发板选择目标处理器。以evkmimxrt1024为例，选择处理器MIMXRT1024xxx5A。
6. 连接后，屏幕应与下图类似：

    ![连接成功后的SEGGER J-Link GDB服务器画面](Getting_Started/images/armgcc_debug_jlink_gdbserver.png)

7. 如果尚未运行，请打开 GCC ARM Embedded 工具链命令窗口。要启动窗口，从Windows 操作系统 **“开始”**菜单中，转至 **“程序 -> GNU 工具 ARM Embedded <版本>”** 并选择 **GCC Command Prompt**。

    ![GCC Command Prompt](Getting_Started/images/armgcc_debug_jdbserver_launch.png)

8. 更改包含演示应用输出的目录。可使用以下路径之一找到输出，具体取决于选择的编译目标：
    *<west_workspace>/examples/<board_name>/<example_type>/<application_name>/armgcc/<build_target>*

    对于这个例子，路径是：
    *<west_workspace>/examples/evkmixrt1024/demo_apps/hello_world/armgcc/debug*
9. 运行命令“arm-none-eabi-gdb.exe <demo_name>.elf”。对于本示例，请运行“arm-none-eabi-gdb.exehello_world.elf”:

    ```arm-none-eabi-gdb.exe <west_workspace>/examples/evkmixrt1024/demo_apps/hello_world/armgcc/debug/hello_world.elf```。

    ![运行 arm-none-eabi-gdb](Getting_Started/images/armgcc_debug_launch_result.png)

10. 运行以下命令：
    - `target remote localhost:2331`
    - `monitor reset`
    - `monitor halt`
    - `load`
    - `monitor reset`
11. 此应用现已下载完毕并在复位向量处停止。执行“monitor go”命令以启动此演示应用。hello_world应用现在正在运行且终端上显示。否则，请检查您的终端设置和连接。

    ![hello_world 演示文本显示](Getting_Started/images/ide_hello_world_result.png)