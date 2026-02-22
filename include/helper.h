#pragma once

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define uint unsigned int

// ! file content must be freed
char* read_file_until_eof(const char* fname, size_t* out_size);

// returns the amount of characters the number takes if it was a string
uint integer_char_len(size_t n);
