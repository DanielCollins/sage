#ifndef PARSE_H
#define PARSE_H

#include <ctype.h>
#include "value.h"

struct Value *parse_list(FILE *s);
struct Value *parse_expression(FILE *s);
struct Value *parse_symbol(FILE *s);
struct Value *parse_integer(FILE *s);
struct Value *parse_boolean(FILE *s);

#endif

