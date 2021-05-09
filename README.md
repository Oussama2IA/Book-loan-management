# Book loan management
> This project is about implementing a book loan management application with **C** using **GTK+ 3**

# Screenshots

# GTK+ 3.0 instalation
## Linux instalation
- Run the following commands: (for ubuntu)
  - sudo apt update (update packages list)
  - sudo apt install build-essential (install gcc and other tools)
  - sudo apt install snapd (install snap to insatll camke)
  - sudo snap install cmake (install cmake)
   -sudo apt-get install libgtk-3-dev (install GTK+ 3.0)
## Windows instalation
- Download and install msys2 from [https://www.msys2.org/](https://www.msys2.org/)
- Open start menu and open the msys2 terminal (**MSYS2 MinGW 64-bit**)
- Run the following commands: (for 64 bit systems)
  - pacman -Syu (update the package database and base packages)
  - pacman -Su (update the rest of the base packages)
  - pacman -S --needed base-devel mingw-w64-x86_64-toolchain (install gcc and other tools)
  - pacman -S mingw-w64-x86_64-cmake (install cmake)
  - pacman -S pacman -S mingw-w64-x86_64-gtk3 (install GTK+ 3.0)

# Build the project
## Linux
- [x] Open terminal and go to projet's directory, then go to build (by typing ***cd project_diretory/build***)
- [x] Run the command ***cmake ..***
- [x] Now run the command ***make***
## Windows
- [x] Open terminal and go to projet's directory, then go to build (by typing ***cd project_diretory/build***)
- [x] Run the command ***cmake -DCMAKE_C_COMPILER="gcc.exe" -DCMAKE_CXX_COMPILER="g++.exe" -G "MinGW Makefiles" ..***
- [x] Now run the command ***cmake --build .*** (**the point in the end is important**)
