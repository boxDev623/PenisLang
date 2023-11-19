#include <iostream>
#include <stdint.h>

// This is a comment in penis.

namespace test
{
    enum penis_type
    {
        PENIS_TYPE_BLACK,
        PENIS_TYPE_ASIAN,
        PENIS_TYPE_WHITE
    };

    struct penis
    {
        int32_t a;
        int32_t b;
        float c;
    };

    int32_t add(penis &p)
    {
        return p.a + p.b;
    }

    int32_t add(int32_t a, int32_t b)
    {
        return a + b;
    }
}

void somefunctionname()
{

}

void moan(std::string str)
{
    std::cout << str << std::endl;
}

int main(void)
{
    test::penis p;
    p.a = 69;
    p.b = 420;

    if (p.a == 69)
    {
        p.a = 1;
    }
    else if (p.b == 420)
    {
        p.b = 1;
    }
    else
    {
        p.a = 0;
        p.b = 0;
    }

    for (int32_t i; i < 10; i++)
    {
        p.a++;
    }

    switch (p.a)
    {
        case 1: p.b = 2;
        break;
    }

    moan("Hello World!");

    return test::add(p);
}