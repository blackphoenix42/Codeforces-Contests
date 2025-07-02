/**
 *    Name:    Ayush Yadav
 *    Author:  IndianTourist01
 *    Created:
 *    Profile: https://codeforces.com/profile/IndianTourist01
 **/

#include <bits/stdc++.h>
using namespace std;

// Fast IO
#define fastio()                 \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);            \
    cout.tie(nullptr)

// Type aliases
using ll = long long;
using pii = pair<ll, int>;

// Macros
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FOR1(i, a, b) for (int i = (a); i <= (b); ++i)
#define all(x) (x).begin(), (x).end()
#define nl '\n'

static const ll MOD = 1'000'000'007;

void solve() {
    int N, K;
    cin >> N >> K;
    vector<ll> C(N + 1);
    FOR1(i, 1, N) { cin >> C[i]; }
    string A;
    cin >> A;

    set<int> sizes;
    FOR1(i, 1, N) sizes.insert(i);

    set<pii> byCost;
    FOR1(i, 1, N) byCost.insert({C[i], i});

    ll revenue = 0;
    for (char c : A) {
        int forbid = (c == '0' ? *sizes.rbegin() : *sizes.begin());

        auto it = prev(byCost.end());
        if (it->second == forbid) {
            it = prev(it);
        }
        revenue = (revenue + it->first) % MOD;
        int soldIdx = it->second;

        byCost.erase(it);
        sizes.erase(soldIdx);
    }

    cout << revenue << nl;
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
