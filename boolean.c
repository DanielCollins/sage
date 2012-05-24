#include "boolean.h"

struct Value *boolean(int b)
{
  if (b)
    return &Truthy;
  return &Falsey;  
}

void print_boolean(int *b)
{
  if (!*b)
    printf("#f");
  else
    printf("#t");
}

struct Value *equal_boolean(int *a, int *b)
{
  if (*a == *b)
    return boolean(1);
  return boolean(0);
}
 
