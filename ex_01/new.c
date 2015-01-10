/*
** new.c for  in /home/broggi_t/projet/rush-skl/ex_01
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Sat Jan 10 12:50:09 2015 broggi_t
** Last update Sat Jan 10 12:50:09 2015 broggi_t
*/

#include <malloc.h>
#include <string.h>
#include "new.h"
#include "point.h"

void	*new(Class *class) {
  Class	*new;

  if ((new = malloc(sizeof(*class))) == NULL
      || memcpy(new, Point, sizeof(*Point)) == NULL)
    return NULL;
  if (new->__init__)
    new->__init__(class);
  return new;
}

void	delete(Object *ptr) {
  if (((Class *)ptr)->__del__)
    ((Class *)ptr)->__del__(ptr);
  free(ptr);
}
