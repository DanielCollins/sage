#include "builtin.h"

void builtin_quote(struct Value *argument, struct Value *env,
   struct Value **out)
{
  (void) env;
  *out = ((struct Pair*)argument->value)->car;
}

void builtin_lambda(struct Value *argument, struct Value *env, 
 struct Value **out)
{
  struct Value *arg, *body;
  arg = ((struct Pair*)argument->value)->car;
  body = ((struct Pair*)argument->value)->cdr;
  if (body->type != PAIR)
    return;
  body = ((struct Pair*)body->value)->car;
  *out = closure(arg, body, env);
}

void builtin_allocation(struct Value *argument, struct Value *env,
  struct Value **out)
{
  (void) argument;
  (void) env;
  *out = make_integer(memory_used); 
}

void builtin_bind(struct Value *argument, struct Value *env, struct Value **out)
{
  struct Value *name, *value;
  name = ((struct Pair*)argument->value)->car;
  value = ((struct Pair*)argument->value)->cdr;
  if (value->type != PAIR)
    return;
  value = ((struct Pair*)value->value)->car;
  evaluate(value, env, &value);
  bind(name, value, env);
  *out = value;
}

void builtin_extend(struct Value *argument, struct Value *env,
  struct Value **out)
{
  struct Value *name, *value;
  name = ((struct Pair*)argument->value)->car;
  value = ((struct Pair*)argument->value)->cdr;
  if (value->type != PAIR)
    return;
  value = ((struct Pair*)value->value)->car;
  evaluate(value, env, &value);
  extend(name, value, env);
  *out = value;
}

void builtin_set(struct Value *argument, struct Value *env, struct Value **out)
{
  struct Value *name, *value;
  name = ((struct Pair*)argument->value)->car;
  value = ((struct Pair*)argument->value)->cdr;
  if (value->type != PAIR)
    return;
  value = ((struct Pair*)value->value)->car;
  evaluate(value, env, &value);
  bind(name, value, env);
  *out = value;
}

void builtin_env(struct Value *argument, struct Value *env, struct Value **out)
{
  (void) argument;
  *out = env;
}

void builtin_eval(struct Value *argument, struct Value *env,
  struct Value **out)
{
  struct Value *exp, *e;
  exp = ((struct Pair*)argument->value)->car;
  e = ((struct Pair*)argument->value)->cdr;
  if (e->type == PAIR)
  {
    e = ((struct Pair*)e->value)->car;
    evaluate(e, env, out);
  }
  else
  {
    e = env;
    evaluate(exp, e, out);
  }
}

void builtin_nilp(struct Value *argument, struct Value *env,
  struct Value **out)
{
  struct Value *exp;
  (void) env;
  exp = ((struct Pair*)argument->value)->car;
  evaluate(exp, env, &exp);
  if (exp->type == NIL)
  {
    *out = boolean(1);
    return;
  }
  *out = boolean(0);
}

void builtin_exit(struct Value *argument, struct Value *env, struct Value **out)
{
  (void) argument;
  (void) env;
  (void) out;
  psage_snuff();
}

