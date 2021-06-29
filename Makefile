ARM_PREFIX      := arm-none-eabi
ARM_AS          := $(ARM_PREFIX)-as
ARM_CC          := $(ARM_PREFIX)-gcc
ARM_LD          := $(ARM_PREFIX)-ld
ARM_OC          := $(ARM_PREFIX)-objcopy
ARM_AS_OPTIONS	:= -mcpu=cortex-m3 -mthumb -g
ARM_CC_OPTIONS	:= -Wall -Os -mcpu=cortex-m3 -mthumb -g -nostdlib -nostartfiles
C_SOURCES       := armsemaforo.c
S_SOURCES       := start.s
PROJECT_NAME    := armsemaforo

BINDIR   = bin
BUILDDIR = build
SRCDIR   = src
LINKER   = stm32f205rb.ld
MEMSTACK = 0x08000000

all: $(BINDIR)/$(PROJECT_NAME).bin $(BUILDDIR)
clean: 
	@rm -rf $(BINDIR)/*.o $(BINDIR)/*.elf $(BINDIR)/*.bin
	@rm -rf $(SRCDIR)/*.o $(SRCDIR)/*.elf $(SRCDIR)/*.bin
	@rm -rf $(BUILDDIR)/*.o $(BUILDDIR)/*.elf $(BUILDDIR)/*.bin
	@rm -rf *.o *.elf *.bin
burn: $(BINDIR)/$(PROJECT_NAME).bin
	st-flash write $(PROJECT_NAME).bin $(MEMSTACK)
$(BUILDDIR)/%.o: $(SRCDIR)/%.s
	$(ARM_AS) $(ARM_AS_OPTIONS) $(<) -o $(@)
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(ARM_CC) $(ARM_CC_OPTIONS) -c $(<) -o $(@)
$(BINDIR)/$(PROJECT_NAME).elf: $(LINKER) $(BUILDDIR)/$(S_SOURCES:.s=.o) $(BUILDDIR)/$(C_SOURCES:.c=.o)
	$(ARM_CC) $(ARM_CC_OPTIONS) -T $(^) -o $(@)
$(BINDIR)/$(PROJECT_NAME).bin: $(BINDIR)/$(PROJECT_NAME).elf
	$(ARM_OC) -O binary $(<) $(@)
