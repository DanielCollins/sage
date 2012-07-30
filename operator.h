#ifndef OPERATOR_H
#define OPERATOR_H

#include <stdlib.h>
#include "value.h"

struct Operator
{
  struct Value *args, *body, *env;
};

struct Value *operator(struct Value *args, struct Value *body,
                         struct Value *env);
void print_operator();
struct Value *equal_operator(struct Operator *a, struct Operator *b);
void free_operator(struct Operator*);

void builtin_operator(struct Value *argument, struct Value *env,
  struct Value **out);

#endif

