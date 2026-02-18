CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic

SOURCE_DIR = src
BUILD_OUT = bin
DEBUG_OUT = bin/debug

CURRENT_DAY = day_1
CURRENT_FILE = $(SOURCE_DIR)/$(CURRENT_DAY).c

day_1:
	$(CC) $(SOURCE_DIR)/day_1.c -o $(BUILD_OUT)/day_1 $(CFLAGS)

build:
	$(CC) $(CURRENT_FILE) -o $(BUILD_OUT)/main $(CFLAGS)

debug:
	$(CC) $(CURRENT_FILE) -o $(DEBUG_OUT)/prog $(CFLAGS) -g

