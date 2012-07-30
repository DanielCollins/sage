#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdlib.h>
#include "value.h"

struct Character
{
  int code;
};

struct Value *character(int c);
void print_character(struct Character *c);
struct Value *equal_character(struct Character *a, struct Character *b);
void free_character(struct Character *c);

#endif


