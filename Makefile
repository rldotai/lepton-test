.PHONY: all clean

CC = gcc
LIBS = -lm -I libs/leptonSDKEmb32PUB/ -lLEPTON_SDK -L libs/leptonSDKEmb32PUB/Debug
CFLAGS = -g -Wall -I/usr/local/include -I libs/altSDK/ -lLEPTON_SDK -L libs/altSDK/Debug -lbcm2835

# Using the standard SDK from GroupGets/LeptonModule/software/raspberrypi_libs/leptonSDKEmb32PUB
# LIBS = -lm -I/usr/local/include -I libs/altSDK/ -lLEPTON_SDK -L libs/altSDK/Debug -lbcm2835
# CFLAGS = -g -Wall -I libs/leptonSDKEmb32PUB/ -lLEPTON_SDK -L libs/leptonSDKEmb32PUB/Debug

SOURCE_DIR := ./src
OUTPUT_DIR := ./bin
BUILD_DIR := ./build

TARGETS := test_libs
OUTPUTS := $(addprefix $(OUTPUT_DIR)/, $(TARGETS))


all: $(OUTPUTS)
	@echo "Making!"
	@echo $(TARGETS)
	@echo $(OUTPUTS)

./bin/test_libs: $(BUILD_DIR)/test_libs.o
	$(CC) -Wall $< $(LIBS) -o $@

$(BUILD_DIR)/test_libs.o: $(SOURCE_DIR)/test_libs.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning!"
	rm -f $(BUILD_DIR)/*
	rm -f $(OUTPUTS)
