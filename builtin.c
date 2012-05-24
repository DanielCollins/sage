#include "builtin.h"

struct Value *builtin_quote(struct Value *argument, struct Value **env)
{
  (void) env;
  return ((struct Pair*)argument->value)->car;
}

struct Value *builtin_lambda(struct Value *argument, struct Value **env)
{
  struct Value *arg, *body;
  arg = ((struct Pair*)argument->value)->car;
  body = ((struct Pair*)argument->value)->cdr;
  if (body->type != PAIR)
    return 0;
  body = ((struct Pair*)body->value)->car;
  return closure(arg, body, *env);
}

struct Value *builtin_allocation(struct Value *argument, struct Value **env)
{
  (void) argument;
  (void) env;
  printf("%d\n", memory_used);
  return nil();
}

struct Value *builtin_bind(struct Value *argument, struct Value **env)
{
  struct Value *name, *value;
  name = ((struct Pair*)argument->value)->car;
  value = ((struct Pair*)argument->value)->cdr;
  if (value->type != PAIR)
    return 0;
  value = ((struct Pair*)value->value)->car;
  evaluate(&value, env);
  bind(name, value, *env);
  return value;
}

struct Value *builtin_extend(struct Value *argument, struct Value **env)
{
  struct Value *name, *value;
  name = ((struct Pair*)argument->value)->car;
  value = ((struct Pair*)argument->value)->cdr;
  if (value->type != PAIR)
    return 0;
  value = ((struct Pair*)value->value)->car;
  evaluate(&value, env);
  *env = extend(name, value, *env);
  return value;
}

struct Value *builtin_env(struct Value *argument, struct Value **env)
{
  (void) argument;
  return *env;
}

