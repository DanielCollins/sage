#include "sage.h"

#define SYM(name) (symbol(strcpy(allocate(sizeof(char) * (strlen(name) + 1)), \
 name)))

#define REGISTER(name, value) (toplevel = extend(SYM(name), (value), toplevel))

struct Value *v;

void toplevel_init(void)
{
  toplevel = make_enviroment();
  ref_inc(toplevel);
  REGISTER("nil", &Nil);
  REGISTER("true", boolean(1));
  REGISTER("false", boolean(0));
  REGISTER("quote", intrinsic(&builtin_quote));
  REGISTER("lambda",  intrinsic(&builtin_lambda));
  REGISTER("allocation", intrinsic(&builtin_allocation));
  REGISTER("define", intrinsic(&builtin_extend));  
  REGISTER("enviroment", intrinsic(&builtin_env));
  REGISTER("set!", intrinsic(&builtin_set));
  REGISTER("evaluate", intrinsic(&builtin_eval));
  REGISTER("nil?", intrinsic(&builtin_nilp));
  REGISTER("halt", intrinsic(&builtin_exit));
  REGISTER("operator", intrinsic(&builtin_operator));
}

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
  toplevel_init();
}

void psage_snuff(void)
{
  extern struct Value Truthy, Falsey;
  ref_dec(v);
  ref_dec(toplevel);
  deallocate(Truthy.value, sizeof(int));
  deallocate(Falsey.value, sizeof(int));
  exit(EXIT_SUCCESS);
}

void builtin_exit(struct Value *argument, struct Value *env, struct Value **out)
{
  (void) argument;
  (void) env;
  (void) out;
  psage_snuff();
}

int main(int argc, char *argv[])
{
  struct Value *out;
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

  printf("lithp ith lithening\n");
  while (1)
  {
    printf("> ");
    if (!(v = parse_expression(istream)))
    {
      fprintf(stderr, "could not parse\n");
      continue;
    }
    out = 0;
    ref_inc(v);
    evaluate(v, toplevel, &out);
    ref_inc(out);
    ref_dec(v);
    print_value(out);
    ref_dec(out);
    printf("\n");
  }
  psage_snuff();
  return EXIT_FAILURE;
}

