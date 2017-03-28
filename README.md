tswOS
=====

An operating system being developed for learning purposes. So far, no plans to overtake Microsoft, Apple, Canonical, etc...

Building
--------

### Requires
- GNU cross compiler targeting i686 systems using the ELF executable format -- called as `i686-elf-gcc` in provided Makefile (tested with gcc 5.3.0)
- GRUB install compiled for i686 systems (for grub-mkrescue)
- QEMU emulation platform

If each requirement can be found in `PATH`, simply call `make` from the root directory to create a bootable .iso called `tswOS.iso`.

The .iso can be booted in a QEMU i386 environment by calling `make run` from the root directory, or running `qemu-system-i386 -cdrom tswOS.iso`.


#### Thanks
Huge thanks to the [OSDev.org wiki](http://wiki.osdev.org), this project would undoubtedly not have gotten nearly this far without everyone who contributes to the wiki.
