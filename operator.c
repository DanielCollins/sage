#include "operator.h"

struct Value *operator(struct Value *args, struct Value *body,
                        struct Value *env)
{
  struct Operator *o;
  if (!(o = allocate(sizeof(struct Operator))))
    return 0;
  o->args = args;
  o->body = body;
  o->env = env;
  ref_inc(args);
  ref_inc(body);
  ref_inc(env);
  return make_value(OPERATOR, o);
}

void print_operator()
{
  printf("#<closure>");
}

struct Value *equal_operator(struct Operator *a, struct Operator *b)
{
  if (*((int*) equal(a->args, b->args)->value) &&
      *((int*) equal(a->body, b->body)->value) &&
      *((int*) equal(a->env, b->env)->value))
    return boolean(1);
  return boolean(0);
}

void free_operator(struct Operator *c)
{
  ref_dec(c->args);
  ref_dec(c->body);
  ref_dec(c->env);
  deallocate(c, sizeof(struct Operator));
}

void builtin_operator(struct Value *argument, struct Value *env,
 struct Value **out)
{
  struct Value *arg, *body;
  arg = ((struct Pair*)argument->value)->car;
  body = ((struct Pair*)argument->value)->cdr;
  if (body->type != PAIR)
    return;
  body = ((struct Pair*)body->value)->car;
  *out = operator(arg, body, env);
}

