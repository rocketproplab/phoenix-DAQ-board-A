# Usage: make build BOARD=A|B   /   make flash BOARD=B PORT=/dev/cu.usbserial-XXXX
BOARD ?= A
PORT  ?=
FQBN  ?= esp32:esp32:esp32
SKETCH = phoenix-fc-valve-board
STAGE  = build/$(SKETCH)

.PHONY: build flash stage clean
stage:
	@mkdir -p $(STAGE)
	@cp $(SKETCH).ino board_config.h w5500.h w5500.cpp $(STAGE)/

build: stage
	arduino-cli compile --fqbn $(FQBN) \
	  --build-property "compiler.cpp.extra_flags=-DBOARD_$(BOARD)" $(STAGE)

flash: stage
	arduino-cli compile --upload -p $(PORT) --fqbn $(FQBN) \
	  --build-property "compiler.cpp.extra_flags=-DBOARD_$(BOARD)" $(STAGE)

clean:
	rm -rf build
