#define _GNU_SOURCE
#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#include "new.h"
#include "vertex.h"

static void Vertex_ctor(Object* self, va_list *args);
static void Vertex_dtor(Object* self);
static char const *Vertex_to_string_t(Object *self);
static Object *Vertex_add(const Object *self, const Object *other);
static Object *Vertex_sub(const Object *self, const Object *other);

typedef struct
{
  Class base;
  int x, y, z;
} VertexClass;

static VertexClass _description = {
  { sizeof(VertexClass), "Vertex", &Vertex_ctor, &Vertex_dtor, &Vertex_to_string_t, &Vertex_add, &Vertex_sub},
  0, 0, 0
};

Class* Vertex = (Class*) &_description;

static void Vertex_ctor(Object* self, va_list *args)
{
  if (!self) return;
  ((VertexClass *)self)->x = va_arg(*args, int);
  ((VertexClass *)self)->y = va_arg(*args, int);
  ((VertexClass *)self)->z = va_arg(*args, int);
}

static void Vertex_dtor(Object* self)
{
  if (!self) return ;
  ((VertexClass *)self)->base.__str__(NULL);
}

static char const *Vertex_to_string_t(Object *self)
{
  static char *str = NULL;

  if (!self) return NULL;
  asprintf(&str, "<Vertex (%d, %d, %d)>", ((VertexClass *)self)->x,
           ((VertexClass *)self)->y, ((VertexClass *)self)->z);
  return (char const *)str;  
}

static Object *Vertex_add(const Object *self, const Object *other)
{
  Object *add;

  if (!self) return NULL;
  add = new(Vertex, ((VertexClass *)self)->x, ((VertexClass *)self)->y, ((VertexClass *)self)->z);
  if (!other) return add;
  ((VertexClass *)add)->x += ((VertexClass *)other)->x;
  ((VertexClass *)add)->y += ((VertexClass *)other)->y;
  ((VertexClass *)add)->z += ((VertexClass *)other)->z;
  return add;
}

static Object *Vertex_sub(const Object *self, const Object *other)
{
  Object *sub;

  if (!self) return NULL;
  sub = new(Vertex, ((VertexClass *)self)->x, ((VertexClass *)self)->y, ((VertexClass *)self)->z);
  if (!other || !sub) return sub;
  ((VertexClass *)sub)->x -= ((VertexClass *)other)->x;
  ((VertexClass *)sub)->y -= ((VertexClass *)other)->y;
  ((VertexClass *)sub)->z -= ((VertexClass *)other)->z;
  return sub;
}
