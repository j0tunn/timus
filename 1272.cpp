#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Задача на обход графа в ширину: нужно выяснить сколько несвязанных между собой туннелями графов (групп островов) всего
// Эти группы будут соединяться мостами
// Хорошее видео про обход в ширину: https://www.youtube.com/watch?v=iEgddjjoFnI
int main()
{
    unsigned int N, K, M;
    cin >> N >> K >> M;

    vector<unsigned int> tunnelEdges[N];

    for (unsigned int i = 0; i < K; ++i) {
        unsigned int u, v;
        cin >> u >> v;
        u--, v--; // На входе индексация с 1, в алгоритме - с 0

        tunnelEdges[u].push_back(v);
        tunnelEdges[v].push_back(u);
    }

    unsigned int graphs = 0;
    bool used[N];
    for (bool& u : used) {
        u = false;
    }

    for (unsigned int i = 0; i < N; ++i) {
        if (used[i]) {
            continue;
        }

        ++graphs;

        queue<unsigned int> q;
        q.push(i);
        used[i] = true;

        while (!q.empty()) {
            unsigned int v = q.front();
            q.pop();

            for (unsigned int i = 0; i < tunnelEdges[v].size(); ++i) {
                unsigned int to = tunnelEdges[v][i];
                if (used[to]) {
                    continue;
                }

                q.push(to);
                used[to] = true;
            }
        }
    }

    cout << graphs - 1 << endl;

    return 0;
}
