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
#include "intrinsic.h"
#include "builtin.h"
#include "integer.h"
#include "character.h"

enum Type
{
  NIL,
  PAIR,
  SYMBOL,
  ENVIROMENT,
  BOOLEAN,
  CLOSURE,
  INTRINSIC,
  INTEGER,
  CHARACTER  
};

struct Value
{
  void *value;
  enum Type type;
  size_t references;
};

size_t memory_used;

void *allocate(size_t size);
void deallocate(void *ptr, size_t size);
void *reallocate(void *ptr, size_t old_size, size_t new_size);

void ref_inc(struct Value *v);
void ref_dec(struct Value *v);

struct Value *make_value(enum Type type, void *value);
void free_value(struct Value *v);

#endif

