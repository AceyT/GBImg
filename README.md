# GBImg

GBImg is a command-line tool to convert BMPs and PNG into Gamebuino Image in the flash memory format  
It currently only support uint8[] Flash image with indexed color.

## Usage

The simplest use case scenario is to give it an image and it will transform it to a gamebuino `const uint8_t[]` data & Image

  $ GBImg -i <image_path> -o <output_path>(default: "code.hpp") -c <code_name>(default:"image")

It can also handle the ["spritesheet" trick][spritesheet] that Sorunome explained and convert a "classic" approach of images tileset to the one that the gamebuino undertstands

  $ GBImg -i <spritesheet_image_path> --spritesheet --tile-x <Number of tiles on the X axis> --tile-y <Number of tiles on the Y axis>

You can display the help with -h or --help (note that it won't execute the rest of the program if this flag is activated)
```
Usage:
  GBImg [OPTION...]

  -o, --output-path arg         File name of the export (default: code.hpp)
  -i, --image-input arg         Image path to convert
  -c, --code-name arg           identifier in the exported code (default:
                                image)
      --transparency [=N(=0)]   Choosen color index used for transparency.
                                Value greater than 15 (0x0F) will make the
                                program not handle transparency (default: 255)
      --palette default / edge16
                                Choosen color palette used for finding
                                correct indexes (default: default)
      --palette-file arg        File from which the color palette will be
                                used (override palette option)
  -h, --help                    Print the help

 Spritesheet options:
  -s, --spritesheet  Activate the spritesheets mode
      --tile-x N     Number of tiles on X coord | Sub width will be deduced
                     with image-width / tile-x (default: 0)
      --tile-y N     Number of tiles on Y coord | Sub height will be deduced
                     with image-height / tile-y (default: 0)
      --framerate N  Framerate of the animation | number of frame per
                     animation (default: 0)
```
## Build

To build it, you have to have to use CMake


````bash

$ mkdir build
$ cd build

# ->For Windows - MS Visual Studio

$ cmake ..
# and open the GBImg.sln

# -> For Windows - msys makefiles
cmake .. -G "MSYS Makefiles"
make

# -> for Linux
cmake ..
make

````

## Requirements

- CMake >= 3.3
- A C++ compiler that supports C++11 regular expression. GCC >= 4.9 should be fine or clang with libc++.

Tested :

- On Windows 7
  - g++ (tdm64-1) 4.9.2
  - MSVC 2015


## Credits

- "Sean T. Barrett" for the [stb library && stb_image.h][stb] 
- "jarro2783" for the [cxxopts library][cxxopts]


[stb]: https://github.com/nothings/stb
[cxxopts]: https://github.com/jarro2783/cxxopts

## Todo
- Loading custom color palette from file
- Support `uint16_t[]` images
- Convert RGB888 to RGB565
- Multiples images at once
- Other Export method


## License

This repository is entirely licensed under the MIT open source license.
You can do whatever you want with it and have no legal obligation of anything.

[spritesheet]: https://gamebuino.com/fr/creations/images