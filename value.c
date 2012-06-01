#include "value.h"

void *allocate(size_t size)
{
  void *r;
  r = malloc(size);
  if (r)
    memory_used += size;
  return r;
}

void deallocate(void *ptr, size_t size)
{
printf("p: %p\n", ptr);
  free(ptr);
  memory_used -= size;
}

struct Value *make_value(enum Type type, void *value)
{
  struct Value *result;
  if (!(result = allocate(sizeof(struct Value))))
    return 0;
  result->type = type;
  result->value = value;
  result->references = 0;
  return result;
}

void free_value(struct Value *v)
{
  deallocate(v, sizeof(struct Value));
}

void ref_inc(struct Value *v)
{

printf("inc ");
print_value(v);
printf("\n");

  ++v->references;
}

void ref_dec(struct Value *v)
{
if (!v) printf("!!!NULL!!!\n");
printf("dec ");
print_value(v);
printf(" %d", v->references - 1);
printf("\n");
  --v->references;
  if (!v->references)
    collect(v);
}

