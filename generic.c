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
      print_enviroment((struct Enviroment*) v->value);
      return;
    case BOOLEAN:
      print_boolean((int*) v->value);
      return;
    case CLOSURE:
      print_closure((struct Closure*) v->value);
      return;
    case INTRINSIC:
      print_intrinsic();
      return;
    case INTEGER:
      print_integer((int*) v->value);
      return;
    case CHARACTER:
      print_character((struct Character*) v->value);
      return;
    case OPERATOR:
      print_operator((struct Operator*) v->value);
      break;
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
      return equal_enviroment((struct Enviroment*) a->value,
                              (struct Enviroment*) b->value);
    case BOOLEAN:
      return equal_boolean((int*) a->value, (int*) b->value);
    case CLOSURE:
      return equal_closure((struct Closure*) a->value,
                           (struct Closure*) b->value);
    case INTRINSIC:
      return equal_intrinsic((struct Intrinsic*) a->value,
                            (struct Intrinsic*) b->value);
    case INTEGER:
      return equal_integer((int*) a->value, (int*) b->value);
    case CHARACTER:
      return equal_character((struct Character*) a->value, (struct Character*) b->value);
    case OPERATOR:
      return equal_operator((struct Operator*) a->value,
                            (struct Operator*) b->value);
    default:
      fprintf(stderr, "equal: unkown type\n");
      return 0; 
  }  
}

void collect(struct Value *v)
{
  if (!v)
    return;
  switch (v->type)
  {
    case PAIR:
      free_pair((struct Pair*) v->value);
      break;
    case SYMBOL:
      free_symbol((Symbol) v->value);
      break;
    case ENVIROMENT:
      free_enviroment((struct Enviroment*) v->value);
      break;
    case CLOSURE:
      free_closure((struct Closure*) v->value);
      break;
    case INTRINSIC:
      free_intrinsic((struct Intrinsic*) v->value);
      break;
    case INTEGER:
      free_integer((int*) v->value);
      break;
    case CHARACTER:
      free_character((struct Character*) v->value);
      break;
    case OPERATOR:
      free_operator((struct Operator*) v->value);
      break;
    case NIL:
    case BOOLEAN:
      return;
  }
  free_value(v);
}

