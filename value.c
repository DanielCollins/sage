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

