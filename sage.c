#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "value.h"
#include "generic.h"
#include "parse.h"
#include "enviroment.h"
#include "evaluate.h"

void psage_init(void)
{
  extern struct Value Nil, Truthy, Falsey;
  extern size_t memory_used;
  memory_used = 0;
  Nil.value = 0;
  Nil.type = NIL;
  Truthy.type = BOOLEAN;
  Truthy.value = allocate(sizeof(int));
  *((int*)Truthy.value) = 1;
  Falsey.type = BOOLEAN;
  Falsey.value = allocate(sizeof(int));
  *((int*)Falsey.value) = 0;
}

int main(int argc, char *argv[])
{
  struct Value *v;
  struct Value *toplevel;
  FILE *istream;

  if (argc == 1)
  {
    istream = stdin;
  }
  else if (argc == 2)
  {
    if (!(istream = fopen(argv[1], "r")))
    {
      fprintf(stderr, "could not open file %s for reading\n", argv[1]);
      return EXIT_FAILURE;
    }
  }
  else
  {
    fprintf(stderr, "usage: %s [file]\n", argv[0]);
    return EXIT_FAILURE;
  }

  psage_init();

  toplevel = make_enviroment();
  toplevel = extend(symbol("nil"), &Nil, toplevel);
  toplevel = extend(symbol("true"), boolean(1), toplevel);
  toplevel = extend(symbol("false"), boolean(0), toplevel);
  toplevel = extend(symbol("quote"), external(&builtin_quote), toplevel);
  toplevel = extend(symbol("lambda"), external(&builtin_lambda), toplevel);
  toplevel = extend(symbol("allocation"), external(&builtin_allocation),
    toplevel);
  toplevel = extend(symbol("define"), external(&builtin_extend), toplevel);
  toplevel = extend(symbol("enviroment"), external(&builtin_env), toplevel);

  printf("lithp ith lithening\n");
  while (1)
  {
    printf("> ");
    if (!(v = parse_expression(istream)))
    {
      fprintf(stderr, "could not parse\n");
      continue;
    }
    evaluate(&v, &toplevel);
    if (!v)
    {
      fprintf(stderr, "could not evaluate\n");
      continue;    
    }
    print_value(v);
    printf("\n");
  }
  return EXIT_SUCCESS;
}

