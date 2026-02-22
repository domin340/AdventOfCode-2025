#include <helper.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROLLS_COUNT 4
#define DIRECTIONS_COUNT 8
#define DIRECTIONS 2

#define msg_assert(exp, ...) \
    if ((exp) != true) {     \
        printf(__VA_ARGS__); \
        abort();             \
    }

typedef struct {
    char** grid;
    int rows;
    int cols;
} ForkliftGrid;

static int forklift_dire[DIRECTIONS_COUNT][DIRECTIONS] = {
    {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1},
};

bool pos_accessible(const ForkliftGrid* grid, int row, int col) {
    int rolls_arround = 0;
    for (int i = 0; i < DIRECTIONS_COUNT; ++i) {
        int _col = col + forklift_dire[i][0];
        int _row = row + forklift_dire[i][1];

        if (_col >= 0 && _col < grid->cols && _row >= 0 && _row < grid->rows) {
            if (grid->grid[_row][_col] != '.') {
                ++rolls_arround;
                if (rolls_arround >= MAX_ROLLS_COUNT) {
                    return false;
                }
            }
        }
    }

    return true;
}

int part1_find_accessible(const ForkliftGrid* grid) {
    int counter = 0;

    for (int row = 0; row < grid->rows; ++row) {
        for (int col = 0; col < grid->cols; ++col) {
            char* c = &grid->grid[row][col];
            if (*c != '.' && pos_accessible(grid, row, col)) {
                // increment counter and mark it
                ++counter;
                *c = '#';
            }
        }
    }

    return counter;
}

static int file_line_len(FILE* f) {
    int len = 0;
    char c;

    while ((c = fgetc(f)) != '\r' && c != '\n' && c != '\0') {
        ++len;
    }

    rewind(f);

    return len;
}

int main(void) {
    FILE* f;
    if (fopen_s(&f, "inputs/day_4.txt", "r") != 0) {
        printf("inputs/day_4.txt must exist!");
        return 1;
    }

    int grid_cols = file_line_len(f);
    msg_assert(grid_cols > 0, "expected line len to the higher: %d\n",
               grid_cols);

    // build a string
    int grid_capacity = 0;
    int grid_rows = 0;
    char** grid = NULL;

    char temp_buf[grid_cols];
    while (fgets(temp_buf, grid_cols + 2, f) != NULL) {
        if (grid_rows >= grid_capacity) {
            grid_capacity = (grid_capacity == 0) ? 2 : (grid_capacity * 2);

            char** new_grid = _recalloc(grid, grid_capacity, sizeof(char*));
            if (new_grid == NULL) {
                printf("couldn't allocate memory for grid\n");
                return 1;
            }

            grid = new_grid;
        }

        temp_buf[strcspn(temp_buf, "\r\n\0")] = '\0';

        grid[grid_rows++] = _strdup(temp_buf);
    }

    grid_rows = fmax(grid_rows, 1);

    ForkliftGrid forklift = {grid, grid_rows, grid_cols};
    int count1 = part1_find_accessible(&forklift);

    // printf("cols: %d, rows: %d\n", grid_cols, grid_rows);
    // printf("marked grid now:\n");
    // for (int i = 0; i < grid_rows; ++i) {
    //     printf("%s\n", grid[i]);
    // }

    printf("part 1 solution is: %d\n", count1);

    // free everything
    for (int i = 0; i < grid_capacity; ++i) {
        if (grid[i] == NULL) {
            continue;
        }

        free(grid[i]);
    }
    free(grid);

    return 0;
}
