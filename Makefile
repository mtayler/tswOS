SHELL	:= /bin/bash

export ROOT	:= ${CURDIR} 
export TARGET ?= i386

#--- Source Files ---
PROJ	:= tswOS
EXT		:= iso
ASFILES	:= boot.s
CFILES	:= $(notdir $(wildcard **/*.c))

LINKER	:= linker.ld

export BLDDIR	:= build
export HEADERS	:= $(realpath ./headers)
# Make build directory if it doesn't exist
$(shell mkdir $(BLDDIR) 2>/dev/null)

#--- Tool Settings ---
CROSS	:= i686-elf-
AS		:= $(CROSS)as
CC		:= $(CROSS)gcc
LD		:= $(CROSS)gcc

CFLAGS := -std=gnu99 -g -ffreestanding -O2 -Wall -Wextra -I$(HEADERS)
LDFLAGS	:= -ffreestanding -O2

LDLIBS	:= -nostdlib -lgcc

$(PROJ).$(EXT): $(BLDDIR)/$(PROJ).bin
	mkdir -p $(BLDDIR)/isodir/boot/grub
	cp -f $(BLDDIR)/$(PROJ).bin $(BLDDIR)/isodir/boot/
	cp -f grub.cfg $(BLDDIR)/isodir/boot/grub/
	grub-mkrescue -o $(PROJ).$(EXT) $(BLDDIR)/isodir

$(BLDDIR)/$(PROJ).bin: $(BLDDIR)/arch.o $(BLDDIR)/kernel.o
	$(LD) -T $(LINKER) -o $@ $(LDFLAGS) $^ $(LDLIBS)

$(BLDDIR)/arch.o:
	cd arch/$(TARGET); make

$(BLDDIR)/kernel.o:
	cd kernel; make

.PHONY: run
run: $(PROJ).$(EXT)
	qemu-system-i386 -cdrom $(PROJ).$(EXT)

.PHONY: debug
debug: $(PROJ).$(EXT)
	qemu-system-i386 -s -S -cdrom $(PROJ).$(EXT)

.PHONY: clean
clean:
	cd arch/*/; make clean
	cd kernel; make clean
	$(RM) $(PROJ).$(EXT)
	$(RM) -r $(BLDDIR)/isodir
	$(RM) $(BLDDIR)/*
