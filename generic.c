#include "generic.h"

void print_value(struct Value *v)
{
  switch (v->type)
  {
    case NIL:
      print_nil();
      return;
    case PAIR:
      print_pair((struct Pair*) v->value);
      return;
    case SYMBOL:
      print_symbol((Symbol) v->value);
      return;
    case ENVIROMENT:
      print_enviroment(v);
      return;
    case BOOLEAN:
      print_boolean((int*) v->value);
      return;
    case CLOSURE:
      print_closure((struct Closure*) v->value);
      return;
    case EXTERNAL:
      print_external();
      return;
    default:
      fprintf(stderr, "print_value: unkown type\n");
  }
}

struct Value *equal(struct Value *a, struct Value *b)
{
  if (a == b)
    return boolean(1);
  if (!a || !b)
    return boolean(0);
  if (a->type != b->type)
    return boolean(0);
  switch (a->type)
  {
    case NIL:
      return boolean(1);
    case PAIR:
      return equal_pair((struct Pair*) a->value, (struct Pair*) b->value);
    case SYMBOL:
      return equal_symbol((Symbol) a->value, (Symbol) b->value);
    case ENVIROMENT:
      return equal_enviroment((struct Frame*) a->value,
                              (struct Frame*) b->value);
    case BOOLEAN:
      return equal_boolean((int*) a->value, (int*) b->value);
    case CLOSURE:
      return equal_closure((struct Closure*) a->value,
                           (struct Closure*) b->value);
    case EXTERNAL:
      return equal_external((struct External*) a->value,
                            (struct External*) b->value);
    default:
      fprintf(stderr, "equal: unkown type\n");
      return 0; 
  }  
}

