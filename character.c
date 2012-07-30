#include "character.h"

struct Value *character(int c)
{
  struct Character *ch;
  if (!(ch = allocate(sizeof(struct Character))))
    return 0;
  ch->code = c;
  return make_value(CHARACTER, ch);
}

void print_character(struct Character *c)
{
  printf("'%c'", c->code);
}

struct Value *equal_character(struct Character *a, struct Character *b)
{
  if (a->code == b->code)
    return boolean(1);
  return boolean(0);
}

void free_character(struct Character *c)
{
  deallocate(c, sizeof(struct Character));
}

