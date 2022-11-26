#include <iostream>
#include <cmath>

using namespace std;

// Задача симметричная, поэтому решаем для четверти круга, и результат умножаем на 4
// Общая площать состоит из квадарата с диагональю R (с округлением в большую сторону до полного квадратика)
// и двух половинок сегмента
// Площадь сегмента считаем построчно, для каждой строки высчитывая x исходя из формулы x*x + y*y = R*R
// (опять же округляя в большую сторону)
// Вазно: следить за неявным привдением типов: long * long сначала обрежется до long, а потом присвоится в double
int main()
{
    unsigned long R;

    cin >> R;

    const unsigned long fullX = ceil(R / sqrt(2));

    unsigned long long res = 0;
    const long double Rsqr = static_cast<long double>(R) * R;
    for (unsigned long y = fullX; y < R; ++y) {
        res += ceill(sqrt(Rsqr - static_cast<unsigned long long>(y)*y));
    }

    cout << 4 * (static_cast<unsigned long long>(fullX) * fullX + 2 *res) << endl;

    return 0;
}
