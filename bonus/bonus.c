
#include <stdio.h>
#include <assert.h>

#include "container.h"
#include "list.h"
#include "int.h"
#include "float.h"
#include "char.h"
#include "new.h"


int		main()
{
  Object *listInt = new(List, 5, Int, 42);
  Object *listFloat = new(List, 5, Float, 42.00f);
  Object *listChar = new(List, 5, Char, 'a');

  printf("\n--- Basics Test ---\n");
  printf("Val 42 : %s\n", str(getitem(listInt, 4)));
  printf("Val 42 : %s\n", str(getitem(listFloat, 4)));
  printf("Val 42 : %s\n", str(getitem(listChar, 4)));

  printf("Len 5 : %u\n", (unsigned int)len(listInt));
  printf("Len 5 : %u\n", (unsigned int)len(listFloat));
  printf("Len 5 : %u\n", (unsigned int)len(listChar));

  setitem(listInt, 4, 21);
  setitem(listFloat, 4, 21.00f);
  setitem(listChar, 4, 'b');

  printf("Val 21 : %s\n", str(getitem(listInt, 4)));
  printf("Val 21 : %s\n", str(getitem(listFloat, 4)));
  printf("Val b : %s\n", str(getitem(listChar, 4)));

  setitem(listInt, 4, 84);
  setitem(listFloat, 4, 84.00f);
  setitem(listChar, 4, 'z');

  printf("Val 84 : %s\n", str(getitem(listInt, 4)));
  printf("Val 84 : %s\n", str(getitem(listFloat, 4)));
  printf("Val z : %s\n", str(getitem(listChar, 4)));

  delete(listInt);
  delete(listFloat);
  delete(listChar);
  printf("\n\n");


  Object* list = new(List, 10, Int, 0);
  Object* it = begin(list);
  Object* it_end = end(list);

  printf("\n--- Second basics test ---\n");
  printf("The list has a size of %zu\n", len(list));
  setitem(list, 0, -1);
  setitem(list, 5, 12);
  setitem(list, 6, 13);
  setitem(list, 9, -1);


  printf("Try to select beg/end\n");
  printf("%s\n", str(getval(it)));
  printf("%s\n", str(getval(it_end)));

  printf("\nbegin to run through\n");
  int i = 0;
  while (i < 10)
    {
      printf("the Int [%u] is : %s\n", i, str(getitem(list, i)));
      i++;
    }

  printf("\n\n--------\n");
  i = 0;
  while (eq(it, it_end) == false)
    {
      printf("The Int [%u] is : %s\n", i, str(getval(it)));
      incr(it);
      i++;
    }
  printf("\n\n--------\n");
  printf("The End\n");

  printf("the Int [%u] is : %s == -1\n", 0, str(getitem(list, 0)));
  popfront(list);
  printf("the Int [%u] is : %s == 0\n", 0, str(getitem(list, 0)));
  printf("the Int [%u] is : %s == -1\n", 8, str(getitem(list, 8)));
  popback(list);
  printf("the Int [%u] is : %s == 0\n", 7, str(getitem(list, 7)));


  Object* lastInt = new(Int, -42);
  pushfront(list, lastInt);
  printf("the Int [%u] is : %s == -42\n", 0, str(getitem(list, 0)));
  pushback(list, lastInt);
  printf("the Int [%u] is : %s == -42\n", 9, str(getitem(list, 9)));

  delete(lastInt);
  delete(it);
  delete(it_end);
  delete(list);
  return 0;
}

