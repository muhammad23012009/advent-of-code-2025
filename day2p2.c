#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "common.h"

long s_total_sum = 0;

bool is_repeating_string(char *str)
{
    size_t len = strlen(str);
    /* sub_len will be the maximum size of the chunks to compare */
    for (size_t sub_len = 1; sub_len <= len / 2; sub_len++) {
        if (len % sub_len != 0)
            continue;

        bool all_match = true;

        /* Chop the original string into two chunks of length i and then compare them to find patterns,
         * starting from index sub_len for the chunked string. For example:
         * "85858585":
         * It will begin by initializing sub_len = 1, which would make the substring below point to '5'.
         * Since str and str + 1 will not match, it will increment sub_len to 2.
         * Now str and str + 2 will be compared ('85' and '85'), which match. It will then continue to compare the rest of the chunks
         * ('85' and '85') until the end of the string is reached, by incrementing i with the chunk length,
         * confirming that the entire string is made up of repeating substrings of '85'.
         */
        for (size_t i = sub_len; i < len; i += sub_len) {
            /* If the chunk doesn't match, increment the starting position and try again */
            if (strncmp(str, str + i, sub_len)) {
                all_match = false;
                break;
            }
        }

        if (all_match)
            return true;
    }
    return false;
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