#ifndef EVALUATE_H
#define EVALUATE_H

#include <stdio.h>
#include <stdlib.h>
#include "value.h"

void evaluate(struct Value *exp, struct Value *env, struct Value **out);

void builtin_eval(struct Value *argument, struct Value *env,
  struct Value **out);

#endif

