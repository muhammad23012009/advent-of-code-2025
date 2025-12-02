#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

static int zero_hit_count = 0;
/* Position will always stay between 0 and 99 */
static int position = 50;

void parse_line(char *line)
{
    char direction;
    int steps;

    if (sscanf(line, "%c %d", &direction, &steps) != 2) {
        fprintf(stderr, "Error: Invalid line format: %s\n", line);
        return;
    }

    if (direction == 'L') {
        position -= steps;
    } else if (direction == 'R') {
        position += steps;
    } else {
        fprintf(stderr, "Error: Unknown direction: %c\n", direction);
    }

    position %= 100;
    if (position == 0)
        zero_hit_count++;
}

int main(void)
{
    void *data = read_from_file("day1_input", NULL);

    foreach_split_string(data, "\n", parse_line);

    printf("Final Position: %d\n", position);
    printf("Zero Hit Count: %d\n", zero_hit_count);

    free(data);
}