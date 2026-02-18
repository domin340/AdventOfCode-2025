#include <stdio.h>

typedef struct {
    int tick;
    int max;
} Dial;

typedef enum {
    DIAL_LEFT = -1,
    DIAL_RIGHT = 1,
} DialDirection;

int dial_tick_by(Dial* dial, DialDirection dire, int ticks) {
    // // lowkey my lazy approach
    // int full_counter = dial->max + 1;
    // int total_clicks = 0;
    //
    // for (int i = 0; i < ticks; ++i) {
    //     dial->tick = (dial->tick + dire) % full_counter;
    //
    //     if (dial->tick == 0) {
    //         ++total_clicks;
    //     }
    // }
    //
    // return total_clicks;

    int full_counter = dial->max + 1;
    int remainder = (ticks * dire) % full_counter;

    int total_clicks = ticks / full_counter;

    int prev_tick = dial->tick;
    int unbalanced_tick = dial->tick + remainder;
    dial->tick = (unbalanced_tick + full_counter) % full_counter;

    if ((prev_tick > 0 && unbalanced_tick < 0) || (unbalanced_tick > dial->max)) {
        ++total_clicks;
    }

    if (unbalanced_tick == 0) {
        ++total_clicks;
    }

    return total_clicks;
}

int main(void) {
    Dial dial = {.tick = 50, .max = 99};
    Dial* dial_ptr = &dial;

    FILE* input;
    if (fopen_s(&input, "inputs/day_1.txt", "r") != 0) {
        perror("can't open input for day 1 (inputs/day_1.txt): ");
        return 1;
    }

    int pointed_zero = 0;
    int clicked = 0;

    char dire_c;
    int ticks;
    while (fscanf_s(input, " %c%d", &dire_c, 1, &ticks) == 2) {
        DialDirection dire = (dire_c == 'L') ? DIAL_LEFT : DIAL_RIGHT;
        clicked += dial_tick_by(dial_ptr, dire, ticks);

        if (dial.tick == 0) {
            pointed_zero++;
        }
    }

    fclose(input);

    printf("current tick: %d\n", dial.tick);
    printf("pointed at zero: %d times\n", pointed_zero);
    printf("dial clicked a total of: %d times\n", clicked);

    return 0;
}
