#include "symbol.h"

struct Value *symbol(char *name)
{
  return make_value(SYMBOL, name);
}

void print_symbol(Symbol s)
{
  printf("%s", s);
}

struct Value *equal_symbol(Symbol a, Symbol b)
{
  if (!strcmp(a, b))
    return boolean(1);
  return boolean(0);
}

