/*
** new.c for  in /home/broggi_t/projet/rush-skl/ex_01
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Sat Jan 10 12:50:09 2015 broggi_t
** Last update Sat Jan 10 12:50:09 2015 broggi_t
*/

#include <stdarg.h>
#include <malloc.h>
#include <string.h>
#include "raise.h"
#include "new.h"

Object		*new(Class *class, ...) {
  Class		*new;
  va_list	ap;

  va_start(ap, class);
  new = va_new(class, &ap);
  va_end(ap);
  return (Object *)new;
}

Object		*va_new(Class* class, va_list *ap) {
  Class		*new;

  if ((new = malloc(class->__size__)) == NULL
      || memcpy(new, class, class->__size__) == NULL)
    raise("Error on constructor.");
  if (new->__init__)
    new->__init__(new, ap);
  return (Object *)new;
}

void	delete(Object *ptr) {
  if (((Class *)ptr)->__del__)
    ((Class *)ptr)->__del__(ptr);
  free(ptr);
}
