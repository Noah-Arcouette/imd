# Improved MarkDown reader ( IMD )

The IMD is a markdown reader designed to look good and be useful.

IMD is written in C and must be recompiled for configuration.


# Examples

![top](/img/top.png)
![bottom](/img/bottom.png)


# Requirements

- [(GNU) LibC](https://www.gnu.org/software/libc/)
- C Compiler
  - [GCC](https://gcc.gnu.org/)
  - [CLANG](https://clang.org/)
- [(GNU) Make](https://www.gnu.org/software/make/)
- [BinUtils](https://www.gnu.org/software/binutils/)
- [(MAKE) Git](https://git-scm.com/)
- [(MAKE) Python](https://www.python.org/)
- [(MAKE) GZip](https://www.gnu.org/software/gzip/)


# To Know

Development is shown is the file `./TODO.md`.

A unchecked box means it's no implemented.

A slashed box means it's partiality implemented.

A checked box means it's fully implemented.


Known bugs are in the `./BUGS.md` file.

**Please report all bugs and ideas for imd in the issues page**


# Configuration

Run `make configure` to configure the program.

***Configuration files not fully implemented***
***Edit `./confs/default.json` to change styling***


# Rebuild

Once IMD is install you can update the source code in the `/etc/imd/src/` directory to your liking.

Then rebuild IMD with `imd-rebuild <cflags>`


# AUR

IMD is on the AUR at https://aur.archlinux.org/packages/imd-git.

I Recommend using [Trizen](https://github.com/trizen/trizen) to download. ***Yay doesn't work***

IMD is also on the [ChaoticAUR](https://github.com/chaotic-aur/packages).


# Install

Run `./install` it will

 - Clean previous build
 - Rebuild all files
 - Strip and zip files
 - Install binaries and data


# Pre-Built ( Doesn't need git clone ) ( Only need 7z and curl )

Get archive.

`curl https://raw.githubusercontent.com/Noah-Arcouette/imd/master/imd.7z -o ./imd.7z`

Uncompress the 7z archive with.

`7z x ./imd.7z -o./pkg && cd ./pkg`

Install with.

`./.INT`


# Uninstall

Run `sudo make uninstall`.


# Build

Run `make build` to build and strip.

Run `make clean` to clean previous build.

Run `make configure` to configure and generate necessary files for build process.

Run `make all` to build on a development build. ***This will run the built program with test file***
