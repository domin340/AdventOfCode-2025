#include <helper.h>

#define ULLONG_CHAR_LEN 20
#define STR_ULLONG_LEN (ULLONG_CHAR_LEN + 1)

bool part1_is_invalid_id(size_t n) {
    uint n_len = integer_char_len(n);
    if (n_len % 2 == 1) {
        return false;
    }

    // number that divides the number into 2
    uint mid_len = n_len / 2;

    // n: 1122 -> left: 11, right: 22
    size_t mid_exponent = pow(10, mid_len);
    size_t left = n / mid_exponent;
    size_t right = n % mid_exponent;

    // compare 2 numbers
    return left == right;
}

int main(void) {
    const char* input_fname = "inputs/day_2.txt";
    size_t content_size;
    char* content = read_file_until_eof(input_fname, &content_size);
    if (content == NULL) {
        perror("file (inputs/day_2.txt) could not be read");
        return 1;
    }

    size_t sum1 = 0;

    // buffer to hold number
    char first_number[STR_ULLONG_LEN], second_number[STR_ULLONG_LEN];

    const char* delim = ",";
    char* next_token;
    char* split = strtok_s(content, delim, &next_token);
    while (split != NULL) {
        char* occurence = strchr(split, '-');

        // copy what's after dash until \0 placed by split
        if (strcpy_s(second_number, sizeof(second_number), (occurence + 1)) != 0) {
            perror("something wrong in input: ");
            break;
        }

        // <first number>-<second number>
        // ^------------^ copy this part
        size_t first_number_size = strlen(split) - strlen(occurence);
        if (strncpy_s(first_number, sizeof(first_number), split, first_number_size) != 0) {
            perror("couldn't parse second number: ");
            break;
        }

        size_t n1 = atoll(first_number), n2 = atoll(second_number);

        for (size_t i = n1; i <= n2; ++i) {
            if (part1_is_invalid_id(i)) {
                sum1 += i;
            }
        }

        // go to the next occurence of comma character
        split = strtok_s(NULL, delim, &next_token);
    }

    free(content);

    printf("part 1 solution is: %zu\n", sum1);

    return 0;
}
