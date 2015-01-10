#define _GNU_SOURCE
#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#include "vertex.h"

typedef struct
{
  Class base;
  int x, y, z;
} VertexClass;

static void Vertex_ctor(Object* self, va_list *args)
{
  ((VertexClass *)self)->x = va_arg(*args, int);
  ((VertexClass *)self)->y = va_arg(*args, int);
  ((VertexClass *)self)->z = va_arg(*args, int);
}

static void Vertex_dtor(Object* self)
{
  (void)self;
}

static char const *Vertex_to_string_t(Object *self) {
  char *str;

  if (self)
    asprintf(&str, "<Vertex (%d, %d, %d)>", ((VertexClass *)self)->x,
	     ((VertexClass *)self)->y, ((VertexClass *)self)->z);
  return (char const *)str;
}

static VertexClass _description = {
  { sizeof(VertexClass), "Vertex", &Vertex_ctor, &Vertex_dtor, &Vertex_to_string_t},
  0, 0, 0
};

Class* Vertex = (Class*) &_description;
