#include "nil.h"

struct Value *nil(void)
{
  return &Nil;
}

void print_nil(void)
{
  fputs("()", stdout);
}

