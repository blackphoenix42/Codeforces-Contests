/**
 *    Name:    Ayush Yadav
 *    author:  blackphoenix42
 *    profile: https://codeforces.com/profile/blackphoenix42
 **/

#include <bits/stdc++.h>
using namespace std;

#define fastio()                 \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);            \
    cout.tie(nullptr)

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vpii = vector<pii>;
using vpll = vector<pll>;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) int((x).size())
#define ff first
#define ss second
#define YES cout << "YES\n"
#define NO cout << "NO\n"

#ifdef LOCAL
#define dbg(x)           \
    cerr << #x << " = "; \
    _print(x);           \
    cerr << endl;
#else
#define dbg(x)
#endif

void _print(int x) { cerr << x; }
void _print(ll x) { cerr << x; }
void _print(char x) { cerr << x; }
void _print(string x) { cerr << x; }
void _print(double x) { cerr << x; }
template <typename T, typename V>
void _print(pair<T, V> p)
{
    cerr << "{";
    _print(p.ff);
    cerr << ", ";
    _print(p.ss);
    cerr << "}";
}
template <typename T>
void _print(vector<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}

const ll INF = 1e18;
const int MOD = 1e9 + 7;

ll mod_add(ll a, ll b) { return (a + b) % MOD; }
ll mod_sub(ll a, ll b) { return ((a - b) % MOD + MOD) % MOD; }
ll mod_mul(ll a, ll b) { return (a * b) % MOD; }
ll mod_pow(ll a, ll b)
{
    ll res = 1;
    a %= MOD;
    while (b > 0)
    {
        if (b & 1)
            res = mod_mul(res, a);
        a = mod_mul(a, a);
        b >>= 1;
    }
    return res;
}
ll mod_inv(ll a) { return mod_pow(a, MOD - 2); }

void solve()
{
    ll nodes, sumReq;
    cin >> nodes >> sumReq;

    ll minSum = nodes;
    ll maxSum = nodes * (nodes + 1) / 2;

    if (sumReq < minSum || sumReq > maxSum)
    {
        cout << "-1\n";
        return;
    }

    int rootDepth = 1;
    for (int d = 1; d <= nodes; ++d)
    {
        ll lo = nodes + 1LL * d * (d - 1) / 2;
        ll hi = 1LL * d * nodes - 1LL * d * (d - 1) / 2;
        if (sumReq >= lo && sumReq <= hi)
        {
            rootDepth = d;
            break;
        }
    }

    ll maxPossible = 1LL * rootDepth * nodes - 1LL * rootDepth * (rootDepth - 1) / 2;
    ll remaining = maxPossible - sumReq;

    vpii edges;
    edges.reserve(nodes - 1);

    for (int i = 1; i < rootDepth; ++i)
        edges.pb({rootDepth, i});

    for (int v = rootDepth + 1; v <= nodes; ++v)
    {
        if (remaining > 0)
        {
            ll dec = min(remaining, 1LL * (rootDepth - 1));
            int parent = rootDepth - (int)dec;
            edges.pb({parent, v});
            remaining -= dec;
        }
        else
        {
            edges.pb({rootDepth, v});
        }
    }

    cout << rootDepth << '\n';
    for (auto &[u, v] : edges)
        cout << u << ' ' << v << '\n';
}

int main()
{
    fastio();
    int t;
    if (!(cin >> t))
        return 0;
    while (t--)
    {
        solve();
    }
    return 0;
}
