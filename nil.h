#include "value.h"

#include <stdio.h>
#ifndef NIL_H
#define NIL_H

struct Value Nil;

struct Value *nil(void);
void print_nil();

void builtin_nilp(struct Value *argument, struct Value *env,
 struct Value **out);

#endif

