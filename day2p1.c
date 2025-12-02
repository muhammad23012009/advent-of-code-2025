#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "common.h"

long s_total_sum = 0;

bool is_repeating_string(char *str)
{
    /* Strings will always have 2 repeated halves, so split in half and compare both strings. */
    size_t len = strlen(str);
    if (len % 2 != 0)
        return false;

    char *substr = str + (len / 2);
    return strncmp(str, substr, len / 2) == 0;
}

void parse_ids(char *line)
{
    char *saveptr;
    char *first_id = __strtok_r(line, "-", &saveptr);
    char *second_id = __strtok_r(NULL, "-", &saveptr);

    long id1 = strtol(first_id, NULL, 10);
    long id2 = strtol(second_id, NULL, 10);

    while (id1++ <= id2) {
        char *tmp_str;
        asprintf(&tmp_str, "%ld", id1);
        if (is_repeating_string(tmp_str)) {
            s_total_sum += id1;
        }
    }
}

int main(void)
{
    void *data = read_from_file("day2_input", NULL);

    foreach_split_string(data, ",", parse_ids);

    printf("Total Sum of Repeating IDs: %ld\n", s_total_sum);
    free(data);
    return 0;
}