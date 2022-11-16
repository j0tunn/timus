#include <iostream>
#include <map>
#include <cstdint>

using namespace std;

// Dynamic Programming + немного комбинаторики
// Формула: f(N) = 1 + ∑ C(N, i) * f(N-i) для i : [1, N-1]
// C(N, i) - число сочетаний из N по i : C(N, i) = N! / ((N - i)! * i!)
//
// Формула строится вокруг количества символов =, а точнее количества объектов в группе, соединенной отношением = (это и есть i)
// Условно можно представить (i - 1) как количество символов =, идущих подряд, которые мы фиксируем слева.
// Для каждой фиксации считаем количество возможных вариантов формирования группы из i объектов - С(N, i)
// И умножаем на решение той же задачи для оставшихся (N - i) объектов
//
// Когда все объекты соединены отношением =, то как ни переставляй их,
// будет только одно отношение. Это частный случай, который выражается единичкой в формуле.

uint32_t fact(uint8_t n) {
    return n == 0 ? 1 : n * fact(n - 1);
}

uint32_t f(uint8_t n, map<uint8_t, uint32_t>& cache) {
    auto it = cache.find(n);
    if (it != cache.end()) {
        return it->second;
    }

    uint32_t res = 1;
    for (uint8_t i = 1; i < n; ++i) {
        res += fact(n)/(fact(n - i) * fact(i)) * f(n - i, cache);
    }

    cache.insert({n, res});
    return res;
}

int main()
{
    map<uint8_t, uint32_t> cache = {{1, 1}};

    for(;;) {
        int N;
        cin >> N;

        if (N == -1) {
            break;
        }

        cout << f((uint8_t)N, cache) << endl;
    }

    return 0;
}
