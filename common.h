#pragma once

#include <stdlib.h>
extern void *read_from_file(const char *filename, size_t *out_size);
extern void foreach_split_string(const char *line, const char *delim,
                          void (*callback)(char *token));