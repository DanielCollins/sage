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
  int c, l, i, t;
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
      t = l * 2;
      if (!(name = (char*) reallocate(name, sizeof(char) * l ,
           sizeof(char) * t)))
        return 0;
      l = t;
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
  {
    name = (char*) reallocate(name, sizeof(char) * l, sizeof(char) * (i + 1));
    return symbol(name);
  }
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

struct Value *parse_integer(FILE *s)
{
  int c, i, z;
  char *identifier;
  struct Value *result;
  identifier = 0;
  z = i = 0;
  while (1)
  {
    c = fgetc(s);
    if (!isdigit(c))
    {
      ungetc(c, s);
      if (i)
      {
        if (!z)
        {
          z = 1;
          identifier = allocate(sizeof(char));
        }
        if (i >= z)
        {
          z *= 2;
          identifier = realloc(identifier, z);
        }
        identifier[i] = '\0';
      }
      break;
    }
    else
    {
      if (!z)
      {
        z = 1;
        identifier = allocate(sizeof(char));
      }
      if (i >= z)
      {
        z *= 2;
        identifier = realloc(identifier, z);
      }
      identifier[i] = c;
      ++i;
    }
  }
  if (!i)
    return 0;
  result = make_integer(atoi(identifier));
  deallocate(identifier, i + 1);
  return result;
}

struct Value *parse_atom(FILE *s)
{
  struct Value *result;
  if ((result = parse_boolean(s)))
    return result;
  if ((result = parse_integer(s)))
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

