@page compiling Installing mk64 Decomp
# Build Instructions
The build system has the following package requirements:

    binutils-mips >= 2.27
    python3 >= 3.6
    libaudiofile

[TOC]

To add submodules run `git submodule update --init --recursive` after cloning.

# Linux
```bash
sudo apt install build-essential pkg-config git binutils-mips-linux-gnu python3 zlib1g-dev libaudiofile-dev libcapstone-dev
```

### Arch

```bash
sudo pacman -S base-devel capstone python
```
Install the following AUR package:
* [mips64-elf-binutils](https://aur.archlinux.org/packages/mips64-elf-binutils) (AUR)

Review the [n64decomp/sm64](https://github.com/n64decomp/sm64) readme for instructions to compile in other distributions.

# Windows

*N64 decomp does not mesh well with Windows. However, this process has been refined to be as painless as possible. WSL is a great alternative if issues arise.*

### Requirements
- Clone the repo or download the zip on your computer
- Dowload toolchain from [here](https://github.com/coco875/mk64-tools/releases/download/v0.0.6/mips-tools-chain-windows.zip)

### Setup
1. copy from mips-tools-chain-windows.zip the folder `mingw64` into tools folder in the repo
2. Open a terminal (cmd or powershell) in the repo folder and run `"tools\mingw64\w64devkit.exe"` and after `make`
3. Wait for the build to finish and Enjoy!

# macOS

Install [Homebrew](https://brew.sh), then install the following dependencies:
```bash
brew update
brew install python3 capstone coreutils make pkg-config tehzz/n64-dev/mips64-elf-binutils
```

Build using `gmake` ensuring homebrew `make` is used instead of the old macOS system `make`.

# Docker

Build the Docker image:
```bash
docker build -t mk64 .
```

When building and using other tools, append the following in front of every command you run:
```bash
docker run --rm -v .:/mk64 mk64
```

For example:
```bash
docker run --rm -v .:/mk64 mk64 make
```

# Building US

Place a US version of Mario Kart 64 called `baserom.us.z64` into the project folder for asset extraction.

Run the following commands after pulling:
```bash
make -j
```

# Building EU

Building EU requires US to be built first. See above.

mk64 decomp supports two EU versions
* EU 1.0 `eu-1.0`
* EU 1.1 `eu-final`

Build using
```bash
make -j VERSION=eu-1.0
```
or
```bash
make -j VERSION=eu-final
```

First-diff/diff commands for EU
```bash
python3 first-diff.py --eu
./diff <function> -eu
```