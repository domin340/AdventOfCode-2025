#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int chr_digit_to_int(char chr) {
    return chr - '0';
}

int get_highest_joltage_two(char* str, size_t len) {
    int highest = 0;

    char* str_end = str + len;
    while (str < str_end) {
        // looking from left to right this is essentially current digit value times 10
        int left_product = chr_digit_to_int(*str) * 10;

        for (char* c = (str + 1); c < str_end; ++c) {
            // product they create with this pair
            int product = left_product + chr_digit_to_int(*c);

            if (product > highest) {
                highest = product;
            }
        }

        ++str;
    }

    return highest;
}

// expected end held back by the expected length at the end
static size_t rec_highest_joltage_sub(char* str, char* end, size_t acc) {
    char* highest_digit = str;
    for (char* s = str; s < end; ++s) {
        if ((*s) > (*highest_digit)) {
            highest_digit = s;
        }
    }

    acc = (acc * 10) + chr_digit_to_int(*highest_digit);

    // end the recursion - expected length
    if ((*end) == '\0') {
        return acc;
    }

    // it shifts the window by 1 to the right (gradually goes "back" and "forward")
    return rec_highest_joltage_sub(highest_digit + 1, end + 1, acc);
}

size_t rec_get_highest_joltage_12(char* str, size_t len) {
    // (11 because in the first search we need to find the highest possible value from all 12)
    char* end = (str + len) - 11;
    return rec_highest_joltage_sub(str, end, 0);
}

// recursive version of "get_highest_joltage_two"
size_t rec_get_highest_joltage_2(char* str, size_t len) {
    char* end = (str + len) - 1;
    return rec_highest_joltage_sub(str, end, 0);
}

int main(void) {
    FILE* f;
    if (fopen_s(&f, "inputs/day_3.txt", "r") != 0) {
        perror("couldn't open inputs/day_3.txt file: ");
        return 1;
    }

    size_t product_sum = 0;
    size_t second_sum = 0;

    char line[128];
    while (fgets(line, sizeof(line), f)) {
        // trim line
        line[strcspn(line, "\r\n")] = '\0';
        size_t line_len = strlen(line);

        // part 1 function (recursive!)
        product_sum += rec_get_highest_joltage_2(line, line_len);

        // part 2 function
        second_sum += rec_get_highest_joltage_12(line, line_len);
    }

    fclose(f);

    printf("part 1 solution is: %zu\n", product_sum);
    printf("part 2 solution is: %zu\n", second_sum);

    return 0;
}
