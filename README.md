# Unspaghettify Kart 64

We all love spaghetti! It's delicious, tasty, and outright brilliant flavours. You can just imagine it. It's 1996 and you're sitting at your IRIX workstation programming Mario Kart 64... With a plate of spaghetti perilously close to the computer keyboard. Your two-thirds through a nearly sixteen hour day and in a tetonic dream-like state. When Miyamoto appears around your shoulder inquiring as to what you are doing. You nearly jump out of your seat as your hand grazes the plate of spaghetti sending it _everywhere_. Spaghetti on you. Spaghetti on Miyamoto. Spaghetti on the keyboard. Spaghetti hanging off the computer monitor. You notice tomato sauce dripping into the mainframe. _This can't be good_. Despite previous preconceptions, code and spaghetti do _not_ mix and your workstation is now infected by spaghetti! Suddenly your code files are tens of thousands of lines long, you have features spread across files in a haphazard, inconsistent, and unorganized manner. Your once majestic memory management routines are no longer existant, replaced by a manually typed DMA everytime one is used. The sweet actor behaviour routines are now spread between two completely different actor setups in no conceptual or coordinated manner. You and Miyamoto look upon the project in horror with Miyamoto quietly whispering "_What have you done?_" Your fantastic state of the art 3D models having been replaced with sprites was the final insult to injury. All you can do is shake your head as you get back to work. Your final deadline is only a month away afterall...

## Decomp Readme

This work-in-progress decompilation of Mario Kart 64 pursues historical and educational elements within the game found via taking it apart and putting it back together. Inspiration to do so not only emanates from the game's hardware and technology but also its immensely positive effects on the cultures and families of nearly every nationality. See [progress](#Progress) for more information.

This repository does not contain assets. Compiling requires asset extraction from a prior copy of the game.

It supports and builds the following versions:

| ROM Output        | Revision| SHA-1 Checksum                           |
|-------------------|---------|------------------------------------------|
| mk64.us.z64       | USA     | 579c48e211ae952530ffc8738709f078d5dd215e |
| mk64.eu-1.0.z64   | EUR 1.0 | a729039453210b84f17019dda3f248d5888f7690 |
| mk64.eu-final.z64 | EUR 1.1 | f6b5f519dd57ea59e9f013cc64816e9d273b2329 |

## Score progress

Total progress consists of all code segments together.

Game code progress consists of `main`, `ending` and `racing`.

[![Build Status](https://ci.valandil.ca/buildStatus/icon?job=mk64%2Fmaster&config=totalProgress)](https://ci.valandil.ca/job/mk64/job/master/)
[![Build Status](https://ci.valandil.ca/buildStatus/icon?job=mk64%2Fmaster&config=gameProgress)](https://ci.valandil.ca/job/mk64/job/master/)

[![Build Status](https://ci.valandil.ca/buildStatus/icon?job=mk64%2Fmaster&config=bytesLeft)](https://ci.valandil.ca/job/mk64/job/master/)
[![Build Status](https://ci.valandil.ca/buildStatus/icon?job=mk64%2Fmaster&config=m2c)](https://ci.valandil.ca/job/mk64/job/master/)
[![Build Status](https://ci.valandil.ca/buildStatus/icon?job=mk64%2Fmaster&config=nonmatching)](https://ci.valandil.ca/job/mk64/job/master/)  

- [![Build Status](https://ci.valandil.ca/buildStatus/icon?job=mk64%2Fmaster&config=mainProgress)](https://ci.valandil.ca/job/mk64/job/master/)
- [![Build Status](https://ci.valandil.ca/buildStatus/icon?job=mk64%2Fmaster&config=endingProgress)](https://ci.valandil.ca/job/mk64/job/master/)
- [![Build Status](https://ci.valandil.ca/buildStatus/icon?job=mk64%2Fmaster&config=racingProgress)](https://ci.valandil.ca/job/mk64/job/master/)
- [![Build Status](https://ci.valandil.ca/buildStatus/icon?job=mk64%2Fmaster&config=audioProgress)](https://ci.valandil.ca/job/mk64/job/master/)
- [![Build Status](https://ci.valandil.ca/buildStatus/icon?job=mk64%2Fmaster&config=osProgress)](https://ci.valandil.ca/job/mk64/job/master/)

## Dependencies

The build system has the following package requirements:

    binutils-mips >= 2.27
    python3 >= 3.6
    libaudiofile

To add submodules run `git submodule update --init --recursive` after cloning.

## EU Specific Steps (All versions)
Both EU builds first requires US to be built first:
```
make -j
```

Now build either EU 1.0 `eu-1.0` or EU 1.1 `eu-final`
```
make -j VERSION=eu-final
```

diff/first-diff commands
```
python3 first-diff.py --eu
./diff <function> -eu
```

#### Debian / Ubuntu
```
sudo apt install build-essential pkg-config git binutils-mips-linux-gnu python3 zlib1g-dev libaudiofile-dev libcapstone-dev
```

#### Arch Linux

To install build dependencies:
```
sudo pacman -S base-devel capstone python
```
Install the following AUR packages:
* [mips64-elf-binutils](https://aur.archlinux.org/packages/mips64-elf-binutils) (AUR)

Review the n64decomp/sm64 readme for instructions to compile in other distributions.

#### Windows

Compiling on Windows requires `MSYS2 MinGW x64`. The setup process is a tad intensive.  

[Instructions here](docs/BUILD_WINDOWS.md)

#### macOS

Install [Homebrew](https://brew.sh), then install the following dependencies:
```
brew update
brew install python3 capstone coreutils make pkg-config tehzz/n64-dev/mips64-elf-binutils
```

When building, use `gmake` to ensure that homebrew `make` is used instead of the old, macOS system `make`.

#### Docker

Build the Docker image:
```
docker build -t mk64 .
```

When building and using other tools, append the following in front of every command you run:
```bash
docker run --rm -v ${PWD}:/mk64 mk64
```

For example:
```bash
docker run --rm -v ${PWD}:/mk64 mk64 make -C tools
docker run --rm -v ${PWD}:/mk64 mk64 make
```

## Building

Place a US version of Mario Kart 64 called `baserom.us.z64` into the project folder for asset extraction.

Run the following commands after pulling:
```bash
make -C tools
make
```

## Progress

The source is in a 'shiftable' state that may allow modding but glitches may exist. Keep in-mind the code-base will alter significantly overtime. Feedback that raises awareness of new shift issues are welcome as a comment on issue #6. Note that some segments must be moved manually to prevent them colliding into each other.  

Some menu textures are compressed using a format called tkmk00. A byte-matching compressor/decompressor does not yet exist.   

## Project Structure
	
	mk64
	├── asm: Handwritten assembly code, rom header and boot
	│   ├── non_matchings: Assembly for non-matching sections
	│   └── os: Libultra handwritten assembly code
	├── assets: Textures
	├── courses: Course data, geography, display lists and staff ghosts
	├── build: Output directory
	├── data: Misc data, text, audio banks, and instrument sets
	├── docs: Build guides
	├── include: Header files
	├── music: Sequences
	├── src: C source code for the game
	|   ├── actors: Individual actors split out from other files
	│   ├── audio: Sample tables and audio code
	│   ├── data: Misc data referenced in other C files
	|   ├── debug: Custom debug code
	|   ├── ending: Podium ceremony and credits code
	│   ├── os: Libultra C code
	|   └── racing: Race and game engine code
	├── textures: Texture data, bitmaps
	|   ├── common: Textures common to many courses
	|   ├── courses: Course specific textures
	|   ├── crash screen: Crash screen font image
	│   ├── raw: Raw textures
    │   ├── standalone: Whole textures
	|   ├── startup_logo: Reflection map
	|   └── trophy: Ceremony cutscene podium and trophy textures
	└── tools: build tools

## Documentation

[Doxygen](https://www.doxygen.nl/index.html) is used to generate documentation. To generate the documentation, run `doxygen Doxyfile` from the project root. The documentation will be generated in the `docs/html` folder.
The documentation is also available online at [https://n64decomp.github.io/mk64/](https://n64decomp.github.io/mk64/).

## Contributing

Pull requests are welcome. For major changes, please discuss in the Discord.

Run `clang-format` on your code to ensure it meets the project's coding standards.

Official Discord: [discord.gg/DuYH3Fh](https://discord.gg/DuYH3Fh)
