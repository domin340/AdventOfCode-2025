#include <stddef.h>
#include <stdio.h>
#include <string.h>

static inline int chr_digit_to_int(char chr) {
    return chr - '0';
}

int get_highest_joltage_two(char* str, size_t len) {
    // THIS MAY CAUSE ISSUES LATER
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

int main(void) {
    FILE* f;
    if (fopen_s(&f, "inputs/day_3.txt", "r") != 0) {
        perror("couldn't open inputs/day_3.txt file: ");
        return 1;
    }

    size_t product_sum = 0;

    char line[128];
    while (fgets(line, sizeof(line), f)) {
        // trim line
        line[strcspn(line, "\r\n")] = '\0';
        size_t line_len = strlen(line);

        // part 1 function
        product_sum += get_highest_joltage_two(line, line_len);
    }

    fclose(f);

    printf("part 1 solution is: %zu\n", product_sum);

    return 0;
}
