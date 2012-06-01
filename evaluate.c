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

void evlis(struct Value **l, struct Value *env)
{
  while (1)
  {
    if ((*l)->type == PAIR)
    {
      evaluate(&((struct Pair*)(*l)->value)->car, env);
      l = &((struct Pair*)(*l)->value)->cdr;
    }
    else
    {
      evaluate(l, env);
      return;
    }
  }
}

void evaluate(struct Value **exp, struct Value *env)
{
  eval_top:
  switch ((*exp)->type)
  {
    case PAIR:
      {
        struct Value *operator, *argument;
        operator = ((struct Pair*)(*exp)->value)->car;
        evaluate(&operator, env);
        if (!operator)
        {
          fprintf(stderr, "could not produce operator\n");
          *exp = 0;
          return;
        }
        switch (operator->type)
        {
          case CLOSURE:
            {
              struct Closure *c;
              c = (struct Closure*)operator->value;
              argument = ((struct Pair*)(*exp)->value)->cdr;
              evlis(&argument, env);
              if (!(env = match(c->args, argument, c->env)))
              {
                fprintf(stderr, "cannot combine\n");
                return;
              }
              ref_dec(*exp);
              *exp = c->body;
              goto eval_top;
            }
          case EXTERNAL:
            {
              struct Value *(*ii) (struct Value *argument, struct Value *env);
              struct Value *t;
              t = *exp;

(void) malloc(1);

              ii = ((struct External*)operator->value)->implementation;

             *exp = ii(((struct Pair*)(*exp)->value)->cdr, env);

printf("\n");
print_value(t);
printf("\n");
              return;
            }
          default:
            fprintf(stderr, "non operative\n");
            print_value(operator);
            *exp = 0;
            return;
        }
      }
    case SYMBOL:
      {
        struct Value *t;
        if (!(t = resolve(*exp, env)))
        {
          fprintf(stderr, "could not resolve\n");
          *exp = 0;
        }
        ref_dec(*exp);
        *exp = t;
      }
    default:
      return;
  }
}

