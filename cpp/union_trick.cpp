#include <iostream>
#include <stdint.h>

union Trick
{
    uint8_t char_array[4];
    float f;
} t,y,z;

int main()
{
   t.f = 0.1;
    y.f = 0.2;
    for (int i=0; i<4; i++)
    {
        std::cerr << static_cast<int>(t.char_array[i]) << std::endl;
    }
    return 0;
}
