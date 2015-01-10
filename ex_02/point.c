#define _GNU_SOURCE
#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#include "raise.h"
#include "new.h"
#include "point.h"

static void Point_ctor(Object* self, va_list *args);
static void Point_dtor(Object* self);
static char const *Point_to_string(Object *self);

typedef struct
{
  Class base;
  int x, y;
} PointClass;

static PointClass _description = {
  { sizeof(PointClass), "Point", &Point_ctor, &Point_dtor, &Point_to_string},
    0, 0
};

Class* Point = (Class*) &_description;

static void Point_ctor(Object* self, va_list *args)
{
  if (!self) raise("Arguments must be initialized.");
  ((PointClass *)self)->x = va_arg(*args, int);
  ((PointClass *)self)->y = va_arg(*args, int);
}

static void Point_dtor(Object* self)
{
  if (!self) raise("Arguments must be initialized.");
}

static char const *Point_to_string(Object *self)
{
  char *str = NULL;

  if (!self) raise("Arguments must be initialized.");
  asprintf(&str, "<Point (%d, %d)>", ((PointClass *)self)->x, ((PointClass *)self)->y);
  return (char const *)str;
}
