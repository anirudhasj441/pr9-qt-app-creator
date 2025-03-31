# Qt_project_creator

Qt_project_creator is a CLI tool that helps you quickly set up a new Qt project, similar to create-react-app. It prompts users for a project name, application name, and optional libraries, then generates a Qt project structure with all necessary files.

## Features
- Interactive CLI to gather project details

- Generates a fully configured CMake-based Qt project

- Automatically sets up CMakeLists.txt

- Creates a basic main.cpp file with project initialization

- Generates a basic MainForm class along with a Qt Designer-compatible UI file.

## Prerequisites
- Qt v6.x
- CMake 

## Installation
To install Qt_project_creator globally, clone this repository and build it:
```bash 
git clone https://github.com/anirudhasj441/pr9-qt-app-creator.git
cd pr9-qt-app-creator/src
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make install
```
Now you can use qt_project_creator as a global command.
## Usage
To create a new Qt project, simply run:
```bash
create_qt_app
```

It will prompt you for:
1. Project Name:
1. App Name:
1. Project Type:
1. Would you like to include cds (Y/N):
1. Would you like to include jsoncons (Y/N):
1. Would you like to include qt-qwt (Y/N):


After that, it generates a project directory with the following structure:

```bash
./
├── CMakeLists.txt
└── src
    ├── CMakeLists.txt
    ├── gui
    │   ├── frm_main.cpp
    │   ├── frm_main.h
    │   └── frm_main.ui
    └── main.cpp
```

# Contributing

Contributions are welcome! Feel free to fork the repository and submit a pull request.