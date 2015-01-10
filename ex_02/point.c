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
  printf("Point(%d, %d)\n", ((PointClass *)self)->x, ((PointClass *)self)->y);
}

static void Point_dtor(Object* self)
{
    (void) self;
    printf("~Point()\n");
}

static char const *Point_to_string_t(Object *self) {
  static char *str = NULL;

  free(str);
  printf("<Point (%d, %d)>", ((PointClass *)self)->x, ((PointClass *)self)->y);
  asprintf(&str, "<Point (%d, %d)>", ((PointClass *)self)->x, ((PointClass *)self)->y);
  printf("%s\n", str);
  return (char const *)str;
}

static PointClass _description = {
  { sizeof(PointClass), "Point", &Point_ctor, &Point_dtor, &Point_to_string_t},
    0, 0
};

Class* Point = (Class*) &_description;
