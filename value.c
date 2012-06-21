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

void *reallocate(void *ptr, size_t old_size, size_t new_size)
{
  memory_used += (ssize_t) new_size - old_size;
  return realloc(ptr, new_size);
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
  ++v->references;
}

void ref_dec(struct Value *v)
{
  --v->references;
  if (!v->references)
    collect(v);
}

