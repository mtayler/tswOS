SHELL = /bin/bash

BLDDIR	?= build
HEADERS	?= ../../headers
ROOT	?= .

#--- Source Files ---
PROJ	:= tswOS
OUTNAME	:= arch.o
OUT		:= $(strip $(ROOT))/$(BLDDIR)/$(OUTNAME)

CFILES	:= $(wildcard **.c)
SFILES	:= $(wildcard **.s)
OBJS	:= $(addprefix $(BLDDIR)/,${CFILES:.c=.o}) $(addprefix $(BLDDIR)/,${SFILES:.s=.o})
	
# make build dir if it doens't exist
$(shell mkdir $(BLDDIR) 2>/dev/null)

#--- Tool Settings ---
CROSS	:= i686-elf-
AS		:= $(CROSS)as
CC		:= $(CROSS)gcc
LD		:= $(CROSS)gcc

ASFLAGS	:=
CFLAGS	:= -std=gnu99 -g -ffreestanding -O2 -Wall -Wextra -I$(HEADERS)
LDFLAGS	:= -ffreestanding -r -O2 -I$(HEADERS)

LDLIBS	:= -nostdlib -lgcc

# link
$(OUT): $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $^ $(LDLIBS)

# pull in dependencies from .d files
-include $(OBJS:.o=.d)

# compile and generate dependency
$(BLDDIR)/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< > $(BLDDIR)/$*.d

# compile boot file
$(BLDDIR)/%.o : %.s
	$(AS) -c $(ASFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) -rf $(OBJS)
	$(RM) -rf $(OBJS:.o=.d)
