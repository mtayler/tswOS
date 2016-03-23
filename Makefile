#--- Source Files ---
PROJ	:= myos
EXT		:= iso
ASFILES	:= boot.s
CFILES	:= kernel.c
LINKER	:= linker.ld

SOBJS	:= $(ASFILES:.s=.o)
COBJS	:= $(CFILES:.c=.o)
OBJS	:= $(SOBJS) $(COBJS)

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
	
$(PROJ).$(EXT): $(PROJ).bin
	mkdir -p isodir/boot/grub
	cp -f $(PROJ).bin isodir/boot/
	cp -f grub.cfg isodir/boot/grub/
	grub-mkrescue -o $(PROJ).$(EXT) isodir

$(PROJ).bin: $(OBJS)
	$(LD) -T $(LINKER) -o $@ $(LDFLAGS) $(OBJS) $(LDLIBS)

# $(COBJS): %.o : %.c
# 	$(CC) $(CLAGS) -c $< -o $@

$(SOBJS): %.o : %.s
	$(AS) $(ASFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJS)
	$(RM) $(PROJ).$(EXT)
	$(RM) $(PROJ).bin
	$(RM) -r isodir
