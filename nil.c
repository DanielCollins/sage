#include "nil.h"

struct Value *nil(void)
{
  return &Nil;
}

void print_nil(void)
{
  fputs("()", stdout);
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

