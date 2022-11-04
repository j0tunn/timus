#include <iostream>

// Поскольку задача симметричная, то достаточно решить ее для одного из углов 4x4 (допустим левого верхнего),
// в котором координаты будут равны отступу от края доски
// Внутри такого прямоугольника задача тоже симметричная относительно главной диагонали,
// поэтому координаты можно записать на бимапе с 4 цифрами:
// 0b1000 == a1
// 0b1100 == a2 или b1 - нас не волнует какая именно клетка, т.к. для них обеих ответ один - 3
// ...
int main()
{
    unsigned short N, coords;
    char c;

    std::cin >> N;

    for (; N > 0; --N) {
        std::cin.ignore(1, '\n');

        std::cin.get(c);
        coords = (0b1000 >> (c < 'e' ? c - 'a' : 'h' - c));

        std::cin.get(c);
        coords |= (0b1000 >> (c < '5' ? c - '1' : '8' - c));

        std::cout << (
            coords == 0b1000 ? 2
                : coords == 0b1100 ? 3
                    : (coords == 0b1010 || coords == 0b1001 || coords == 0b0100) ? 4
                        : (coords == 0b0110 || coords == 0b0101) ? 6
                            : 8
        ) << std::endl;
    }

    return 0;
}
