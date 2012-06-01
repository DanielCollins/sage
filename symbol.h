#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "value.h"

typedef char *Symbol;

struct Value *symbol(char *name);
void print_symbol(Symbol);
struct Value *equal_symbol(Symbol a, Symbol b);
void free_symbol(Symbol s);


#endif

