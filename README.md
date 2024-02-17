# Auto Picture Puzzle <br> Create an interactive sliding picture puzzle from any image. <br> Written in C++ with [Raylib](https://www.raylib.com/).

 
- Overview:
  - Compilation:  
    - [Linux](#compilation-linux)
    - [Windows](#compilation-windows)

## Compilation (Linux)
### Install Raylib's dependencies
(Source: https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)
```
#Ubuntu 
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev

#Fedora
sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic

#Arch Linux
sudo pacman -S alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama
```
### Clone the Raylib repo
```
git clone https://github.com/raysan5/raylib.git
```

### Edit CMakeOptions.txt to support more image formats
#### Then, navigate to the source folder's CMakeOptions.txt, and find the following lines

<details>
<summary> Original CMakeOptions.txt section from the Raylib repo: </summary> 
(Source: https://github.com/raysan5/raylib/blob/master/CMakeOptions.txt)
  
```
# rtextures.c
cmake_dependent_option(SUPPORT_IMAGE_EXPORT "Support image exporting to file" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_IMAGE_GENERATION "Support procedural image generation functionality (gradient, spot, perlin-noise, cellular)" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_IMAGE_MANIPULATION "Support multiple image editing functions to scale, adjust colors, flip, draw on images, crop... If not defined only three image editing functions supported: ImageFormat(), ImageAlphaMask(), ImageToPOT()" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_PNG "Support loading PNG as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_DDS "Support loading DDS as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_HDR "Support loading HDR as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_PIC "Support loading PIC as textures" ${OFF} CUSTOMIZE_BUILD OFF)
cmake_dependent_option(SUPPORT_FILEFORMAT_PNM "Support loading PNM as textures" ${OFF} CUSTOMIZE_BUILD OFF)
cmake_dependent_option(SUPPORT_FILEFORMAT_KTX "Support loading KTX as textures" ${OFF} CUSTOMIZE_BUILD OFF)
cmake_dependent_option(SUPPORT_FILEFORMAT_ASTC "Support loading ASTC as textures" ${OFF} CUSTOMIZE_BUILD OFF)
cmake_dependent_option(SUPPORT_FILEFORMAT_BMP "Support loading BMP as textures" ${OFF} CUSTOMIZE_BUILD OFF)
cmake_dependent_option(SUPPORT_FILEFORMAT_TGA "Support loading TGA as textures" ${OFF} CUSTOMIZE_BUILD OFF)
cmake_dependent_option(SUPPORT_FILEFORMAT_JPG "Support loading JPG as textures" ${OFF} CUSTOMIZE_BUILD OFF)
cmake_dependent_option(SUPPORT_FILEFORMAT_GIF "Support loading GIF as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_QOI "Support loading QOI as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_PSD "Support loading PSD as textures" ${OFF} CUSTOMIZE_BUILD OFF)
cmake_dependent_option(SUPPORT_FILEFORMAT_PKM "Support loading PKM as textures" ${OFF} CUSTOMIZE_BUILD OFF)
cmake_dependent_option(SUPPORT_FILEFORMAT_PVR "Support loading PVR as textures" ${OFF} CUSTOMIZE_BUILD OFF)
cmake_dependent_option(SUPPORT_FILEFORMAT_SVG "Support loading SVG as textures" ${OFF} CUSTOMIZE_BUILD OFF)
```
</details>

Replace all instances of "OFF" with "ON" here, to allow for every image file type raylib supports. **Do not avoid this step, it is the most important.**

<details> 
<summary> Desired CMakeOptions.txt section for easy copy and pasting: </summary> 
  
```
# rtextures.c
cmake_dependent_option(SUPPORT_IMAGE_EXPORT "Support image exporting to file" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_IMAGE_GENERATION "Support procedural image generation functionality (gradient, spot, perlin-noise, cellular)" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_IMAGE_MANIPULATION "Support multiple image editing functions to scale, adjust colors, flip, draw on images, crop... If not defined only three image editing functions supported: ImageFormat(), ImageAlphaMask(), ImageToPOT()" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_PNG "Support loading PNG as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_DDS "Support loading DDS as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_HDR "Support loading HDR as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_PIC "Support loading PIC as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_PNM "Support loading PNM as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_KTX "Support loading KTX as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_ASTC "Support loading ASTC as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_BMP "Support loading BMP as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_TGA "Support loading TGA as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_JPG "Support loading JPG as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_GIF "Support loading GIF as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_QOI "Support loading QOI as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_PSD "Support loading PSD as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_PKM "Support loading PKM as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_PVR "Support loading PVR as textures" ON CUSTOMIZE_BUILD ON)
cmake_dependent_option(SUPPORT_FILEFORMAT_SVG "Support loading SVG as textures" ON CUSTOMIZE_BUILD ON)
```
</details>

### Build and install Raylib
```
#Generate the build files

mkdir build
cd build

#This will build a *static* library.
cmake -DCUSTOMIZE_BUILD=ON -DCMAKE_BUILD_TYPE=Release ..

#Make Raylib
make -j4

#Install it
sudo make install
```

### Clone this repo, and build it
```
#Clone the repo, create a build directory
git clone https://github.com/phensd/Auto-Picture-Puzzle.git
cd Auto-Picture-Puzzle-master
mkdir build
cd build

#Generate the build files
cmake -DCMAKE_BUILD_TYPE=Release ..

#Compile and build
make -j4
```
The program can now be run with ``./PicturePuzzle``.



## Compilation (Windows)
**Note: I am not a windows developer. If someone would like to assist in making this simpler/more typical of a windows compilation process, feel free to contribute.**
### Download W64DevKit and add it to your PATH environment variable:


[Navigate to "Releases" and download the provided .zip file.](https://github.com/skeeto/w64devkit)

Extract it somewhere convenient, [then add the .bin folder to your PATH environment variable in Windows.](https://www.mathworks.com/matlabcentral/answers/94933-how-do-i-edit-my-system-path-in-windows)

W64DevKit allows for use of common GNU tools found on most Linux distributions through the windows command line, including a C and C++ compiler, making this process much simpler.



### Download and install CMake
[CMake for windows can be found here, with a convenient installer that will automatically add CMake to your PATH variable.](https://cmake.org/download/)



### Download the Raylib repo, compile the library and install it

First, [Download the raylib repo and extract it somewhere accessible](https://github.com/raysan5/raylib)

Then, [Follow the previous instructions on how to modify the root folder's CMakeOptions.txt for this project](#edit-cmakeoptionstxt-to-support-more-image-formats). **This step should not be skipped.**

Now, Open a Command Prompt with **administrator privileges** and run the following commands
```
#Go to the Raylib source directory, and make a build directory, then change to it.
cd <the path to the extracted Raylib source>
mkdir build
cd build

#Generate MinGW build files
cmake -G "MinGW Makefiles" -DCUSTOMIZE_BUILD=ON -DCMAKE_BUILD_TYPE=Release ..

#Make the static lib
make -j4

#Install raylib to C:\Program Files (x86)\raylib
#This command in particular requires the command prompt to be elevated to admin.
make install
```
Make sure wherever Raylib installed to [is set in your PATH environment variable.](https://www.mathworks.com/matlabcentral/answers/94933-how-do-i-edit-my-system-path-in-windows) *It should be in C:\Program Files (x86)\Raylib\\*


### Compile Auto Picture Puzzle

[Download this repo, and extract it somewhere easy-to-access.](https://github.com/phensd/Auto-Picture-Puzzle/archive/refs/heads/master.zip)

Now, run the following commands:
```
cd <the path to the extracted Auto Puzzle Picture source>
mkdir build
cd build

#Generate MinGW build files
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..

#Build Auto Picture Puzzle
make -j4
```
The final result should be a file `PicturePuzzle.exe` in the build directory!

