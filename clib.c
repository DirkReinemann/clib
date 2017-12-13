#include "clib.h"

char *string_replace(const char *value, const char *sequence, const char *replacement)
{
    char *result = (char *)malloc(1 * sizeof(char));
    result[0] = '\0';

    if (value == NULL || strlen(value) == 0) {
        return result;
    }

    size_t svalue = strlen(value);
    if (sequence == NULL || strlen(sequence) == 0) {
        result = (char *)realloc(result, (svalue + 1) * sizeof(char));
        strncpy(result, value, svalue);
        result[svalue] = '\0';
        return result;
    }

    char *match = (char *)value;
    size_t pos = 0;
    size_t rpos = 0;
    size_t sreplacement = strlen(replacement);
    size_t ssequence = strlen(sequence);
    while ((match = strcasestr(match, sequence)) != NULL) {
        size_t oldpos = pos;
        size_t smatch = strlen(match);
        pos = svalue - smatch;
        size_t length = pos - oldpos;
        result = (char *)realloc(result, (rpos + length + sreplacement) * sizeof(char));
        if (length > 0)
            strncpy(result + rpos, value + oldpos, length);
        strncpy(result + rpos + length, replacement, sreplacement);
        rpos = rpos + length + sreplacement;
        match++;
        pos += ssequence;
    }
    size_t rest = svalue - pos;
    result = (char *)realloc(result, (rpos + rest + 1) * sizeof(char));
    strncpy(result + rpos, value + pos, rest);
    rpos += rest;
    result[rpos] = '\0';
    return result;
}

void *measure_microseconds(unsigned long *microseconds, void *(*func)(void *data), void *data)
{
    struct timeval stop, start;
    gettimeofday(&start, NULL);
    data = func(data);
    gettimeofday(&stop, NULL);
    *microseconds = stop.tv_usec - start.tv_usec;
    return data;
}

void *traverse_directory(const char *path,
                         void *(*ondir)(const char *path, const char *dirname, void *data),
                         void *(*onfile)(const char *path, const char *filename, void *data),
                         void *data)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(path)))
        return data;
    if (!(entry = readdir(dir)))
        return data;

    do {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            if (ondir != NULL)
                data = ondir(path, entry->d_name, data);

            size_t size = strlen(path) + strlen(entry->d_name) + 2;
            char dirpath[size];
            snprintf(dirpath, size, "%s/%s", path, entry->d_name);
            data = traverse_directory(dirpath, ondir, onfile, data);
        } else {
            if (onfile != NULL)
                data = onfile(path, entry->d_name, data);
        }
    } while ((entry = readdir(dir)) != NULL);
    closedir(dir);
    return data;
}
