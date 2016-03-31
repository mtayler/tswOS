tswOS
=====

An operating system being developed for learning purposes. So far, no plans to overtake Microsoft, Apple, Canonical, etc...

Building
--------
###Requires
- GNU cross compiler targeting i686 systems using the ELF executable format -- called as `i686-elf-gcc` in provided Makefile
- GRUB install compiled for i686 systems (for grub-mkrescue)
- QEMU emulation platform

If each requirement is available in your path, simply call `make` to create a bootable .iso called `tswOS.iso`.

The .iso can be booted in a QEMU i386 environment by calling `make run`, or running `qemu-system-i386 -cdrom tswOS.iso`.
