#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

// Достаточно решить для одного цвета
// Считываем позиции в map, где:
// - ключ - индекс угла 0, 1, 2, 3 по часовой стрелке, в котором находится кубик определенного цвета
// - значение - сколько таких кубиков в этом углу
// Далее нахоим угол, в котором больше всего кубиков, и складываем расстояния от остальных до него
// с учетом возможности крутить как в одну, так и в другую сторону
int main()
{
    map<unsigned short, unsigned short> positions;

    for (unsigned short i = 0; i < 4; ++i) {
        for (unsigned short j = 0; j < 4; ++j) {
            unsigned short color;

            cin >> color;
            if (color != 1) {
                continue;
            }

            unsigned short index = i < 2
                ? (j < 2 ? 0 : 1)
                : (j < 2 ? 3 : 2);

            positions[index] += 1;
        }
    }

    const unsigned short baseLine = max_element(positions.begin(), positions.end(), [](auto a, auto b) { return a.second < b.second; })->first;

    unsigned short res = 0;
    for (auto& p : positions) {
        res += p.second * (
            p.first < baseLine
                ? min(baseLine - p.first, 4 - baseLine + p.first)
                : min(p.first - baseLine, 4 - p.first + baseLine)
        );
    }

    cout << res << endl;

    return 0;
}
