#include "pair.h"

struct Value *pair(struct Value *car, struct Value *cdr)
{
  struct Pair *p;
  struct Value *result;
  if (!(p = allocate(sizeof(struct Pair))))
    return 0;
  p->car = car;
  p->cdr = cdr;
  result = make_value(PAIR, p);
  if (car)
    ++(*car).references;
  if (cdr)
    ++(*cdr).references;
  return result;
}

void set_car(struct Pair *p, struct Value *v)
{
  if (p->car)
    --p->car->references;
  p->car = v;
  ++v->references;
}

void set_cdr(struct Pair *p, struct Value *v)
{
  if (p->cdr)
    --p->cdr;
  p->cdr = v;
  ++v->references;
}

void print_pair(struct Pair *p)
{
  putchar('(');
  while (1)
  {
    print_value(p->car);
    if (p->cdr->type == NIL)
    {
      putchar(')');
      return; 
    }
    else
    {
      putchar(' ');
      if (p->cdr->type == PAIR)
      {
        p = (struct Pair*) p->cdr->value;
      }
      else
      {
        fputs(". ", stdout);
        print_value(p->cdr);
        putchar(')');
        return;
      }
    }
  }
}

struct Value *equal_pair(struct Pair *a, struct Pair *b)
{
  if (equal(a->car, b->car)->value && equal(a->cdr, b->cdr)->value)
    return boolean(1);
  return boolean(0);
}

