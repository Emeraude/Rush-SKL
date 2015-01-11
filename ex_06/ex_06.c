
#include <stdio.h>
#include <assert.h>

#include "list.h"
#include "int.h"
#include "new.h"


int main()
{
    Object* list = new(List, 10, Int, 0);
    Object* it = begin(list);
    Object* it_end = end(list);

    printf("list size: %zu\n", len(list));
    setitem(list, 5, 12);
    setitem(list, 6, 13);
    printf("begin to run through\n");
    int i = 0;
    while (i < 10)
      {
        printf("the int [%u] is : %s\n", i, str(getitem(list, i)));
        i++;
      }

    printf("\n\n");
    i = 0;
    while (lt(it, it_end))
      {
        printf("The int [%u] is : %s\n", i, str(getval(it)));
        incr(it);
        i++;
    }

    delete(it);
    delete(it_end);
    delete(list);
    return 0;
}

