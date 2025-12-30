TARGET  := blink

CC      := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
OBJDUMP := arm-none-eabi-objdump
SIZE    := arm-none-eabi-size

# ---- Paths ----
BUILD   := build

# ---- Device ----
DEFS := -DSTM32F411xE

# ---- Includes ----
INCLUDES := \
  -ICore/inc \
  -IDrivers/CMSIS/Core/Include \
  -IDrivers/CMSIS/Device/ST/STM32F4xx/Include

# ---- Flags ----
CFLAGS := -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard \
          -O0 -g3 -ffreestanding -fdata-sections -ffunction-sections \
          -Wall -Wextra \
          $(DEFS) $(INCLUDES)

LDFLAGS := -T linker_script.ld -nostdlib \
           -Wl,--gc-sections -Wl,-Map=$(BUILD)/$(TARGET).map

# ---- Sources ----
SRCS := \
  Core/src/main.c \
  Drivers/CMSIS/Device/ST/STM32F4xx/Source/system_stm32f4xx.c \
  Core/src/gpio.c \
  Core/src/clock.c \
  Core/src/uart.c \
  Core/src/startup.c

OBJS := $(patsubst %.c,$(BUILD)/%.o,$(SRCS))

# ---- Default ----
all: $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).bin

# Ensure build dirs exist
$(BUILD):
	mkdir -p $(BUILD)

# Compile C files to build/...
$(BUILD)/%.o: %.c | $(BUILD)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Link
$(BUILD)/$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) $@

# Binary
$(BUILD)/$(TARGET).bin: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Disassembly
disasm: $(BUILD)/$(TARGET).elf
	$(OBJDUMP) -D $< > $(BUILD)/$(TARGET).lst

clean:
	rm -rf $(BUILD)
