#define _GNU_SOURCE
#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#include "raise.h"
#include "new.h"
#include "float.h"

static void Float_ctor(Object* self, va_list *args);
static void Float_dtor(Object* self);
static char const *Float_to_string(Object *self);
static Object *Float_add(const Object *self, const Object *other);
static Object *Float_sub(const Object *self, const Object *other);
static Object *Float_mul(const Object *self, const Object *other);
static Object *Float_div(const Object *self, const Object *other);
static int Float_eq(const Object *self, const Object *other);
static int Float_gt(const Object *self, const Object *other);
static int Float_lt(const Object *self, const Object *other);

typedef struct
{
  Class base;
  float x;
} FloatClass;

static FloatClass _description = {
  { sizeof(FloatClass), "Float", &Float_ctor, &Float_dtor, &Float_to_string, &Float_add, &Float_sub, &Float_mul, &Float_div, Float_eq, Float_gt, &Float_lt},
    0
};

Class* Float = (Class*) &_description;

static void Float_ctor(Object* self, va_list *args)
{
  if (!self) raise("Arguments must be initialized.");
  ((FloatClass *)self)->x = (float)va_arg(*args, double);
}

static void Float_dtor(Object* self)
{
  if (!self) raise("Arguments must be initialized.");
}

static char const *Float_to_string(Object *self)
{
  char *str = NULL;

  if (!self) raise("Arguments must be initialized.");
  asprintf(&str, "<Float (%f)>", ((FloatClass *)self)->x);
  return (char const *)str;
}

static Object *Float_add(const Object *self, const Object *other)
{
  Object *add;

  if (!self || !other) raise("Arguments must be initialized.");
  add = new(Float, ((FloatClass *)self)->x);
  ((FloatClass *)add)->x += ((FloatClass *)other)->x;
  return add;
}

static Object *Float_sub(const Object *self, const Object *other)
{
  Object *sub;

  if (!self || !other) raise("Arguments must be initialized.");
  sub = new(Float, ((FloatClass *)self)->x);
  if (!other || !sub) return sub;
  ((FloatClass *)sub)->x -= ((FloatClass *)other)->x;
  return sub;
}

static Object *Float_mul(const Object *self, const Object *other)
{
  Object *sub;

  if (!self || !other) raise("Arguments must be initialized.");
  sub = new(Float, ((FloatClass *)self)->x);
  if (!other || !sub) return sub;
  ((FloatClass *)sub)->x *= ((FloatClass *)other)->x;
  return sub;
}

static Object *Float_div(const Object *self, const Object *other)
{
  Object *sub;

  if (!self || !other) raise("Arguments must be initialized.");
  if (!((FloatClass *)other)->x) raise("Dividing by zero");
  sub = new(Float, ((FloatClass *)self)->x);
  if (!other || !sub) return sub;
  ((FloatClass *)sub)->x /= ((FloatClass *)other)->x;
  return sub;
}

static Object *Float_mod(const Object *self, const Object *other)
{
  if (!self || !other) raise("Arguments must be initialized.");
  raise("Modulos are impossible with Float type.");
  return self;
}

static int Float_eq(const Object *self, const Object *other)
{
  if (!self || !other) raise("Arguments must be initialized.");
  return (((FloatClass *)self)->x == ((FloatClass *)other)->x);
}

static int Float_gt(const Object *self, const Object *other)
{
  return (((FloatClass *)self)->x > ((FloatClass *)other)->x);
}

static int Float_lt(const Object *self, const Object *other)
{
  return (((FloatClass *)self)->x < ((FloatClass *)other)->x);
}
