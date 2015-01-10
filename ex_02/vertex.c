#define _GNU_SOURCE
#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#include "point.h"

typedef struct
{
    Class base;
  int x, y, z;
} VertexClass;

static void Vertex_ctor(Object* self, va_list *args)
{
  ((VertexClass *)self)->x = va_arg(*args, int);
  ((VertexClass *)self)->y = va_arg(*args, int);
}

static void Vertex_dtor(Object* self)
{
    (void) self;
    printf("~Vertex()\n");
}

static char const *Vertex_to_string_t(Object *self) {
  static char *str = NULL;

  free(str);
  printf("<Vertex (%d, %d, %d)>", ((VertexClass *)self)->x,
	 ((VertexClass *)self)->y), ((VertexClass *)self)->z);
  asprintf(&str, "<Vertex (%d, %d, %d)>", ((VertexClass *)self)->x,
	   ((VertexClass *)self)->y, ((VertexClass *)self)->z);
  printf("%s\n", str);
  return (char const *)str;
}

static VertexClass _description = {
  { sizeof(VertexClass), "Vertex", &Vertex_ctor, &Vertex_dtor, &Vertex_to_string_t},
  0, 0, 0
};

Class* Vertex = (Class*) &_description;
