#ifndef GENERIC_H
#define GENERIC_H

#include <stdio.h>
#include "value.h"

void print_value(struct Value *v);
struct Value *equal(struct Value *a, struct Value *b);

#endif

