#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdio.h>
#include "value.h"
#include "evaluate.h"

struct Value *builtin_quote(struct Value *argument, struct Value **env);
struct Value *builtin_lambda(struct Value *argument, struct Value **env);
struct Value *builtin_allocation(struct Value *argument, struct Value **env);
struct Value *builtin_bind(struct Value *argument, struct Value **env);
struct Value *builtin_extend(struct Value *argument, struct Value **env);
struct Value *builtin_env(struct Value *argument, struct Value **env);
struct Value *builtin_set(struct Value *argument, struct Value **env);

#endif

