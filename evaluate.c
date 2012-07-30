#include "evaluate.h"

struct Value *match(struct Value *pattern, struct Value *term,
                      struct Value *env)
{
  match_top:
  if (!pattern || !term)
     return 0;
  switch (pattern->type)
  {
    case SYMBOL:
      return extended(pattern, term, env);
    case PAIR:
      env = match(((struct Pair*)pattern->value)->car,
                  ((struct Pair*)term->value)->car,
                   env);
      pattern = ((struct Pair*)pattern->value)->cdr;
      term = ((struct Pair*)term->value)->cdr;
      goto match_top;
    default:
      if (*((int*)equal(pattern, term)->value))
        return env;
      fprintf(stderr, "no match\n");
      return 0; 
  }
}

void evlis(struct Value *l, struct Value *env, struct Value **out)
{
  struct Value *i, *o, *e, *t;
  o = e = 0;
  for (i = l; i->type == PAIR; i = ((struct Pair*)i->value)->cdr)
  {
    evaluate(((struct Pair*)i->value)->car, env, &t);
    if (o)
    {
      set_cdr((struct Pair*)e->value, pair(t, 0));
      e = ((struct Pair*)e->value)->cdr;
    }
    else
      o = e = pair(t, 0);
  }
  evaluate(i, env, &t);
  if (o)
    set_cdr((struct Pair*)e->value, t);
  else
    o = t;
  *out = o;
}

void evaluate(struct Value *exp, struct Value *env, struct Value **out)
{
  eval_top:
  switch (exp->type)
  {
    case PAIR:
      {
        struct Value *operator, *argument;
        operator = ((struct Pair*)exp->value)->car;
        evaluate(operator, env, &operator);
        if (!operator)
        {
          fprintf(stderr, "could not produce operator\n");
          return;
        }
        set_car(((struct Pair*)exp->value), operator);
        switch (operator->type)
        {
          case CLOSURE:
            {
              struct Closure *c;
              c = (struct Closure*)operator->value;
              argument = ((struct Pair*)exp->value)->cdr;
              evlis(argument, env, &argument);
              if (!(env = match(c->args, argument, c->env)))
              {
                fprintf(stderr, "cannot combine\n");
                return;
              }
              exp = c->body;
              goto eval_top;
            }
          case INTRINSIC:
            {
              ((struct Intrinsic*)operator->value)->implementation
                (((struct Pair*)exp->value)->cdr, env, out);
              return;
            }
          default:
            fprintf(stderr, "non operative\n");
            print_value(operator);
            return;
        }
      }
    case SYMBOL:
      {
        struct Value *t;
        if (!(t = resolve(exp, env)))
        {
          fprintf(stderr, "could not resolve\n");
          return;
        }
        *out = t;
        return;
      }
    default:
      *out = exp;
      return;
  }
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
