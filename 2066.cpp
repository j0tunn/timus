#include <iostream>

int main()
{
    unsigned short a, b, c;

    std::cin >> a >> b >> c;

    std::cout << (
        b == 0 ? a * b - c
            : b == 1 ? a - b - c
                : a - b * c
    ) << std::endl;

    return 0;
}
