#include "intrinsic.h"

struct Value *intrinsic(void (*implementation)(struct Value *argument,
                                              struct Value *env,
                                              struct Value **out))
{
  struct Intrinsic *e;
  if (!(e = allocate(sizeof(struct Intrinsic))))
    return 0;
  e->implementation = implementation;
  return make_value(INTRINSIC, e);
}

void print_intrinsic()
{
  printf("#<closure>");
}

struct Value *equal_intrinsic(struct Intrinsic *a, struct Intrinsic *b)
{
  if (a->implementation == b->implementation)
    return boolean(1);
  return boolean(0);
}

void free_intrinsic(struct Intrinsic *e)
{
  deallocate(e, sizeof(struct Intrinsic));
}


