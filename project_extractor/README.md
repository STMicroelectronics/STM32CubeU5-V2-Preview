# Project_Extractor

## General

The Project Extractor is an utility to extract an example project from this repository to a standard project format, which in this case can be used with STM32Cube for Visual Studio Code.

## Usage

Call the extractor script from the root of this repository (e.g. `./project_extractor/projectExtractor.exe`)

	The project extractor requires the following parameters:
	-p, --projectName <PROJECT>  The name of the project to be extracted
	-b, --boardName <BOARD>      The name of the target board
	-f, --format <FORMAT>        The IDE Name. Currently supported formats: EWARM, Open-CMSIS, CMAKE
	-o, --projectDir <DIR>       The location where to extract the project

- The project name is of the folder where the example is located (e.g. exit, full_duplex_two_boards_com_it_controller, pwm_output).
- The board name is the name of the board to run the example on (for this release it is NUCLEO-U575ZI-Q).
- The format in this case is CMAKE, which is the format used by STM32Cube for Visual Studio Code.
- The project directory is the location where the project will be extracted to (e.g. C:\STM32U5_Preview_projects)
	
Example:
    
	C:\STM32Cube5_Preview> .\project_extractor\project_extractor.exe --projectName trigger_timer_dma --boardName NUCLEO-U575ZI-Q --format cmake --projectDir C:\STM32Cube5_Preview_Examples


 ### Troubleshooting

If you encounter issues with the extraction, an overview of the examples and related project extractor commands can be found in the [Example catalog](https://dev.st.com/stm32cube-docs/examples/1.0.0-beta.1.0/docs/markup/more/examples-catalog.html)
