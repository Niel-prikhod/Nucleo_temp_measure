PRESET ?= Debug

BUILD_DIR = build/$(PRESET)

OPENOCD_INTERFACE = interface/stlink.cfg
OPENOCD_TARGET    = target/stm32f4x.cfg

ELF_FILE = $(shell find $(BUILD_DIR) -name "*.elf" -print -quit)

.PHONY: all config build flash clean fclean re debug server

all: config build flash

config:
	cmake --preset $(PRESET)

build: 
	cmake --build --preset $(PRESET)

flash: 
	@if [ -z "$(ELF_FILE)" ]; then echo "Error: .elf file not found!"; exit 1; fi
	openocd -f $(OPENOCD_INTERFACE) -f $(OPENOCD_TARGET) \
		-c "program $(ELF_FILE) verify reset exit"

clean:
	cmake --build --preset $(PRESET) --target clean

fclean:
	rm -rf build

re: fclean all

debug:
	arm-none-eabi-gdb $(ELF_FILE) \
		-ex "target remote localhost:3333" \
		-ex "monitor reset init"

server:
	openocd -f $(OPENOCD_INTERFACE) -f $(OPENOCD_TARGET)
