/*
 * name:wenford 
 * email:26597925@qq.com
 *
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include "Mem.h"

void exit_program(int ret);
char *str_split(char **stringp, const char *delim);
char *str_dup(const char *s);
char *parse_key(const char *s);
void *grow_array(void *array, int elem_size, int *size, int new_size);
#define GROW_ARRAY(array, nb_elems)\
    array = grow_array(array, sizeof(*array), &nb_elems, nb_elems + 1)
