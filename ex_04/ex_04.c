#include <stdio.h>
#include <assert.h>

#include "char.h"
#include "int.h"
#include "float.h"
#include "new.h"

void test(Object* a, Object* b, Object* c)
{
    printf("a = %s, b = %s, c = %s\n", str(a), str(b), str(c));
    assert(eq(a, b));
    assert(!gt(a, b));
    assert(!lt(a, b));
    assert(!eq(a, c));
    assert(eq(a, b));
    assert(gt(c, a));

    delete(a);
    delete(b);
    delete(c);
}

void compareAndDivide(Object* a, Object* b)
{
 if (gt(a, b))
 printf("a > b\n");
 else if (lt(a, b))
 printf("a < b\n");
 else
 printf("a == b\n");
 printf("b / a = %s\n", str(div(b, a)));
}

int main()
{
    test(new(Int, 12), new(Int, 12), new(Int, 13));
    test(new(Int, -42), new(Int, -42), new(Int, 0));
    test(new(Int, 0), new(Int, 0), new(Int, 1));
    test(new(Char, 'a'), new(Char, 'a'), new(Char, 'z'));
    test(new(Char, '\0'), new(Char, '\0'), new(Char, 'd'));
    test(new(Float, 3.14159f), new(Float, 3.14159f), new(Float, 3.15f));

    new(Float, 1);
    new(Float, -42,42);
    new(Float, 0);
    new(Float, '\b');
    new(Float, 424242424242424242);
    new(Int, 0);
    new(Int, -42);
    new(Char, 0);
    new(Char, '\n');
    new(Char, '\0');
    new(Char, -42);
    new(Char, -42,42);
    new(Char, 424242424242424242);


    compareAndDivide(new(Int, 12), new(Int,2));
    compareAndDivide(new(Int, 12), new(Int,12));
    compareAndDivide(new(Int, 12), new(Int,22));
    compareAndDivide(new(Int, -2), new(Int,12));
    compareAndDivide(new(Int, -2), new(Int,-42));
    compareAndDivide(new(Int, 0), new(Int, 12));
    return 0;
}
