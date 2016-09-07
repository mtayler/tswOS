SHELL	:= /bin/bash

export TARGET ?= i386

#--- Source Files ---
PROJ	:= fat-test
CFILES	:= $(notdir $(wildcard *.c))

LINKER	:= linker.ld

export BLDDIR	:= build
# Make build directory if it doesn't exist
$(shell mkdir $(BLDDIR) 2>/dev/null)

#--- Tool Settings ---
AS		:= $(CROSS)as
CC		:= $(CROSS)gcc
LD		:= $(CROSS)gcc

CFLAGS := -std=gnu99 -g -ffreestanding -O2 -Wall -Wextra
LDFLAGS	:= -ffreestanding -O2

LDLIBS	:= -nostdlib -lgcc

$(BLDDIR)/$(PROJ): $(CFILES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	$(RM) $(BLDIR)/*
