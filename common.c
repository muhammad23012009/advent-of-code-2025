#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void *read_from_file(const char *filename, size_t *out_size)
{
    struct stat st;
    void *ret;
    FILE *f = fopen(filename, "r");
    if (!f)
        return NULL;

    stat(filename, &st);
    ret = malloc(st.st_size);
    fread(ret, st.st_size, 1, f);
    fclose(f);

    if (out_size)
        *out_size = st.st_size;

    return ret;
}

void foreach_split_string(const char *line, const char *delim,
                          void (*callback)(char *token))
{
    char *line_copy = strdup(line);
    char *saveptr;
    char *token = __strtok_r(line_copy, delim, &saveptr);

    while (token) {
        callback(token);
        token = __strtok_r(NULL, delim, &saveptr);
    }

    free(line_copy);
}