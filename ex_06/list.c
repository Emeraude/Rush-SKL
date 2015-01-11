
#include <stdlib.h>
#include <stdarg.h>

#include "raise.h"
#include "new.h"
#include "list.h"
#include "int.h"
#include "float.h"
#include "char.h"

typedef struct s_list ListClass;

typedef struct s_list
{
  Container base;
  Class* _type;
  size_t _size;
  Object *_object;
  ListClass *_next;
} ListClass;

typedef struct {
  Iterator base;
  ListClass* _list;
  ListClass *_idx;
} ListIteratorClass;

// args: (1: size_t _idx) (2: ListClass* _list)
void ListIterator_ctor(ListIteratorClass* self, va_list* args)
{
  size_t i;
  ListClass *tmp;

  if (!self) raise("Arguments must be initialized.");
  i = va_arg(*args, size_t);
  self->_list = va_arg(*args, ListClass*);
  if (i > self->_list->_size)
    raise("Argument idx is higher than list length.");

  tmp = self->_list->_next;
  while (i--)
    tmp = tmp->_next;
  self->_idx = tmp;
}

static bool isAfter(ListIteratorClass* self, ListIteratorClass* other)
{
  ListClass *tmp;

  if (!self || !other) raise("Arguments must be initialized.");
  if (!self->_idx || !other->_idx) return false;
  tmp = self->_idx;
  while (tmp) {
    tmp = tmp->_next;
    if (tmp == other->_idx)
      return true;
  }
  return false;
}

static bool isBefore(ListIteratorClass* self, ListIteratorClass* other)
{
  return isAfter(other, self);
}

bool ListIterator_eq(ListIteratorClass* self, ListIteratorClass* other)
{
  if (!self || !other) raise("Arguments must be initialized.");
  if (!self->_idx || !other->_idx) return false;
  return (self->_idx == other->_idx ? true : false);
}

bool ListIterator_gt(ListIteratorClass* self, ListIteratorClass* other)
{
  if (!self || !other) raise("Arguments must be initialized.");
  if (!self->_idx || !other->_idx) return false;
  return (isAfter(self->_idx, other->_idx) ? true : false);
}

bool ListIterator_lt(ListIteratorClass* self, ListIteratorClass* other)
{
  if (!self || !other) raise("Arguments must be initialized.");
  if (!self->_idx || !other->_idx) return false;
  return (isBefore(self->_idx, other->_idx) ? true : false);
}

void ListIterator_incr(ListIteratorClass* self)
{
  if (!self) raise("Arguments must be initialized.");
  if (self->_idx->_next)
    self->_idx = self->_idx->_next;
}

Object* ListIterator_getval(ListIteratorClass* self)
{
  if (!self || !self->_idx) raise("Arguments must be initialized.");
  return (self->_idx->_object);
}

void ListIterator_setval(ListIteratorClass* self, ...)
{
  Object *obj;
  va_list ap;

  if (!self) raise("Arguments must be initialized.");
  va_start(ap, self);
  obj = va_arg(ap, Object*);
  if (!obj) raise("Arguments must be initialized.");
  ((Class*)obj)->__init__(obj, &ap);
  va_end(ap);
}

static ListIteratorClass ListIteratorDescr = {
    {
        {
            sizeof(ListIteratorClass), "ListIterator",
            (ctor_t) &ListIterator_ctor,
            NULL, /* dtor */
            NULL, /* str */
            NULL, NULL, NULL, NULL, /* add, sub, mul, div */
            (binary_comparator_t) &ListIterator_eq,
            (binary_comparator_t) &ListIterator_gt,
            (binary_comparator_t) &ListIterator_lt,
        },
        (incr_t) &ListIterator_incr,
        (getval_t) &ListIterator_getval,
        (setval_t) &ListIterator_setval,
    },
    NULL,
    0
};

static Class* ListIterator = (Class*) &ListIteratorDescr;

static void List_push_back(ListClass *list, Object *new) {
  ListClass *newNode;

  if (!list || !new) raise("Arguments must be initialized.");

  // Initialize the new node
  if ((newNode = malloc(sizeof(ListClass))) == NULL) raise("Out of memory.");
  newNode->_object = new;
  newNode->_next = NULL;
  newNode->_size = 0;
  newNode->_type = list->_type;

  // Set the new node at the end of the list
  list->_size++;
  while (list && list->_next)
    list = list->_next;
  list->_next = newNode;
}

static void List_pop_back(ListClass *list) {
  if (!list) raise("Arguments must be initialized.");

  // free and set to null the last element of the list
  if (list->_size == 0) return;
  list->_size--;
  list = list->_next;
  while (list->_next && list->_next->_next)
    list = list->_next;
  free(list->_next);
  list->_next = NULL;
}

// args: (1: size_t _size) (2: Class* _type) (3: default_value)
void List_ctor(ListClass* self, va_list* args)
{
  size_t i;

  if (!self) raise("Arguments must be initialized.");
  i = va_arg(*args, size_t);
  self->_type = va_arg(*args, Class*);
  // _size and _object and _next are null

  va_list default_argument;

  while (i)
    {
      va_copy(default_argument, *args);
      List_push_back(self, va_new(self->_type, &default_argument));
      va_end(default_argument);
      i--;
    }
}

void List_dtor(ListClass* self)
{
  size_t i;

  if (!self) raise("Arguments must be initialized.");
  for (i=0; i < self->_size ; i++)
    {
      List_pop_back(self);
    }
}

size_t List_len(ListClass* self)
{
  if (!self) raise("Arguments must be initialized.");
  return (self->_size);
}

Iterator* List_begin(ListClass* self)
{
  if (!self) raise("Arguments must be initialized.");
  if (self->_size == 0) return NULL;
  printf("THIS IS THE BEGIN OF MY REIGN HEIL\n");
  return (new(ListIterator, 0, self));
}

Iterator* List_end(ListClass* self)
{
  if (!self) raise("Arguments must be initialized.");
  if (self->_size == 0) return NULL;
  printf("THIS IS THE END OF MY REIGN HEIL %u\n", self->_size);
  return (new(ListIterator, self->_size - 1, self));
}

Object* List_getitem(ListClass* self, ...)
{
  size_t i;
  va_list ap;

  if (!self) raise("Arguments must be initialized.");
  va_start(ap, self);
  i = va_arg(ap, size_t) + 1;
  while (i-- && self)
    self = self->_next;
  if (!i) raise("Argument idx is higher than list length.");
  va_end(ap);
  return self->_object;
}

void List_setitem(ListClass* self, ...)
{
  size_t i, j;
  va_list ap;
  ListClass *tmp;

  if (!self) raise("Arguments must be initialized.");
  va_start(ap, self);
  i = va_arg(ap, size_t) + 1;
  if (i > self->_size)
    raise("Argument idx is higher than list length.");
  tmp = self;
  for (j = 0; tmp && j < i; ++j)
    tmp = tmp->_next;
  ((Class *)tmp->_object)->__init__(tmp->_object, &ap);
  va_end(ap);
}

static ListClass _descr = {
    { /* Container */
        { /* Class */
            sizeof(ListClass), "List",
            (ctor_t) &List_ctor, (dtor_t) &List_dtor,
            NULL, /*str */
            NULL, NULL, NULL, NULL, /* add, sub, mul, div */
            NULL, NULL, NULL, /* eq, gt, lt */
        },
        (len_t) &List_len,
        (iter_t) &List_begin,
        (iter_t) &List_end,
        (getitem_t) &List_getitem,
        (setitem_t) &List_setitem,
    },
    NULL, 0, NULL, NULL
};

Class* List = (Class*) &_descr;

