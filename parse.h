#ifndef PARSE_H
#define PARSE_H

#include <ctype.h>
#include "value.h"

struct Value *parse_list(FILE *s);
struct Value *parse_expression(FILE *s);
struct Value *parse_symbol(FILE *s);

#endif

