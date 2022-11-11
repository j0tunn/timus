#include <iostream>
#include <map>
#include <algorithm>

int main()
{
    std::map<unsigned long, unsigned short> m;

    for (unsigned int i = 0; i < 3; ++i) {
        unsigned int n;
        std::cin >> n;
        for (; n > 0; --n) {
            unsigned long a;
            std::cin >> a;

            m[a] += 1;
        }
    }

    unsigned int res = std::count_if(m.begin(), m.end(), [](auto const& p) { return p.second == 3; });

    std::cout << res << std::endl;

    return 0;
}
