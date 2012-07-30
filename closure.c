#include "closure.h"

struct Value *closure(struct Value *args, struct Value *body,
                       struct Value *env)
{
  struct Closure *c;
  if (!(c = allocate(sizeof(struct Closure))))
    return 0;
  c->args = args;
  c->body = body;
  c->env = env;
  ref_inc(args);
  ref_inc(body);
  ref_inc(env);
  return make_value(CLOSURE, c);
}

void print_closure()
{
  printf("#<closure>");
}

struct Value *equal_closure(struct Closure *a, struct Closure *b)
{
  if (*((int*)equal(a->args, b->args)->value) &&
      *((int*)equal(a->body, b->body)->value) &&
      *((int*)equal(a->env, b->env)->value))
    return boolean(1);
  return boolean(0);
}

void free_closure(struct Closure *c)
{
  ref_dec(c->args);
  ref_dec(c->body);
  ref_dec(c->env);
  deallocate(c, sizeof(struct Closure));
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

