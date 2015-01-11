
#include <stdlib.h>
#include <stdarg.h>

#include "raise.h"
#include "new.h"
#include "array.h"
#include "int.h"
#include "float.h"
#include "char.h"

typedef struct
{
    Container base;
    Class* _type;
    size_t _size;
    Object** _tab;
} ArrayClass;

typedef struct {
    Iterator base;
    ArrayClass* _array;
    size_t _idx;
} ArrayIteratorClass;

// args: (1: size_t _idx) (2: ArrayClass* _array)
void ArrayIterator_ctor(ArrayIteratorClass* self, va_list* args)
{
  size_t length;

  if (!self) raise("Arguments must be initialized.");
  length = va_arg(*args, size_t);
  self->_array = va_arg(*args, ArrayClass*);
  if (length > self->_array->_size)
    raise("Argument idx is higher than array length.");
}

bool ArrayIterator_eq(ArrayIteratorClass* self, ArrayIteratorClass* other)
{
  if (!self || !other) raise("Arguments must be initialized.");
  return (self->_idx == other->_idx ? true : false);
}

bool ArrayIterator_gt(ArrayIteratorClass* self, ArrayIteratorClass* other)
{
  if (!self || !other) raise("Arguments must be initialized.");
  return (self->_idx > other->_idx ? true : false);
}

bool ArrayIterator_lt(ArrayIteratorClass* self, ArrayIteratorClass* other)
{
  if (!self || !other) raise("Arguments must be initialized.");
  return (self->_idx < other->_idx ? true : false);
}

void ArrayIterator_incr(ArrayIteratorClass* self)
{
  if (!self) raise("Arguments must be initialized.");
  self->_idx++;
}

Object* ArrayIterator_getval(ArrayIteratorClass* self)
{
  if (!self) raise("Arguments must be initialized.");
  return (self->_array->_tab[self->_idx]);
}

void ArrayIterator_setval(ArrayIteratorClass* self, ...)
{
  Object *obj;
  va_list ap;

  if (!self) raise("Arguments must be initialized.");
  va_start(ap, self);
  obj = va_arg(ap, Object*);
  ((Class*)obj)->__init__(obj, &ap);
  va_end(ap);
}

static ArrayIteratorClass ArrayIteratorDescr = {
    {
        {
            sizeof(ArrayIteratorClass), "ArrayIterator",
            (ctor_t) &ArrayIterator_ctor,
            NULL, /* dtor */
            NULL, /* str */
            NULL, NULL, NULL, NULL, /* add, sub, mul, div */
            (binary_comparator_t) &ArrayIterator_eq,
            (binary_comparator_t) &ArrayIterator_gt,
            (binary_comparator_t) &ArrayIterator_lt,
        },
        (incr_t) &ArrayIterator_incr,
        (getval_t) &ArrayIterator_getval,
        (setval_t) &ArrayIterator_setval,
    },
    NULL,
    0
};

static Class* ArrayIterator = (Class*) &ArrayIteratorDescr;

// args: (1: size_t _size) (2: Class* _type) (3: default_value)
void Array_ctor(ArrayClass* self, va_list* args)
{
  size_t i;

  if (!self) raise("Arguments must be initialized.");
  self->_size = va_arg(*args, size_t);
  self->_type = va_arg(*args, Class*);
  self->_tab = NULL;
  if (((ArrayClass *)self)->_size == 0) return ;
  self->_tab = malloc(sizeof(Object*) * self->_size);
  if (!self->_tab) raise("Out of memory.");

  va_list default_argument;

  for (i=0; i < self->_size; i++)
    {
      va_copy(default_argument, *args);
      self->_tab[i] = va_new(self->_type, &default_argument);
      va_end(default_argument);
    }
}

void Array_dtor(ArrayClass* self)
{
  size_t i;

  if (!self) raise("Arguments must be initialized.");
  for (i=0; i < self->_size ; i++)
    {
      delete(self->_tab[i]);
    }
  free(self->_tab);
}

size_t Array_len(ArrayClass* self)
{
  if (!self) raise("Arguments must be initialized.");
  return (self->_size);
}

Iterator* Array_begin(ArrayClass* self)
{
  if (!self) raise("Arguments must be initialized.");
  if (len(&self->base) == 0) return NULL;
  return (new(ArrayIterator, 0, self));
}

Iterator* Array_end(ArrayClass* self)
{
  if (!self) raise("Arguments must be initialized.");
  if (len(&self->base) == 0) return NULL;
  return (new(ArrayIterator, len(&self->base) - 1, self));
}

Object* Array_getitem(ArrayClass* self, ...)
{
  size_t i;
  va_list ap;

  if (!self) raise("Arguments must be initialized.");
  va_start(ap, self);
  i = va_arg(ap, size_t);
  if (i > self->_size)
    raise("Argument idx is higher than array length.");
  va_end(ap);
  return self->_tab[i];
}

void Array_setitem(ArrayClass* self, ...)
{
  size_t i;
  va_list ap;

  if (!self) raise("Arguments must be initialized.");
  va_start(ap, self);
  i = va_arg(ap, size_t);
  if (i > self->_size)
    raise("Argument idx is higher than array length.");
  ((Class *)self->_tab[i])->__init__(self->_tab[i], &ap);
  va_end(ap);
}

static ArrayClass _descr = {
    { /* Container */
        { /* Class */
            sizeof(ArrayClass), "Array",
            (ctor_t) &Array_ctor, (dtor_t) &Array_dtor,
            NULL, /*str */
            NULL, NULL, NULL, NULL, /* add, sub, mul, div */
            NULL, NULL, NULL, /* eq, gt, lt */
        },
        (len_t) &Array_len,
        (iter_t) &Array_begin,
        (iter_t) &Array_end,
        (getitem_t) &Array_getitem,
        (setitem_t) &Array_setitem,
    },
    NULL, 0, NULL
};

Class* Array = (Class*) &_descr;

