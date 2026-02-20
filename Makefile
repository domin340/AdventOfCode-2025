CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic

SOURCE_DIR = src
BUILD_OUT = bin
DEBUG_OUT = bin/debug

CURRENT_DAY = day_3
CURRENT_FILE = $(SOURCE_DIR)/$(CURRENT_DAY).c

day_1:
	$(CC) $(SOURCE_DIR)/day_1.c -o $(BUILD_OUT)/day_1 $(CFLAGS)

day_2:
	$(CC) $(SOURCE_DIR)/day_2.c -o $(BUILD_OUT)/day_2 $(CFLAGS)

day_3:
	$(CC) $(SOURCE_DIR)/day_3.c -o $(BUILD_OUT)/day_3 $(CFLAGS)

build:
	$(CC) $(CURRENT_FILE) -o $(BUILD_OUT)/main $(CFLAGS)

debug:
	$(CC) $(CURRENT_FILE) -o $(DEBUG_OUT)/prog $(CFLAGS) -g

