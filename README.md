# Auto Picture Puzzle - Create an interactive sliding picture puzzle from any image 

- [Compilation (Linux)](#compilation-linux)
- [Compilation (Windows)](#compilation-windows)

## Compilation (Linux)
### Install Raylib's dependencies:
```
(Source: https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)

#Ubuntu 
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev

#Fedora
sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic

#Arch Linux
sudo pacman -S alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama

```
### Clone the Raylib repo:
```
git clone https://github.com/raysan5/raylib.git
```

### Edit CMakeOptions.txt to support more image formats:
#### Then, navigate to the source folder's CMakeOptions.txt, and find the following lines:

<details>
<summary> Original CMakeOptions.txt section from the Raylib repo: </summary> 
  
```
(Source: https://github.com/raysan5/raylib/blob/master/CMakeOptions.txt)
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

#The program can now be run with "./PicturePuzzle".
```


### Compilation (Windows)
