# GPRSerialTestSender

## Overview

GPRSerialTestSender is a Windows C++ application designed to send test data over a serial port. It is intended for use in FLL team 65226 Lego Dynamics' Innovation Project for the 2025-2026 season UNEARTHED, providing a simple interface for serial communication testing and debugging for the Perlin noise renderer..

## Features

- Serial port communication
- Test data sending functionality
- Windows GUI (icon and resource files included)
- Easy integration with other FLL robotics software

## Project Structure

- `GPRSerialTestSender.cpp` / `.h`: Main application source and header
- `framework.h`, `targetver.h`: Windows framework and target version headers
- `Resource.h`, `.ico`, `.rc`: Resource files for icons and UI
- `GPRSerialTestSender.sln`, `.vcxproj`, `.filters`, `.user`: Visual Studio solution and project files

## Building

1. Open `GPRSerialTestSender.sln` in Visual Studio 2022.
2. Build the solution (Ctrl+Shift+B).
3. The executable will be located in `x64/Debug/GPRSerialTestSender.exe`.

## Usage

1. Run the compiled executable.
2. Select the desired serial port and configure settings as needed.
3. Send test data to the connected device.

## Requirements

- Windows 10 or later
- Visual Studio 2022 or later (for building)

## License

This project is intended for educational and non-commercial use in FLL Innovation projects, or whatever you choose to do with it.

## Author

Arcmyx
