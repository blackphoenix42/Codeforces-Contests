#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int to;
    long long w;
};

int n, m, q;
vector<vector<Edge>> graph;
vector<int> scc_id;
vector<vector<int>> scc_nodes;
int scc_count;

vector<int> stack_scc, on_stack;
int time_dfs, dfs_num, low_link;
vector<int> dfn, low;

void tarjan(int u)
{
    dfn[u] = low[u] = ++time_dfs;
    stack_scc.push_back(u);
    on_stack[u] = 1;
    for (auto &e : graph[u])
    {
        int v = e.to;
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (on_stack[v])
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u])
    {
        vector<int> comp;
        while (true)
        {
            int x = stack_scc.back();
            stack_scc.pop_back();
            on_stack[x] = 0;
            scc_id[x] = scc_count;
            comp.push_back(x);
            if (x == u)
                break;
        }
        scc_nodes.push_back(comp);
        scc_count++;
    }
}

bool scc_has_cycle(const vector<int> &comp, const vector<vector<Edge>> &g)
{
    if ((int)comp.size() > 1)
        return true;
    int u = comp[0];
    for (auto &e : g[u])
    {
        if (e.to == u)
            return true;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    graph.assign(n, {});
    scc_id.assign(n, -1);
    dfn.assign(n, 0);
    low.assign(n, 0);
    on_stack.assign(n, 0);

    for (int i = 0; i < m; ++i)
    {
        int x, y;
        long long z;
        cin >> x >> y >> z;
        --x;
        --y;
        graph[y].push_back({x, z});
    }

    time_dfs = 0;
    scc_count = 0;
    for (int i = 0; i < n; ++i)
        if (!dfn[i])
            tarjan(i);

    vector<bool> scc_cycle(scc_count, false);
    for (int i = 0; i < scc_count; ++i)
    {
        scc_cycle[i] = scc_has_cycle(scc_nodes[i], graph);
    }

    cin >> q;
    while (q--)
    {
        long long k;
        cin >> k;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i];

        string ans(n, '0');

        for (int i = 0; i < n; ++i)
        {
            if (scc_cycle[scc_id[i]] && k > 0)
            {
                ans[i] = '1';
            }
        }

        cout << ans << "\n";
    }

    return 0;
}