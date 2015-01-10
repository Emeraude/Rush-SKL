#define _GNU_SOURCE
#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#include "raise.h"
#include "new.h"
#include "float.h"

static void Char_ctor(Object* self, va_list *args);
static void Char_dtor(Object* self);
static char const *Char_to_string(Object *self);
static Object *Char_add(const Object *self, const Object *other);
static Object *Char_sub(const Object *self, const Object *other);
static Object *Char_mul(const Object *self, const Object *other);
static Object *Char_div(const Object *self, const Object *other);
static int Char_eq(const Object *self, const Object *other);
static int Char_gt(const Object *self, const Object *other);
static int Char_lt(const Object *self, const Object *other);

typedef struct
{
    Class base;
  char x;
} CharClass;

static CharClass _description = {
  { sizeof(CharClass), "Char", &Char_ctor, &Char_dtor, &Char_to_string, &Char_add, &Char_sub, &Char_mul, &Char_div, Char_eq, Char_gt, &Char_lt},
    0
};

Class* Char = (Class*) &_description;

static void Char_ctor(Object* self, va_list *args)
{
  if (!self) raise("Arguments must be initialized.");
  ((CharClass *)self)->x = (char)va_arg(*args, int);
}

static void Char_dtor(Object* self)
{
  if (!self) raise("Arguments must be initialized.");
}

static char const *Char_to_string(Object *self)
{
  char *str = NULL;

  if (!self) raise("Arguments must be initialized.");
  asprintf(&str, "<Char (%c)>", ((CharClass *)self)->x);
  return (char const *)str;
}

static Object *Char_add(const Object *self, const Object *other)
{
  Object *add;

  if (!self || !other) raise("Arguments must be initialized.");
  add = new(Char, ((CharClass *)self)->x);
  ((CharClass *)add)->x += ((CharClass *)other)->x;
  return add;
}

static Object *Char_sub(const Object *self, const Object *other)
{
  Object *sub;

  if (!self || !other) raise("Arguments must be initialized.");
  sub = new(Char, ((CharClass *)self)->x);
  if (!other || !sub) return sub;
  ((CharClass *)sub)->x -= ((CharClass *)other)->x;
  return sub;
}

static Object *Char_mul(const Object *self, const Object *other)
{
  Object *sub;

  if (!self || !other) raise("Arguments must be initialized.");
  sub = new(Char, ((CharClass *)self)->x);
  if (!other || !sub) return sub;
  ((CharClass *)sub)->x *= ((CharClass *)other)->x;
  return sub;
}

static Object *Char_div(const Object *self, const Object *other)
{
  Object *sub;

  if (!self || !other) raise("Arguments must be initialized.");
  if (!((CharClass *)other)->x) raise("Dividing by zero");
  sub = new(Char, ((CharClass *)self)->x);
  if (!other || !sub) return sub;
  ((CharClass *)sub)->x /= ((CharClass *)other)->x;
  return sub;
}

static int Char_eq(const Object *self, const Object *other)
{
  if (!self || !other) raise("Arguments must be initialized.");  
  return (((CharClass *)self)->x == ((CharClass *)other)->x);
}

static int Char_gt(const Object *self, const Object *other)
{
  return (((CharClass *)self)->x > ((CharClass *)other)->x);
}

static int Char_lt(const Object *self, const Object *other)
{
  return (((CharClass *)self)->x <((CharClass *)other)->x);
}
