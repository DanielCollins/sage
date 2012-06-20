#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdio.h>
#include "value.h"
#include "evaluate.h"
#include "sage.h"

void builtin_quote(struct Value *argument, struct Value *env,
  struct Value **out);
void builtin_lambda(struct Value *argument, struct Value *env,
  struct Value **out);
void builtin_allocation(struct Value *argument, struct Value *env,
  struct Value **out);
void builtin_bind(struct Value *argument, struct Value *env,
  struct Value **out);
void builtin_extend(struct Value *argument, struct Value *env,
  struct Value **out);
void builtin_env(struct Value *argument, struct Value *env, struct Value **out);
void builtin_set(struct Value *argument, struct Value *env, struct Value **out);
void builtin_eval(struct Value *argument, struct Value *env,
  struct Value **out);
void builtin_nilp(struct Value *argument, struct Value *env,
 struct Value **out);
void builtin_exit(struct Value *argument, struct Value *env,
  struct Value **out);

#endif

