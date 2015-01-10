#define _GNU_SOURCE
#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#include "raise.h"
#include "new.h"
#include "vertex.h"

static void Vertex_ctor(Object* self, va_list *args);
static void Vertex_dtor(Object* self);
static char const *Vertex_to_string_t(Object *self);

typedef struct
{
  Class base;
  int x, y, z;
} VertexClass;

static VertexClass _description = {
  { sizeof(VertexClass), "Vertex", &Vertex_ctor, &Vertex_dtor, &Vertex_to_string_t},
  0, 0, 0
};

Class* Vertex = (Class*) &_description;

static void Vertex_ctor(Object* self, va_list *args)
{
  if (!self) raise("Arguments must be initialized.");
  ((VertexClass *)self)->x = va_arg(*args, int);
  ((VertexClass *)self)->y = va_arg(*args, int);
  ((VertexClass *)self)->z = va_arg(*args, int);
}

static void Vertex_dtor(Object* self)
{
  if (!self) raise("Arguments must be initialized.");
}

static char const *Vertex_to_string_t(Object *self)
{
  char *str = NULL;

  if (!self) raise("Arguments must be initialized.");
  asprintf(&str, "<Vertex (%d, %d, %d)>", ((VertexClass *)self)->x,
           ((VertexClass *)self)->y, ((VertexClass *)self)->z);
  return (char const *)str;  
}
