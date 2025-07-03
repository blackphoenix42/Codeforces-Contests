/**
 *    Name:    Ayush Yadav
 *    author:  blackphoenix42
 *    profile: https://codeforces.com/profile/blackphoenix42
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
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vpii = vector<pii>;
using vpll = vector<pll>;

// Macros
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) int((x).size())
#define ff first
#define ss second
#define YES cout << "YES\n"
#define NO cout << "NO\n"

// Debugging (disable before submission)
// #define LOCAL
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

// Constants
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

bool canFormLine(int a1, int b1, int a2, int b2, int a3, int b3)
{
    if (b1 == b2 && b2 == b3 && a1 + a2 + a3 == b1)
        return true;
    if (a1 == a2 && a2 == a3 && b1 + b2 + b3 == a1)
        return true;
    return false;
}

bool canFitL(int a1, int b1, int a2, int b2, int a3, int b3)
{
    vector<tuple<int, int, int, int, int, int>> configs = {
        {a1, b1, a2, b2, a3, b3},
        {a2, b2, a1, b1, a3, b3},
        {a3, b3, a1, b1, a2, b2}};

    for (auto &[x1, y1, x2, y2, x3, y3] : configs)
    {
        int S = max(x1, y1);
        if ((x1 == S && y2 == y3 && y1 + max(y2, y3) == S && x2 + x3 == S) ||
            (y1 == S && x2 == x3 && x1 + max(x2, x3) == S && y2 + y3 == S))
            return true;
    }
    return false;
}

void solve()
{
    int x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    if (canFormLine(x1, y1, x2, y2, x3, y3) || canFitL(x1, y1, x2, y2, x3, y3))
        YES;
    else
        NO;
}

int main()
{
    fastio();
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
