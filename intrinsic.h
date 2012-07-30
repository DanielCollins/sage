#ifndef INTRINSIC_H
#define INTRINSIC_H

#include <stdlib.h>
#include "value.h"

struct Intrinsic
{
  void (*implementation) (struct Value *argument, struct Value *env,
    struct Value **out);
};

struct Value *intrinsic(void (*implementation)(struct Value *argument,
                                              struct Value *env,
                                              struct Value **out));
void print_intrinsic();
struct Value *equal_intrinsic(struct Intrinsic *a, struct Intrinsic *b);
void free_intrinsic(struct Intrinsic *e);

#endif

