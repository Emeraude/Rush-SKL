#define _GNU_SOURCE
#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#include "new.h"
#include "point.h"

static void Point_ctor(Object* self, va_list *args);
static void Point_dtor(Object* self);
static char const *Point_to_string(Object *self);
static Object *Point_add(const Object *self, const Object *other);
static Object *Point_sub(const Object *self, const Object *other);

typedef struct
{
    Class base;
    int x, y;
} PointClass;

static PointClass _description = {
  { sizeof(PointClass), "Point", &Point_ctor, &Point_dtor, &Point_to_string, &Point_add, &Point_sub},
    0, 0
};

Class* Point = (Class*) &_description;

static void Point_ctor(Object* self, va_list *args)
{
  if (!self) return ;
  ((PointClass *)self)->x = va_arg(*args, int);
  ((PointClass *)self)->y = va_arg(*args, int);
}

static void Point_dtor(Object* self)
{
  (void)self;
}

static char const *Point_to_string(Object *self)
{
  char *str = NULL;

  if (!self) return NULL;
  asprintf(&str, "<Point (%d, %d)>", ((PointClass *)self)->x, ((PointClass *)self)->y);
  return (char const *)str;
}

static Object *Point_add(const Object *self, const Object *other)
{
  Object *add;

  if (!self) return NULL;
  add = new(Point, ((PointClass *)self)->x, ((PointClass *)self)->y);
  if (!other) return add;
  ((PointClass *)add)->x += ((PointClass *)other)->x;
  ((PointClass *)add)->y += ((PointClass *)other)->y;
  return add;
}

static Object *Point_sub(const Object *self, const Object *other)
{
  Object *sub;

  if (!self) return NULL;
  sub = new(Point, ((PointClass *)self)->x, ((PointClass *)self)->y);
  if (!other || !sub) return sub;
  ((PointClass *)sub)->x -= ((PointClass *)other)->x;
  ((PointClass *)sub)->y -= ((PointClass *)other)->y;
  return sub;
}
