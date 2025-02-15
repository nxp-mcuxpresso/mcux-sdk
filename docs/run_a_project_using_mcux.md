[Previous Page](Getting_Started.md)

This section describes the steps required to configure MCUXpresso IDE to build, run, and debug example applications.

# :one:Set up Environment

## 1. Install MCUXpresso IDE
1. Download MCUXpresso IDE from [LINK](https://www.nxp.com/design/software/development-software/mcuxpresso-software-and-tools-/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE?tab=Design_Tools_Tab). 
2. Open MCUXpresso IDE, select workspace location.

    Every time MCUXpresso IDE launches, it prompts the user to select a workspace location. MCUXpresso IDE is built on top of Eclipse which uses workspace to store information about its current configuration, and in some use cases, source files for the projects are in the workspace. The location of the workspace can be anywhere, but it is recommended that the workspace be located outside of the MCUXpresso SDK tree.

# :two:Build an example application
To build an example application, follow these steps. 

The step 1 differs according to the version of MCUXpresso IDE. If you are using MCUXpresso IDE version above 11.5.0, please follow below first step:

1. Right-click the empty space in the **Installed SDKs** view to show the menus, select **Import local SDK Git repository** and input the root folder of west workspace(mcuxsdk), then IDE will be able to recognize all boards support in local GitHub SDK repository.
    ![Import local directory](Getting_Started/images/mcux_import_local_repository.png)
    ![Import local git](Getting_Started/images/mcux_import_local_git_repo.png)
    ![Default manifests core](Getting_Started/images/mcux_default_manifests_core_folder.png)
    ![Local github repositories](Getting_Started/images/mcux_github_repository.png)

As shown in above picture, the default manifests folder chosen by IDE is **core/manifests**, with the setting IDE will list the latest and newest board support in MCUXpresso SDK. If you want to have the full board support(such as FRDM-K64F), please follow below guidance to manually switch to the **examples/manifests** folder:
![Change manifests to examples](Getting_Started/images/mcux_change_manifests_examples_folder.png)
![Manifests examples](Getting_Started/images/mcux_manifests_folder_examples.png)


Else if you are using IDE version older than 11.5.0, you need to refer to below step 1. 

1. Copy the board manifest file from the `examples/manifests` folder to the root folder of west workspace(mcuxsdk) to explore MCUXpresso IDE build and debug for example application of specified board. Then you drag and drop the west workspace into the **Installed SDKs** view to install the MCUXpresso SDK. In the window that
appears, click the **OK** button and wait until the import has finished.

    
        *Take FRDM-K28FA as an example, copy FRDM-K28FA_manifest_v3_8.xml file in `manifests` folder to the repository root directory.*

    ![Install SDK](Getting_Started/images/mcux_install_a_sdk.png)


The other steps for import, build and run an example are same for different IDE versions.

2. On the **Quickstart Panel**, click **Import SDK example(s)….**

    ![Import an SDK example](Getting_Started/images/mcux_import_project.png)
3. In the window that appears, expand the **MIMXRT1020** folder and select **MIMXRT1021xxxxx**. Then, select **evkmimxrt1020** and click the **Next** button.

    ![Selecting EVK-MIMXRT1020 board](Getting_Started/images/mcux_select_rt1020_board.png)

4. Expand the demo_apps folder and select hello_world. Then, click the **Next** button.

    ![Selecting hello_world](Getting_Started/images/mcux_import_example_evkmimxrt1020.png)

    | :exclamation: NOTE | 
    |:-----------------------------------------:| 
    | If you want to use semihost to print log, first select the Semihost button when importing projects.|

    ![Selecting User floating point version of printf](Getting_Started/images/mcux_select_semihost.png)

5. Ensure the option **Redlib: Use floating point version of printf** is selected if the cases print floating point numbers on the terminal (such as mmcau_examples mmcau_api). Otherwise, there is no need to select it. Click the **Finish** button.

    ![Selecting User floating point version of printf](Getting_Started/images/mcux_select_float_number.png)

6. On the **Quickstart** panel, click **build evkmimxrt1020_demo_apps_hello_world [Debug]**.

    ![Building hello world case](Getting_Started/images/mcux_build.png)

# :three:Run an example application
For more information on debug probe support in the MCUXpresso IDE, visit community.nxp.com.

To download and run the application, perform these steps:

| :exclamation: NOTE | 
|:-----------------------------------------:| 
| If you are using our evaluation board which uses flashless soc, please make sure that the board is on QSPI_Flash mode before download. (For EVK-MIMXRT1020 in the example, set t SW8: 0010).|

1. On the **Quickstart** panel, click **Debug evkmimxrt1020_demo_apps_hello_world [Debug]**.

    ![Debugging hello_world case](Getting_Started/images/mcux_debug.png)

2. The first time you debug a project, the Debug Emulator Selection Dialog is displayed, showing all supported probes
that are attached to your computer. Select the probe through which you want to debug and click the **OK** button. (For
any future debug sessions, the stored probe selection is automatically used, unless the probe cannot be found.)

    ![Attached Probes: debug emulator selection](Getting_Started/images/mcux_select_debug_emulator_evkmimxrt1020.png)

3. The application is downloaded to the target and automatically runs to main().

    ![Stop at main() when running debugging](Getting_Started/images/mcux_debug_stop_main_evkmimxrt1020.png)

4. Start the application by clicking the **Resume** button.

    ![Resume button](Getting_Started/images/mcux_debug_go_evkmimxrt1020.png)

The hello_world application is now running and a banner is displayed on the MCUXpresso IDE console window. If this is
not the case, check your terminal settings and connections.

![Text display of the hello_world demo](Getting_Started/images/ide_hello_world_result.png)
