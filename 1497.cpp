// https://acm.timus.ru/problem.aspx?space=1&num=1497
// Вытащить нельзя, если сразу над 0 есть 1
// Для каждой грани, соприкасающейся с нулями, предварительно разворачиваем матрицу гранью вверх

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

using Row = vector<bool>;
using Matrix = vector<Row>;

bool hasZeroes(const Matrix& m, function<bool(const Matrix& m, unsigned short i)> getter) {
    for (unsigned short i = 0; i < m.size(); ++i) {
        if (getter(m, i) == false) {
            return true;
        }
    }

    return false;
}

bool hasZeroesAtTop(const Matrix& m) {
    return hasZeroes(m, [](const Matrix& m, unsigned short i) { return m.front()[i]; });
}

bool hasZeroesAtBottom(const Matrix& m) {
    return hasZeroes(m, [](const Matrix& m, unsigned short i) { return m.back()[i]; });
}

bool hasZeroesAtRight(const Matrix& m) {
    return hasZeroes(m, [](const Matrix& m, unsigned short i) { return m[i].back(); });
}

bool hasZeroesAtLeft(const Matrix& m) {
    return hasZeroes(m, [](const Matrix& m, unsigned short i) { return m[i].front(); });
}

Matrix transform(const Matrix& m, function<bool(const Matrix& src, unsigned short j, unsigned short i)> transformator) {
    Matrix target(m.size());

    for (unsigned short j = 0; j < m.size(); ++j) {
        target[j] = Row(m.size());

        for (unsigned short i = 0; i < m.size(); ++i) {
            target[j][i] = transformator(m, j, i);
        }
    }

    return target;
}

Matrix rotateCounterclockwise(const Matrix& m) {
    return transform(m, [](const Matrix& src, unsigned short j, unsigned short i) {
        return src[i][src.size() - j - 1];
    });
}

Matrix rotateClockwise(const Matrix& m) {
    return transform(m, [](const Matrix& src, unsigned short j, unsigned short i) {
        return src[src.size() - i - 1][j];
    });
}

Matrix flip(const Matrix& m) {
    return transform(m, [](const Matrix& src, unsigned short j, unsigned short i) {
        return src[src.size() - j - 1][i];
    });
}

bool check(const Matrix& m) {
    for (unsigned short j = 1; j < m.size(); ++j) {
        for (unsigned short i = 0; i < m[j].size(); ++i) {
            if (m[j][i] == false && m[j - 1][i] == true) {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    unsigned short N;
    cin >> N;

    Matrix m(N);
    for (unsigned short j = 0; j < N; ++j) {
        std::cin.ignore(1, '\n');
        m[j] = Row(N, true);

        for (unsigned short i = 0; i < N; ++i) {
            char c;
            std::cin.get(c);

            m[j][i] = c == '1';
        }
    }

    const bool result = hasZeroesAtTop(m) && check(m)
        || hasZeroesAtRight(m) && check(rotateCounterclockwise(m))
        || hasZeroesAtLeft(m) && check(rotateClockwise(m))
        || hasZeroesAtBottom(m) && check(flip(m));

    cout << (result ? "Yes" : "No") << endl;

    return 0;
}
