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

#endif

