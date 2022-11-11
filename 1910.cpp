#include <iostream>

int main()
{
    unsigned int n, N;
    std::cin >> n;

    unsigned long pprev = 0, prev = 0, curr, res = 0, maxSum = 0;

    for (unsigned int i = 0; i < n; ++i, pprev = prev, prev = curr) {
        std::cin >> curr;
        if (pprev + prev + curr > maxSum) {
            maxSum = pprev + prev + curr;
            N = i; // Cредним элементом будет i - 1, но т.к. i идет с нуля, а ответ отсчитывается от 1, то i + 1 - 1 = i
        }
    }

    std::cout << maxSum << " " << N << std::endl;

    return 0;
}
