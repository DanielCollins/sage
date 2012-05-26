#ifndef EXTERNAL_H
#define EXTERNAL_H

#include <stdlib.h>
#include "value.h"

struct External
{
  struct Value *(*implementation) (struct Value *argument, struct Value *env);
};

struct Value *external(struct Value *(*implementation)(struct Value *argument,
                                                       struct Value *env));
void print_external();
struct Value *equal_external(struct External *a, struct External *b);

#endif

