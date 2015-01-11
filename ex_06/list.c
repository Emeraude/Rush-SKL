
#include <stdlib.h>
#include <stdarg.h>

#include "raise.h"
#include "new.h"
#include "list.h"
#include "int.h"
#include "float.h"
#include "char.h"

typedef struct s_node ListNode;

typedef struct s_node
{
  Object *_object;
  ListNode *_next;
} ListNode;

typedef struct
{
  Container base;
  Class* _type;
  size_t _size;
  ListNode *_node;
} ListClass;

typedef struct {
  Iterator base;
  ListClass* _list;
  ListNode *_idx;
} ListIteratorClass;

// args: (1: size_t _idx) (2: ListClass* _list)
void ListIterator_ctor(ListIteratorClass* self, va_list* args)
{
  size_t i, j;
  ListNode *tmp;

  if (!self) raise("Arguments must be initialized.");
  i = va_arg(*args, size_t);
  self->_list = va_arg(*args, ListClass*);
  if (i > self->_list->_size)
    raise("Argument idx is higher than list length.");
  for (j = 0; j < i; ++j)
    tmp = tmp->_next;
  self->_idx = tmp;
}

bool ListIterator_eq(ListIteratorClass* self, ListIteratorClass* other)
{
  if (!self || !other) raise("Arguments must be initialized.");
  return (eq(self->_idx, other->_idx) ? true : false);
}

bool ListIterator_gt(ListIteratorClass* self, ListIteratorClass* other)
{
  if (!self || !other) raise("Arguments must be initialized.");
  return (gt(self->_idx, other->_idx) ? true : false);
}

bool ListIterator_lt(ListIteratorClass* self, ListIteratorClass* other)
{
  if (!self || !other) raise("Arguments must be initialized.");
  return (lt(self->_idx, other->_idx) ? true : false);
}

void ListIterator_incr(ListIteratorClass* self)
{
  if (!self) raise("Arguments must be initialized.");
  if (self->_idx->_next)
    self->_idx = self->_idx->_next;
}

Object* ListIterator_getval(ListIteratorClass* self)
{
  if (!self) raise("Arguments must be initialized.");
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

static void List_push_front(ListClass *list, Object *new) {
  ListNode *newNode;

  if (!list || !new) raise("Arguments must be initialized.");
  if ((newNode = malloc(sizeof(ListClass))) == NULL) raise("Out of memory.");
  newNode->_object = new;
  newNode->_next = list->_node;
  list->_node = newNode;
  list->_size--;
}

static void List_pop_front(ListClass *list) {
  ListNode *tmp;

  if (!list) raise("Arguments must be initialized.");
  tmp = list->_node;
  list->_node = list->_node->_next;
  list->_size--;
  free(tmp);
}

// args: (1: size_t _size) (2: Class* _type) (3: default_value)
void List_ctor(ListClass* self, va_list* args)
{
  size_t i;

  if (!self) raise("Arguments must be initialized.");
  self->_size = va_arg(*args, size_t);
  self->_type = va_arg(*args, Class*);
  self->_node = NULL;
  if (((ListClass *)self)->_size == 0) return ;

  va_list default_argument;

  for (i=0; i < self->_size; i++)
    {
      va_copy(default_argument, *args);
      List_push_front(self, va_new(self->_type, &default_argument));
      va_end(default_argument);
    }
}

void List_dtor(ListClass* self)
{
  size_t i;

  if (!self) raise("Arguments must be initialized.");
  for (i=0; i < self->_size ; i++)
    {
      List_pop_front(self);
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
  if (len(&self->base) == 0) return NULL;
  return (new(ListIterator, 0, self));
}

Iterator* List_end(ListClass* self)
{
  if (!self) raise("Arguments must be initialized.");
  if (len(&self->base) == 0) return NULL;
  return (new(ListIterator, len(&self->base) - 1, self));
}

Object* List_getitem(ListClass* self, ...)
{
  size_t i, j;
  va_list ap;
  ListNode *tmp;

  if (!self) raise("Arguments must be initialized.");
  va_start(ap, self);
  i = va_arg(ap, size_t);
  if (i > self->_size)
    raise("Argument idx is higher than list length.");
  tmp = self->_node;
  for (j = 0; j < i; ++j)
    tmp = tmp->_next;
  va_end(ap);
  return tmp->_object;
}

void List_setitem(ListClass* self, ...)
{
  size_t i, j;
  va_list ap;
  ListNode *tmp;

  if (!self) raise("Arguments must be initialized.");
  va_start(ap, self);
  i = va_arg(ap, size_t);
  if (i > self->_size)
    raise("Argument idx is higher than list length.");
  tmp = self->_node;
  for (j = 0; j < i; ++j)
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
    NULL, 0, NULL
};

Class* List = (Class*) &_descr;

