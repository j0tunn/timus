#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

// Тригонометрия
// - если диаметр окружности больше, чем диагональ квадрата - весь квадрат
// - если диаметр окружности меньше, чем сторона квадрата - весь круг
// - в остальных случаях - площадь круга минус площать 4х выступающих сегментов
// Площадь сегмента: S = 1/2 * R * R * (a - sin(a))
// a - угол сектора, считаем из формулы для хорды: c = 2 * R * sin(a/2)
int main()
{
    double a, r; // Важно для прохождения тестов: не считывать значения в целые типы
    cin >> a >> r;

    const double d = 2 * r;

    if (d > a * sqrt(2.0)) {
        cout << a * a << endl;
        return 0;
    }

    const double pi = 4 * atan(1);
    double S = pi * r * r;

    if (d > a) {
        double alpha = 2 * asin(sqrt(1 - a * a/(d * d)));
        double Ssegment = r * r/2 * (alpha - sin(alpha));
        S -= 4 * Ssegment;
    }

    printf("%.3lf\n", S);

    return 0;
}
