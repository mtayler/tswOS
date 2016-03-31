#--- Source Files ---
PROJ	:= myos
EXT		:= iso
ASFILES	:= boot.s
CFILES	:= $(notdir $(wildcard src/*.c))

LINKER	:= linker.ld

OBJDIR	:= build
SRCDIR	:= src

SOBJS	:= $(addprefix $(OBJDIR)/,$(ASFILES:.s=.o))
COBJS	:= $(addprefix $(OBJDIR)/,$(CFILES:.c=.o))
OBJS	:= $(SOBJS) $(COBJS)

VPATH	:= $(SRCDIR)

#--- Tool Settings ---
CROSS	:= i686-elf-
AS		:= $(CROSS)as
CC		:= $(CROSS)gcc
LD		:= $(CROSS)gcc

ASFLAGS	:=
CFLAGS	:= -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS	:= -ffreestanding -O2

LDLIBS	:= -nostdlib -lgcc

all: $(PROJ).$(EXT)

$(PROJ).$(EXT): $(OBJDIR)/$(PROJ).bin
	mkdir -p $(OBJDIR)/isodir/boot/grub
	cp -f $(OBJDIR)/$(PROJ).bin $(OBJDIR)/isodir/boot/
	cp -f grub.cfg $(OBJDIR)/isodir/boot/grub/
	grub-mkrescue -o $(PROJ).$(EXT) $(OBJDIR)/isodir

$(OBJDIR)/$(PROJ).bin: $(OBJS)
	$(LD) -T $(SRCDIR)/$(LINKER) -o $@ $(LDFLAGS) $(OBJS) $(LDLIBS)

$(COBJS): $(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SOBJS): $(OBJDIR)/%.o : %.s
	$(AS) $(ASFLAGS) $< -o $@


.PHONY: run
run: $(PROJ).$(EXT)
	qemu-system-i386 -cdrom $(PROJ).$(EXT)

.PHONY: clean
clean:
	$(RM) $(OBJS)
	$(RM) $(PROJ).$(EXT)
	$(RM) $(OBJDIR)/$(PROJ).bin
	$(RM) -r isodir
