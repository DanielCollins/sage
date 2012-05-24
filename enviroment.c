#include "enviroment.h"

struct Value *extend(struct Value *name, struct Value *value, struct Value *env)
{
  struct Frame *f;
  if (!(f = allocate(sizeof(struct Frame))))
    return 0;
  f->name = name;
  f->value = value;
  f->parent = env;
  ++(*value).references;
  ++(*name).references;
  return make_value(ENVIROMENT, f);
}

struct Value *bind(struct Value *name, struct Value *value, struct Value *env)
{
/*  struct Frame *f;*/
(void)value;(void)env;
  return name;
}

void print_enviroment()
{
  printf("#<enviroment>\n");
}

struct Value *resolve(struct Value *name, struct Value *env)
{
  struct Value *current;
  current = env;
  while (current && current->type == ENVIROMENT)
  {
    if (*((int*)(equal(((struct Frame*)current->value)->name, name)->value)))
      return ((struct Frame*)current->value)->value;
    current = ((struct Frame*)current->value)->parent; 
  }
  return 0;
}

struct Value *equal_enviroment(struct Frame *a, struct Frame *b)
{
  if (equal(a->name, b->name)->value &&
      equal(a->value, b->value)->value &&
      equal(a->parent, b->parent)->value)
    return boolean(1);
  return boolean(0);
}

