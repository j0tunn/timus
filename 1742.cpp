#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <list>

using namespace std;

using Vertices = vector<unsigned long>;

// Минимальное количество групп будет равно количеству листьев в графе
// Если граф полностью замкнутый, то 1
unsigned long getMinGroups(const Vertices& fromVertices, const vector<unsigned long>& transitions) {
    unordered_set<unsigned long> toVertices;
    for (const auto from : fromVertices) {
        toVertices.insert(transitions[from]);
    }

    const unsigned long diffSize = fromVertices.size() - toVertices.size();

    return diffSize > 0 ? diffSize : 1;
}

// Максимальное количество групп будет равно количеству вершин, не входящих в цикл, + 1 на сам цикл (цикл есть всегда)
unsigned long getMaxGroups(const Vertices& fromVertices, const vector<unsigned long>& transitions) {
    unordered_set<unsigned long> visited;
    unsigned long top;

    for(top = *fromVertices.begin();; top = transitions[top]) {
        const auto res = visited.insert(top);
        if (!res.second) {
            break;
        }
    }

    unsigned long cycleLen = 1;
    for(unsigned long next = transitions[top]; next != top; next = transitions[next]) {
        ++cycleLen;
    }

    return 1 + fromVertices.size() - cycleLen;
}

// Графов может быть несколько, несвязанных между собой. Нужно просуммировать результаты для каждого
// Важно - использовать структуры с постоянным временем вставки и доступа к элементам, иначе просто не уложимся в отведенную секунду
int main()
{
    unsigned long n;
    cin >> n;

    list<Vertices> verticesGroups;
    vector<unsigned long> transitions(n);
    vector<list<Vertices>::iterator> links(n, verticesGroups.end());
    for (unsigned long from = 0; from < n; ++from) {
        unsigned long p;
        cin >> p;

        unsigned long to = p - 1;
        transitions[from] = to;

        auto itFrom = links[from];
        auto itTo = links[to];

        if (itFrom == itTo) {
            if (itFrom == verticesGroups.end()) {
                verticesGroups.push_back({from});
                links[from] = prev(verticesGroups.end());
                links[to] = prev(verticesGroups.end());
            } else {
                itFrom->push_back(from);
            }

            continue;
        }

        if (itFrom == verticesGroups.end()) {
            links[from] = itTo;
            itTo->push_back(from);
            continue;
        }

        if (itTo == verticesGroups.end()) {
            links[to] = itFrom;
            itFrom->push_back(from);
            continue;
        }

        for (auto v : *itTo) {
            links[v] = itFrom;
            links[transitions[v]] = itFrom;
        }

        itFrom->reserve(itFrom->capacity() + itTo->size() + 1);
        itFrom->insert(itFrom->end(), itTo->begin(), itTo->end());
        itFrom->push_back(from);
        verticesGroups.erase(itTo);
        links[to] = itFrom;
    }

    const unsigned long minGroups = accumulate(verticesGroups.begin(), verticesGroups.end(), 0, [&transitions](unsigned long acc, const Vertices& g) {
        return acc + getMinGroups(g, transitions);
    });
    const unsigned long maxGroups = accumulate(verticesGroups.begin(), verticesGroups.end(), 0, [&transitions](unsigned long acc, const Vertices& g) {
        return acc + getMaxGroups(g, transitions);
    });

    cout << minGroups << " " << maxGroups << endl;

    return 0;
}
