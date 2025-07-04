# Getting started with Cube Software Examples

## STM32Cube for Visual Studio Code extension

The examples projects in this preview delivery are intended to be used with the Visual Studio Code and the STM32Cube for Visual Studio Code extension
The extension can be found here [STM32Cube for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=stmicroelectronics.stm32-vscode-extension&ssr=false#review-details)

> [!NOTE]  
> The examples are compatible with version 3.0.0 and later of the STM32Cube for Visual Studio Code extension, currently in preview.

## Extracting Examples projects

With the new structure of our examples, a shift in the way examples is being used are introduced.
Interacting with examples directly through the projects in the repository is no longer the recommended way to go.
When working with examples through the repository, a new utility, called project_extractor, is introduced.
The purpose of the project_extractor, is to extract a selected example along with the required resources into a standalone project structure.

How to use the project_extractor utility can be found in the [project_extractor](./../project_extractor/README.md).

## Preparing the examples in STM32CubeIDE for VS Code

After extracting the example project, open the app folder in VS Code

![Opening app folder in VS Code](./_images/vscode_open_app_folder.png)

Go to STM32Cube VS Code extension through the STM32 icon in the left side panel

![The STM32 icon located in the side panel](./_images/STM32Cube_Sidebar.png)

To set up the example in STM32Cube VS Code, click on the "Setup STM32Cube project(s)" button under STM32CUBE KEY ACTIONS

![Setup STM32Cube project(s) button](./_images/setup_stm32cube_project.png)

In the Board/Device selection dialog, search for U575 and select the NUCLEO-U575ZI-Q board

![Board/Device selection dialog](./_images/select_board.png)

Leave GCC as the setting for Toolchain and click on the "Configure" button

![Toolchain selection and configuration](./_images/toolchain_and_configure.png)

When profile options are presented, select the "release_GCC_NUCLEO_U575ZI_Q" profile

![Profile selection dialog](./_images/profile_selection.png)

Let CMAKE prepare the project and when finished, press the save and close option that appears

![Save and close button](./_images/save_and_close.png)

You should now be able to build the project by pressing the build button in the bottom bar of the VS Code window

![Build button in the bottom bar](./_images/build_button.png)

## Debugging the example

To improve the debugging experience and enable step-by-step debugging, the compiler flags need to be changed from "-Os" to "-O0 -g3".
This is done by editing the CMakeLists.txt file in the app folder.

Select the Explorer view in VS Code, and open the CMakeLists.txt file

![CMakeLists.txt file in the Explorer view](./_images/cmakelists_explorer.png)

In the CMakeLists.txt file, find the line that starts with target_compile_options and contains "-Os" (Use control-F and search for "-Os", there can be multiple lines starting with target_compile_options)

![Target compile options in CMakeLists.txt](./_images/target_compile_options.png)

Change the "-Os" to "-O0 -g3"

![Change -Os to -O0 -g3](./_images/change_os_to_o0_g3.png)

Save the CMakeLists.txt file, and then rebuild the project by pressing the Build button in the bottom bar of the VS Code window again.

![Rebuild button in the bottom bar](./_images/rebuild_button.png)

To start debugging, go to the Run and Debug view in VS Code by clicking on the Run and Debug icon in the left side panel.

![Run and Debug button](./_images/run_and_debug.png)

Then click on the "create a launch.json file" link to create a new launch configuration.

![Create launch.json file link](./_images/create_launch_json.png)

The "Select debugger" dialog will appear, select "STM32Cube: STLink GDB Server" from the list.

![Select debugger dialog](./_images/select_debugger.png)

A new launch.json file will be created in the .vscode folder, and the configuration will be set up for debugging with the STLink GDB server.

![Launch.json file created](./_images/launch_json_created.png)

You should now be able to press "Start Debugging" to debug the example project step-by-step.

![Debugging the example project](./_images/debugging_example_project.png)

![Running example in debug](./_images/running_example_in_debug.png)
