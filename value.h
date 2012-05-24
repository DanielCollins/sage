#ifndef VALUE_H
#define VALUE_H

#include <stdlib.h>
#include <stdio.h>
#include "nil.h"
#include "pair.h"
#include "symbol.h"
#include "enviroment.h"
#include "boolean.h"
#include "closure.h"
#include "external.h"
#include "builtin.h"

enum Type
{
  NIL,
  PAIR,
  SYMBOL,
  ENVIROMENT,
  BOOLEAN,
  CLOSURE,
  EXTERNAL  
};

struct Value
{
  void *value;
  enum Type type;
  size_t references;
};

size_t memory_used;

void *allocate(size_t size);
void deallocate(void *ptr);

struct Value *make_value(enum Type type, void *value);

#endif

