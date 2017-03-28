SHELL	:= /bin/bash

export TARGET ?= i386

#--- Source Files ---
PROJ	:= fat-test
CFILES	:= $(notdir $(wildcard *.c))
HEADERS	:= $(notdir $(wildcard *.h))

LINKER	:= linker.ld

export BLDDIR	:= build
# Make build directory if it doesn't exist
$(shell mkdir $(BLDDIR) 2>/dev/null)

#--- Tool Settings ---
AS		:= $(CROSS)yasm
CC		:= $(CROSS)gcc
LD		:= $(CROSS)gcc

CFLAGS := -std=gnu99 -g -ffreestanding -O2 -Wall -Wextra
LDFLAGS	:= -ffreestanding -O2

LDLIBS	:= -nostdlib -lgcc

$(BLDDIR)/$(PROJ): $(CFILES)
	$(CC) $(CFLAGS) -o $@ $^

depend: .depend

.depend: $(CFILES) $(HEADERS)
	@rm -f ./.depend
	@$(CC) $(CFALGS) -MM $^ > ./.depend;

-include .depend

.PHONY: clean
clean:
	$(RM) $(BLDDIR)/*
	$(RMDIR) $(BLDDIR)/*.dSYM

.PHONY: run
run:
	./$(BLDDIR)/$(PROJ)
