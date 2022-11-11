#include <iostream>
#include <cstdio>
#include <deque>
#include <cmath>

int main()
{
    unsigned long long x;
    std::deque<unsigned long long> input;

    while (std::cin >> x) {
        input.push_back(x);
    }

    for (x = input.size(); x > 0; --x) {
        std::printf("%.4f\n", std::sqrt(input[x - 1]));
    }

    return 0;
}
