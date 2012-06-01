#ifndef PAIR_H
#define PAIR_H

#include <stdlib.h>
#include <stdio.h>
#include "value.h"
#include "generic.h"
#include "boolean.h"

struct Pair
{
  struct Value *car, *cdr;
};

struct Value *pair(struct Value *car, struct Value *cdr);
void set_car(struct Pair *p, struct Value *v);
void set_cdr(struct Pair *p, struct Value *v);
void print_pair(struct Pair *p);
struct Value *equal_pair(struct Pair *a, struct Pair *b);
void free_pair(struct Pair *p);

#endif

