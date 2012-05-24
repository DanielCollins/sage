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

