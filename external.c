#include "external.h"

struct Value *external(struct Value *(*implementation)(struct Value *argument,
                                                       struct Value *env))
{
  struct External *e;
  if (!(e = allocate(sizeof(struct External))))
    return 0;
  e->implementation = implementation;
  return make_value(EXTERNAL, e);
}

void print_external()
{
  printf("#<closure>");
}

struct Value *equal_external(struct External *a, struct External *b)
{
  if (a->implementation == b->implementation)
    return boolean(1);
  return boolean(0);
}

void free_external(struct External *e)
{
  deallocate(e, sizeof(struct External));
}


