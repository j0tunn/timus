#include <iostream>

int main()
{
    unsigned int N;

    std::cin >> N;
    std::cout <<
        (N <= 4 ? "few"
            : N <= 9 ? "several"
                : N <= 19 ? "pack"
                    : N <= 49 ? "lots"
                        : N <= 99 ? "horde"
                            : N <= 249 ? "throng"
                                : N <= 499 ? "swarm"
                                    : N <= 999 ? "zounds"
                                        : "legion")
        << std::endl;

    return 0;
}
