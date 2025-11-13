# Microprocessors & Microcontrollers (CO3010) — Lab Repository

This repository contains the lab materials, source code and schematics for the Microprocessors & Microcontrollers (CO3010) course. Projects target the STM32F103 (Blue Pill / Value line) family and are organised by lab number.

## Contents
- `LAB 1/`, `LAB 2/`, `LAB 3/`, `LAB 4/`, `LAB 5/`, ... : Top-level lab folders.
  - Each lab folder contains:
    - `Code/` — STM32CubeIDE projects and generated source (`Core/`, `Drivers/`, `Debug/`).
    - `*.ioc` — STM32CubeMX project configuration for the lab (open with STM32CubeIDE).
    - `STM32F103C6UX_FLASH.ld` — linker script used by the projects.
  - `Schematic/` folders contain Proteus (or other) schematic files and backups for the corresponding lab exercises.

## Quickstart
Prerequisites:
- STM32CubeIDE (recommended) or STM32CubeMX + toolchain
- ST-Link hardware (or other programmer/debugger)

To open a lab project:
1. Start STM32CubeIDE.
2. In the IDE choose `File -> Open Projects from File System...` and point to the lab's `Code/` folder, or simply double-click the `*.ioc` file inside the lab `Code/` folder to open the CubeMX configuration and generate code.
3. Build using the IDE build button, then use the debugger with ST-Link to flash and run on hardware.

Notes on structure:
- Example: `LAB 1/Code/LAB 1.1/` contains the project for lab 1.1 with an `LAB 1.1.ioc` CubeMX file and the generated `Core`, `Drivers`, and `Debug` folders.
- Schematic files for each exercise are in `Schematic/` under subfolders like `ex 1/`, `ex 2/`, etc.

Development tips:
- If you modify `.ioc` settings, regenerate the code from CubeMX and re-build in the IDE.
- Keep backups of custom code you add under separate source files (do not rely only on generated code blocks).

Repository conventions:
- Lab folders are named `LAB X` and may contain multiple sub-exercises (e.g., `LAB 1.1`, `LAB 1.2`, ...).
- Always test flashing and debug on hardware when possible — behaviour in the simulator may differ from the real microcontroller.

Contact
- If you have questions or need corrections, open an issue in the repository or contact the course instructor / TA for guidance.

License
- Course materials: check with the course instructor for reuse permissions. No explicit license file is provided in this repository.

--
Generated: README for the CO3010 lab workspace.
