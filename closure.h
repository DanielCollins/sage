#ifndef CLOSURE_H
#define CLOSURE_H

#include <stdlib.h>
#include "value.h"

struct Closure
{
  struct Value *args, *body, *env;
};

struct Value *closure(struct Value *args, struct Value *body,
                        struct Value *env);
void print_closure();
struct Value *equal_closure(struct Closure *a, struct Closure *b);

#endif

