#include "value.h"

void *allocate(size_t size)
{
  void *r;
  r = malloc(size);
  if (r)
    ++memory_used;
  return r;
}

void deallocate(void *ptr)
{
  --memory_used;
  free(ptr);
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

