#include <stdarg.h>
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
  char const *str;
  sprintf(str, "<Point (%d, %d)>", ((PointClass *)self)->x, ((PointClass *)self)->y);
  return str;
}

static PointClass _description = {
  { sizeof(PointClass), "Point", &Point_ctor, &Point_dtor,  },
    0, 0
};

Class* Point = (Class*) &_description;
