#define _GNU_SOURCE
#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#include "point.h"

typedef struct
{
    Class base;
    int x, y;
} PointClass;

static void Point_ctor(Object* self, va_list *args)
{
  ((PointClass *)self)->x = va_arg(*args, int);
  ((PointClass *)self)->y = va_arg(*args, int);
}

static void Point_dtor(Object* self)
{
  ((PointClass *)self)->base.__str__(NULL);
}

static char const *Point_to_string(Object *self) {
  static char *str = NULL;

  free(str);
  str = NULL;
  if (self)
    asprintf(&str, "<Point (%d, %d)>", ((PointClass *)self)->x, ((PointClass *)self)->y);
  return (char const *)str;
}

static PointClass _description = {
  { sizeof(PointClass), "Point", &Point_ctor, &Point_dtor, &Point_to_string},
    0, 0
};

Class* Point = (Class*) &_description;
