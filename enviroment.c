#include "enviroment.h"

struct Value *make_enviroment(void)
{
  struct Enviroment *e;
  if (!(e = allocate(sizeof(struct Enviroment))))
    return 0;
  e->root = 0;
  return make_value(ENVIROMENT, e);
}

struct Value *extend(struct Value *name, struct Value *value, struct Value *env)
{
  struct Frame *f;
  if (!(f = allocate(sizeof(struct Frame))))
    return 0;
  f->name = name;
  f->value = value;
  f->parent = ((struct Enviroment*)env->value)->root;
  ((struct Enviroment*)env->value)->root = f;
  return env;
}

struct Value *bind(struct Value *name, struct Value *value, struct Value *env)
{
  (void)value;
  (void)env;
  return name;
}

void print_enviroment(struct Enviroment *e)
{
  struct Frame *i;
  printf("#<enviroment\n");
  i = e->root;
  while (i)
  {
    printf("  ");
    print_value(i->name);
    printf(" => ");
    print_value(i->value);
    if (i->parent)
    {
      printf(",\n");
      i = i->parent;
    }
    else
    {
      printf(" >");
      return;
    }
  } 
}

struct Value *resolve(struct Value *name, struct Value *env)
{
  struct Frame *current;
  current = ((struct Enviroment*)env->value)->root;
  while (current)
  {
    if (*((int*)(equal(current->name, name)->value)))
      return current->value;
    current = current->parent; 
  }
  return 0;
}

struct Value *equal_enviroment(struct Enviroment *a, struct Enviroment *b)
{
  struct Frame *aa, *bb;
  aa = a->root;
  bb = b->root;

  while (1)
  {
    if (aa == bb)
      return boolean(1);

    if (!aa || !bb)
      return boolean(0);

    if (!equal(aa->name, bb->name)->value ||
        !equal(aa->value, bb->name)->value)
      return boolean(0);

    aa = aa->parent;
    bb = bb->parent;
  }
}

