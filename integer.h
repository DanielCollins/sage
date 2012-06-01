#ifndef INTEGER_H
#define INTEGER_H

#include "value.h"

struct Value *make_integer(int x);
void print_integer(int *x);
struct Value *equal_integer(int *a, int *b);
void free_integer(int *i);

#endif

