#ifndef CLIB_H_
#define CLIB_H_

#define _GNU_SOURCE

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define UNUSED(x) (void)(x)

/**
 * @brief Replaces all occurences of @sequence with @replacement.
 *
 * The returned string is allocated and has to be freed by the user. When the given @value 
 * is NULL or EMPTY an empty string is returned that also has to be freed. When the given 
 * @sequence is NULL or EMPTY a copy of the given input value is returned that also has to 
 * be freed.
 *
 * @param value the string that contains the @sequence
 * @param sequence the string that has to be replaced by @replacement
 * @param replacement the string that replaced all @sequence
 *
 * @return an allocated string where all @sequence have been replaced by @replacement
*/
char *string_replace(const char *value, const char *sequence, const char *replacement);

/**
 * @brief Measures the time for a given function.
 *
 * Takes a timestamp before and after calling the function @func. The functiona accepts a 
 * pointer @data so that the user can pass any data he wants to the function.
 *
 * @param microseconds a pointer to the duration of the function @func
 * @param func a function that needs to be measured
 * @param data any given data that needs to be passed to the function @func
 *
*/
void *measure_microseconds(unsigned long *microseconds, void *(*func)(void *data), void *data);

/**
 * @brief Recursively traverses a directory and all subdirectories.
 *
 * Takes a @path to the root directory that needs to be traversed. Takes a function @ondir 
 * that is called when a directory occurs and a function @onfile that is called when a file 
 * occurs. The function accepts a pointer @data so that the user can pass any data he wants 
 * to the functions @ondir and @onfile. Both functions @ondir and @onfile receive a string 
 * with the current pathname and the given @data. The function @onfile receives a string with 
 * the current @filename and @ondir a string with the current @dirname.
 *
 * @param path the directory that needs to be traversed
 * @param ondir the function that is called when a directory occurs
 * @param onfile the function that is called when a file occurs
 * @param data the custom data that needs the user wants to pass
*/
void *traverse_directory(const char *path, 
                         void *(*ondir)(const char *path, const char *dirname, void *data),
                         void *(*onfile)(const char *path, const char *filename, void *data),
                         void *data);

#endif 
