#include <iostream>
#include <cmath>
#include <limits>
#include <map>

// Простой DP
// Важно следить за накоплением погрешности в double

using namespace std;
using Cache = map<unsigned int, unsigned int>;

unsigned int getMaxTransitions(const unsigned int start, const unsigned int limit, Cache& cache) {
    if (cache.contains(start)) {
        return cache[start];
    }

    unsigned int maxTransitions = 0;

    for (unsigned short i = 1; i <= 100; ++i) {
        // Решение с выражением `start * (1 + static_cast<double>(i) / 100)` не пройдет,
        // т.к. 1 при преобразовании в double будет иметь какую-то погрешность, и при умножении на start
        // погрешность станет слишком большой
        const double nextCandidate = start + start * static_cast<double>(i) / 100;
        if (nextCandidate > limit) {
            break;
        }

        if (nextCandidate != round(nextCandidate)) {
            continue;
        }

        const unsigned int maxCandidate = 1 + getMaxTransitions(nextCandidate, limit, cache);
        if (maxCandidate > maxTransitions) {
            maxTransitions = maxCandidate;
        }
    }

    cache[start] = maxTransitions;

    return maxTransitions;
}

int main()
{
    unsigned int n, s;
    cin >> n >> s;

    Cache cache;
    cout << 1 + getMaxTransitions(s, n, cache) << endl;

    return 0;
}
