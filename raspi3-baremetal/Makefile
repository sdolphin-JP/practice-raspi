CFLAGS   = -mcpu=cortex-a53 -fpic -ffreestanding -fsigned-char -Wall -Wextra -Wno-missing-field-initializers -O0 -g3
ASMFLAGS = -mcpu=cortex-a53
LDFLAGS  = -T lscript.ld
TARGET   = kernel8.elf kernel8.lst kernel8.bin
LIBS     = -lc -lm
ASMFILES = $(wildcard sources/*.S)
CFILES   = $(wildcard sources/*.c)
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
	$(OC) --strip-debug --strip-unneeded -O binary $< $@

.PHONY: kernel8.lst
kernel8.lst: kernel8.elf
	$(OD) -d $< > $@

.PHONY: kernel8.elf
kernel8.elf: $(OBJS) $(LIBS)
	$(CC) -o $@ $(CFLAGS) -nostdlib $(LDFLAGS) $(OBJS) $(LIBS)

.PHONY: %.asm_o
%.asm_o : %.S
	$(AS) -o $@ $(ASMFLAGS) $<

.PHONY: %.src_o
%.src_o : %.c
	$(CC) -o $@ -c $(CFLAGS) $(INCS) $<

.PHONY: run-qemu
run-qemu:
	@/opt/qemu-6.1.0/bin/qemu-system-aarch64 \
		-M raspi3b \
		-m 1024 \
		-monitor stdio \
		-display none \
		-d in_asm \
		-kernel kernel8.elf
