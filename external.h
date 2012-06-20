#ifndef EXTERNAL_H
#define EXTERNAL_H

#include <stdlib.h>
#include "value.h"

struct External
{
  void (*implementation) (struct Value *argument, struct Value *env,
    struct Value **out);
};

struct Value *external(void (*implementation)(struct Value *argument,
                                              struct Value *env,
                                              struct Value **out));
void print_external();
struct Value *equal_external(struct External *a, struct External *b);
void free_external(struct External *e);

#endif

