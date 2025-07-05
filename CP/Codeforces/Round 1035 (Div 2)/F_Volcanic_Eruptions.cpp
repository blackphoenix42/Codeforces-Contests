/**
 *    Name:    Ayush Yadav
 *    Author:  IndianTourist01
 *    Created: 2025-07-05
 *    Profile: https://codeforces.com/profile/IndianTourist01
 **/

#include <bits/stdc++.h>
using namespace std;

// Fast IO
#define fastio()                 \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);            \
    cout.tie(nullptr);

using ll = long long;
#define print(x) cout << (x) << '\n'

void solve() {
    int n, st;
    cin >> n >> st;
    vector<int> w(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    vector<vector<int>> adj(n+1);
    for (int i = 0, u, v; i < n-1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 1) BFS from root=1 to compute flood times
    vector<int> dist(n+1, -1);
    queue<int> q;
    dist[1] = 0;
    q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v: adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    // 2) Greedy frontier: max-heap of (weight, vertex)
    //    Start at 'st' at time t=0 with life S=1.
    ll S = 1;
    int t = 0;
    priority_queue<pair<int,int>> pq;
    // push the start vertex as our first “move”
    pq.push({w[st], st});

    int bestMoves = 0;
    while (!pq.empty()) {
        auto [cw, u] = pq.top();
        pq.pop();
        // would arrive at time t+1
        if (t+1 >= dist[u]) {
            // flooded on arrival, skip
            continue;
        }
        // make the move
        t++;
        S += cw;
        if (S <= 0) break;   // you die immediately
        bestMoves = t;
        // push all neighbors as future candidates
        for (int v: adj[u]) {
            pq.push({w[v], v});
        }
    }

    print(bestMoves);
}

int main() {
    fastio();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
