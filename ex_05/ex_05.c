
#include <stdio.h>
#include <assert.h>

#include "array.h"
#include "int.h"
#include "new.h"


int main()
{
    Object* array = new(Array, 15, Int, 0);
    Object* it = begin(array);
    Object* it_end = end(array);

    printf("array size: %zu\n", len(array));
    setitem(array, 5, 12);
    setitem(array, 6, 13);
    setitem(array, 7, 'd');
    setitem(array, 8, -42);
    setitem(array, 9, 42);
    setitem(array, 10, 2);
    setitem(array, 11, 5);


    printf("begin to run through\n");
    int i = 0;
    while (i < 10)
      {
        printf("the int [%u] is : %s\n", i, str(getitem(array, i)));
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

    printf("should abort NOW :\n");
    setitem(array, 9999, 5);
    delete(it);
    delete(it_end);
    delete(array);
    return 0;
}

