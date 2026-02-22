#include <helper.h>

char* read_file_until_eof(const char* fname, size_t* out_size) {
    FILE* f;
    if (fopen_s(&f, fname, "rb") != 0) {
        return NULL;
    }

    // find file size
    fseek(f, 0, SEEK_END);
    long f_size = ftell(f);
    rewind(f);

    // get all the content
    char* src = (char*)malloc(f_size + 1);

    if (src != NULL) {
        size_t readb = fread(src, sizeof(char), f_size, f);
        src[readb] = '\0';

        if (out_size != NULL) {
            *out_size = readb;
        }
    }

    // close the file
    fclose(f);

    return src;
}

uint integer_char_len(size_t n) {
    uint len = 1;
    while (n >= 10) {
        n /= 10;
        ++len;
    }

    return len;
}
