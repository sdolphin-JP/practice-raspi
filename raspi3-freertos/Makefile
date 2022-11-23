CFLAGS   = -mcpu=cortex-a53 -fpic -ffreestanding -fsigned-char -Wall -Wextra -Wno-missing-field-initializers -O0 -g0
ASMFLAGS = -mcpu=cortex-a53
LDFLAGS  = -T lscript.ld
TARGET   = kernel8.elf kernel8.lst kernel8.bin
LIBS     = -lc -lm
ASMFILES = $(wildcard Application/*.S)
CFILES   = $(wildcard Application/*.c)
OBJS     = $(ASMFILES:.S=.asm_o) $(CFILES:.c=.src_o)
INCS     =

.PHONY: default
default: kernel8.bin kernel8.lst

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) *.gcda *.gcno *.gcov *.out *.a *.0 *.su *~

.PHONY: kernel8.bin
kernel8.bin: kernel8.elf
	$(OC) -v -g --strip-unneeded -O binary $< $@

.PHONY: kernel8.lst
kernel8.lst: kernel8.elf
	$(OD) -d $< > $@

.PHONY: kernel8.elf
kernel8.elf: $(OBJS) $(LIBS)
	$(CC) -o $@ $(CFLAGS) -nostdlib $(LDFLAGS) $(OBJS) $(LIBS)

.PHONY: %.asm_o
%.asm_o : %.S
	$(AS) -o $@ $(ASFLAGS) $<

.PHONY: %.src_o
%.src_o : %.c
	$(CC) -o $@ -c $(CFLAGS) $(INCS) $<
