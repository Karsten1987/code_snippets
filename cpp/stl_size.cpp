#include <iostream>
#include <vector>

int main()
{
    std::vector<int> a;
    a.reserve(10);
//    a[0] = 0;
//    a[1] = 1;
//    a[3] = 14;
    a.push_back(0);
    a.push_back(1);
    a.push_back(10);
    std::cerr << a[3] << std::endl;

    std::cerr << a.size() << std::endl;

    float max;
    float min;
    if (max<10)
        max=10;
    if (min>11)
        min=11;
    std::cerr << max << std::endl;
    std::cerr << min << std::endl;

    return 0;

}
