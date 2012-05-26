#include "parse.h"

void skip_whitespace(FILE *s)
{
  int c;
  while ((c = fgetc(s)) != EOF && isspace(c));
  ungetc(c, s);
}

struct Value *parse_list(FILE *s)
{
  struct Value *result, *current, *t;
  int c;

  result = current = 0;
  if ((c = fgetc(s)) == EOF || c != '(')
  {
    ungetc(c, s);
    return 0;
  }

  while (1)
  {
    if ((c = fgetc(s)) == EOF)
      return 0;

    if (result && !isspace(c) && c != ')')
    {
      ungetc(c, s);
      return 0;
    }
    else
      ungetc(c, s);

    skip_whitespace(s);

    if ((c = fgetc(s)) == EOF)
      return 0;

    if (c == '.')
    {
      if (!result)
        return 0;
      if (!(t = parse_expression(s)))
        return 0;
      set_cdr((struct Pair*)current->value, t);
      skip_whitespace(s);
      if ((c = fgetc(s)) == EOF)
        return 0;
      if (c != ')')
        return 0;
      return result;
    }
    else if (c == ')')
    {
      if (result)
      {
        set_cdr((struct Pair*)current->value, nil());
        return result;  
      }
      return nil();
    }
    else if (!result)
    {
      ungetc(c, s);
      current = result = pair(parse_expression(s), 0);
      if (!((struct Pair*)current->value)->car)
        return 0;
    }
    else
    {
      ungetc(c, s);
      set_cdr((struct Pair*)current->value, pair(parse_expression(s), 0));
      current = ((struct Pair*)current->value)->cdr;
      if (!((struct Pair*)current->value)->car)
        return 0;
    }
  }
}

struct Value *parse_symbol(FILE *s)
{
  char *name;
  int c, l, i;
  i = l = 0;
  name = 0;
  while ((c = fgetc(s)) != EOF && !isspace(c) && c != '(' && c != ')')
  {
    if (!l)
    {
      l = 2;
      if (!(name = allocate(sizeof(char) * l)))
        return 0;
    }
    else if (i + 1 >= l) 
    {
      l *= 2;
      if (!(name = realloc(name, sizeof(char) * l)))
        return 0;
    }
    name[i++] = c;
    name[i] = '\0';
  }
  if (ungetc(c, s) == EOF)
  {
    fprintf(stderr, "could not ungetc\n");
    return 0;
  }
  if (i)
    return symbol(name);
  return 0;
}

struct Value *parse_boolean(FILE *s)
{
  int c;
  c = fgetc(s);
  if (c != '#')
  {
    ungetc(c, s);
    return 0;
  }
  c = fgetc(s);
  if (c == 't')
    return boolean(1);
  else if (c == 'f')
    return boolean(0);
  else
  {
    ungetc(c, s);
    ungetc(c, s);
    return 0;
  }
}

struct Value *parse_atom(FILE *s)
{
  struct Value *result;
  if ((result = parse_boolean(s)))
    return result;
  result = parse_symbol(s);
  return result;
}

struct Value *parse_expression(FILE *s)
{
  struct Value *result;
  skip_whitespace(s);
  if ((result = parse_list(s)))
    return result;
  result = parse_atom(s);
  return result;
}

