#ifndef SAGE_H
#define SAGE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "value.h"
#include "generic.h"
#include "parse.h"
#include "enviroment.h"
#include "evaluate.h"

struct Value *toplevel;

void psage_init(void);
void psage_snuff(void);

void builtin_exit(struct Value *argument, struct Value *env,
  struct Value **out);

#endif

