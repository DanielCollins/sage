#ifndef BOOLEAN_H
#define BOOLEAN_H

#include <stdlib.h>
#include "value.h"

struct Value Truthy;
struct Value Falsey;

struct Value *boolean(int);
void print_boolean(int*);
struct Value *equal_boolean(int *a, int *b);

#endif

