#include <iostream>

// Кол-во ходов всегда будет на 1 меньше площади плитки
// Соответственно дальше нужно просто проверить m*n на четность.
int main()
{
    unsigned short m, n;

    std::cin >> m >> n;
    std::cout << (
        (m & 1) && (n & 1) ? "[second]=:]" : "[:=[first]"
    ) << std::endl;

    return 0;
}
