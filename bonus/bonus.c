
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
    setitem(list, 0, -1);
    setitem(list, 5, 12);
    setitem(list, 6, 13);
    setitem(list, 9, -1);

    printf("Try to select beg/end\n");
    printf("%s\n", str(getval(it)));
    printf("%s\n", str(getval(it_end)));

    printf("begin to run through\n");
    int i = 0;
    while (i < 10)
      {
        printf("the int [%u] is : %s\n", i, str(getitem(list, i)));
        i++;
      }

    printf("\n\n--------\n");
    i = 0;
    while (lt(it, it_end))
      {
        printf("i ... %u ...\n", i);
        printf("The int [%u] is : %s\n", i, str(getval(it)));
        incr(it);
        i++;
    }
    printf("\n\n--------\n");

    printf("The int [%u] is : %s\n", i, str(getval(it)));
    decr(it);
    printf("The int [%u] is : %s\n", i, str(getval(it)));

    delete(it);
    delete(it_end);
    delete(list);
    return 0;
}

