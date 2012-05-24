#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include "value.h"
#include <stdlib.h>
#include "generic.h"

struct Frame
{
  struct Value *name, *value, *parent;
};

void print_enviroment(struct Frame *f);
struct Value *extend(struct Value *name, struct Value *value, struct Value *env);
struct Value *bind(struct Value *name, struct Value *value, struct Value *env);
struct Value *resolve(struct Value *name, struct Value *env);
struct Value *equal_enviroment(struct Frame *a, struct Frame *b);

#endif

