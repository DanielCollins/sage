#include "integer.h"

struct Value *make_integer(int x)
{
  int *v;
  if (!(v = allocate(sizeof(int))))
    return 0;
  *v = x;
  return make_value(INTEGER, v);
}

void print_integer(int *x)
{
  printf("%d", *x);
}

struct Value *equal_integer(int *a, int *b)
{
  if (*a == *b)
    return boolean(1);
  return boolean(0);
}

