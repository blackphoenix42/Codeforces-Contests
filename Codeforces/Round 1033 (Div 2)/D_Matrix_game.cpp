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
const int MOD = 1'000'000'007;

ll mod_add(ll a, ll b) { return (a + b) % MOD; }
ll mod_sub(ll a, ll b) { return ((a - b) % MOD + MOD) % MOD; }
ll mod_mul(ll a, ll b) { return (a % MOD) * (b % MOD) % MOD; }
ll mod_pow(ll a, ll b)
{
    ll res = 1;
    a %= MOD;
    while (b)
    {
        if (b & 1)
            res = mod_mul(res, a);
        a = mod_mul(a, a);
        b >>= 1;
    }
    return res;
}
ll mod_inv(ll a) { return mod_pow(a, MOD - 2); }

void solve_case(vector<tuple<ll, ll, ll>> &data, const vll &inv)
{
    for (auto &[x, y, rep] : data)
    {
        ll totalLen = (x - 1) * rep + 1;
        auto chooseMod = [&](ll n, int r) -> ll
        {
            ll prod = 1;
            for (int i = 1; i <= r; ++i)
            {
                ll num = (n - r + i) % MOD;
                prod = mod_mul(prod, num);
                prod = mod_mul(prod, inv[i]);
            }
            return prod;
        };

        ll countWays = chooseMod(totalLen, int(x));
        ll multiplier = mod_mul((y - 1) % MOD, rep % MOD);
        ll finalVal = mod_add(mod_mul(multiplier, countWays), 1);
        cout << totalLen % MOD << ' ' << finalVal << '\n';
    }
}

int main()
{
    fastio();
    int t;
    if (!(cin >> t))
        return 0;

    vector<tuple<ll, ll, ll>> dataset(t);
    int largest = 0;
    for (int i = 0; i < t; ++i)
    {
        ll x, y, rep;
        cin >> x >> y >> rep;
        dataset[i] = {x, y, rep};
        largest = max(largest, int(x));
    }

    vll inv(largest + 2);
    inv[1] = 1;
    for (int i = 2; i <= largest + 1; ++i)
        inv[i] = mod_sub(0, mod_mul(MOD / i, inv[MOD % i]));

    solve_case(dataset, inv);
    return 0;
}
