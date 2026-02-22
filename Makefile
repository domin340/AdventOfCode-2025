CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic

INCLUDE = -I"include"
FILES = src/helper.c
INCLUDE_FILES = $(INCLUDE) $(FILES)

CC_FILES_FLAGS = $(CC) $(CFLAGS) $(INCLUDE_FILES)

SOURCE_DIR = src
BUILD_OUT = bin
DEBUG_OUT = bin/debug

CURRENT_DAY = day_4
CURRENT_FILE = $(SOURCE_DIR)/$(CURRENT_DAY).c

day_1:
	$(CC_FILES_FLAGS) $(SOURCE_DIR)/day_1.c -o $(BUILD_OUT)/day_1

day_2:
	$(CC_FILES_FLAGS) $(SOURCE_DIR)/day_2.c -o $(BUILD_OUT)/day_2

day_3:
	$(CC_FILES_FLAGS) $(SOURCE_DIR)/day_3.c -o $(BUILD_OUT)/day_3

day_4:
	$(CC_FILES_FLAGS) $(SOURCE_DIR)/day_4.c -o $(BUILD_OUT)/day_4

build:
	$(CC_FILES_FLAGS) $(CURRENT_FILE) -o $(BUILD_OUT)/main

debug:
	$(CC_FILES_FLAGS) $(CURRENT_FILE) -o $(DEBUG_OUT)/prog -g

