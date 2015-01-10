#define _GNU_SOURCE
#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#include "raise.h"
#include "new.h"
#include "int.h"

static void Int_ctor(Object* self, va_list *args);
static void Int_dtor(Object* self);
static char const *Int_to_string(Object *self);
static Object *Int_add(const Object *self, const Object *other);
static Object *Int_sub(const Object *self, const Object *other);
static Object *Int_mul(const Object *self, const Object *other);
static Object *Int_div(const Object *self, const Object *other);
static int Int_eq(const Object *self, const Object *other);
static int Int_gt(const Object *self, const Object *other);
static int Int_lt(const Object *self, const Object *other);

typedef struct
{
  Class base;
  int x;
} IntClass;

static IntClass _description = {
  { sizeof(IntClass), "Int", &Int_ctor, &Int_dtor, &Int_to_string, &Int_add, &Int_sub, &Int_mul, &Int_div, Int_eq, Int_gt, &Int_lt},
    0
};

Class* Int = (Class*) &_description;

static void Int_ctor(Object* self, va_list *args)
{
  if (!self) raise("Arguments must be initialized.");
  ((IntClass *)self)->x = va_arg(*args, int);
}

static void Int_dtor(Object* self)
{
  if (!self) raise("Arguments must be initialized.");
}

static char const *Int_to_string(Object *self)
{
  char *str = NULL;

  if (!self) raise("Arguments must be initialized.");
  asprintf(&str, "<Int (%i)>", ((IntClass *)self)->x);
  return (char const *)str;
}

static Object *Int_add(const Object *self, const Object *other)
{
  Object *add;

  if (!self || !other) raise("Arguments must be initialized.");
  add = new(Int, ((IntClass *)self)->x);
  ((IntClass *)add)->x += ((IntClass *)other)->x;
  return add;
}

static Object *Int_sub(const Object *self, const Object *other)
{
  Object *sub;

  if (!self || !other) raise("Arguments must be initialized.");
  sub = new(Int, ((IntClass *)self)->x);
  if (!other || !sub) return sub;
  ((IntClass *)sub)->x -= ((IntClass *)other)->x;
  return sub;
}

static Object *Int_mul(const Object *self, const Object *other)
{
  Object *sub;

  if (!self || !other) raise("Arguments must be initialized.");
  sub = new(Int, ((IntClass *)self)->x);
  if (!other || !sub) return sub;
  ((IntClass *)sub)->x *= ((IntClass *)other)->x;
  return sub;
}

static Object *Int_div(const Object *self, const Object *other)
{
  Object *sub;

  if (!self || !other) raise("Arguments must be initialized.");
  if (!((IntClass *)other)->x) raise("Dividing by zero");
  sub = new(Int, ((IntClass *)self)->x);
  if (!other || !sub) return sub;
  ((IntClass *)sub)->x /= ((IntClass *)other)->x;
  return sub;
}

static int Int_eq(const Object *self, const Object *other)
{
  if (!self || !other) raise("Arguments must be initialized.");  
  return (((IntClass *)self)->x == ((IntClass *)other)->x);
}

static int Int_gt(const Object *self, const Object *other)
{
  return (((IntClass *)self)->x > ((IntClass *)other)->x);
}

static int Int_lt(const Object *self, const Object *other)
{
  return (((IntClass *)self)->x < ((IntClass *)other)->x);
}
