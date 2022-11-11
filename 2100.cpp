#include <iostream>

int main()
{
    unsigned short n;

    std::cin >> n;

    for (;;) {
        // 450 > максимум 20 гостей по максимум 20 символов + 1 символ перевода строки (+ на всякий слуачай несколько символов)
        std::cin.ignore(450, '+');

        if (std::cin.eof()) {
            break;
        } else {
            ++n;
        }
    }

    n += 2;
    if (n == 13) {
        ++n;
    }

    std::cout << n * 100 << std::endl;

    return 0;
}
