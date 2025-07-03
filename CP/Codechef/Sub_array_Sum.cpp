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
#define LOCAL
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
// const int MOD = 998244353;
// const int N = 2e5 + 5;

// Modular arithmetic utils (optional)
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

ll get_max(vi &arr, int &n)
{
    vi pre(n), suf(n);

    for (int i = 0; i < n; i++)
    {
        int j = i;

        while (j > 0 && arr[j - 1] <= arr[i])
        {
            j = pre[j - 1];
        }

        pre[i] = j;
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int j = i;

        while (j < n - 1 && arr[j + 1] < arr[i])
        {
            j = suf[j + 1];
        }

        suf[i] = j;
    }

    ll res = 0;

    for (int i = 0; i < n; i++)
    {
        ll sub = 1LL * (i - pre[i] + 1) * (suf[i] - i + 1);
        res += 1LL * arr[i] * sub;
    }

    return res;
}

ll get_min(vi &arr, int &n)
{
    vi pre(n), suf(n);

    for (int i = 0; i < n; i++)
    {
        int j = i;

        while (j > 0 && arr[j - 1] >= arr[i])
        {
            j = pre[j - 1];
        }

        pre[i] = j;
    }
    // dbg(pre);
    for (int i = n - 1; i >= 0; i--)
    {
        int j = i;

        while (j < n - 1 && arr[j + 1] > arr[i])
        {
            j = suf[j + 1];
        }

        suf[i] = j;
    }
    //   dbg(suf);

    ll res = 0;

    for (int i = 0; i < n; i++)
    {
        ll sub = 1LL * (i - pre[i] + 1) * (suf[i] - i + 1);
        res += 1LL * arr[i] * sub;
    }

    return res;
}

void solve()
{
    int n;
    cin >> n;
    vi arr(n);

    for (int &i : arr)
        cin >> i;

    ll a = get_max(arr, n);
    ll b = get_min(arr, n);
    cout << a - b << "\n";
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
