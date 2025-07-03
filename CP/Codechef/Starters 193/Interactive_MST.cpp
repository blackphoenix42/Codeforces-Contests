#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
};

int N, M;
vector<Edge> edges;

int mst(const vector<int>& weights, vector<int>* used_edges = nullptr) {
    vector<tuple<int,int,int,int>> es;
    for (int i = 0; i < M; ++i)
        es.emplace_back(weights[i], edges[i].u, edges[i].v, i);
    sort(es.begin(), es.end());
    vector<int> parent(N);
    iota(parent.begin(), parent.end(), 0);
    function<int(int)> find = [&](int x) {
        return parent[x]==x ? x : parent[x]=find(parent[x]);
    };
    int total = 0;
    if (used_edges) used_edges->clear();
    for (auto [w, u, v, idx] : es) {
        int pu = find(u), pv = find(v);
        if (pu != pv) {
            parent[pu] = pv;
            total += w;
            if (used_edges) used_edges->push_back(idx);
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T; cin >> T;
    while (T--) {
        cin >> N >> M;
        edges.clear(); edges.resize(M);
        vector<int> W(M);
        for (int i = 0; i < M; ++i) {
            int u, v, w; cin >> u >> v >> w;
            --u; --v;
            edges[i] = {u, v};
            W[i] = w;
        }

        int ans = INT_MAX;

        // Try every possible assignment of 0/1s
        for (int mask = 0; mask < (1<<M); ++mask) {
            vector<int> testW(M);
            for (int i = 0; i < M; ++i)
                testW[i] = (mask >> i) & 1;

            bool ok = true;

            // For each edge, can we make it appear in some MST (by choosing query vector A)?
            for (int i = 0; i < M && ok; ++i) {
                bool found = false;
                // Try two "query vectors": all 1's and only edge i set to 1, rest 0
                // (more generally, try all 2^M possible A, but two is enough for 0/1 weights!)
                for (int flip = 0; flip < 2; ++flip) {
                    vector<int> A(M, 1);
                    if (flip == 1) fill(A.begin(), A.end(), 0), A[i] = 1;
                    vector<int> weighted(M);
                    for (int j = 0; j < M; ++j)
                        weighted[j] = A[j] * testW[j];

                    vector<int> used;
                    mst(weighted, &used);
                    if (find(used.begin(), used.end(), i) != used.end())
                        found = true;
                }
                if (!found) ok = false;
            }

            if (ok) {
                // Count flips needed
                int flips = 0;
                for (int i = 0; i < M; ++i)
                    if (W[i] != testW[i]) ++flips;
                ans = min(ans, flips);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
