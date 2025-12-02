#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

static int zero_hit_count = 0;
/* Position will always stay between 0 and 99 */
static int position = 50;

/* Should probably clean this up later */
void go_left(int steps)
{
    while (steps-- > 0) {
        if (position - 1 < 0) {
            position = 99;
            continue;
        }

        position--;
        if (position == 0 && steps > 0) {
            zero_hit_count++;
        }
    }

    if (position == 0)
        zero_hit_count++;
}

void go_right(int steps)
{
    while (steps-- > 0) {
        if (position + 1 > 99) {
            position = 0;
            if (steps > 0)
                zero_hit_count++;
            continue;
        }

        position++;
    }

    if (position == 0)
        zero_hit_count++;
}

void parse_line(char *line)
{
    char direction;
    int steps;

    if (sscanf(line, "%c %d", &direction, &steps) != 2) {
        fprintf(stderr, "Error: Invalid line format: %s\n", line);
        return;
    }

    printf("Direction: %c, Steps: %d\n", direction, steps);
    if (direction == 'L') {
        go_left(steps);
    } else if (direction == 'R') {
        go_right(steps);
    } else {
        fprintf(stderr, "Error: Unknown direction: %c\n", direction);
    }
}

int main(void)
{
    void *data = read_from_file("day1_input", NULL);

    foreach_split_string(data, "\n", parse_line);

    printf("Final Position: %d\n", position);
    printf("Zero Hit Count: %d\n", zero_hit_count);

    free(data);
}