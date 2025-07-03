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

ll computeContribution(const vll &input, ll k, ll base, ll totalUnits)
{
    ll aggregate = 0;
    int n = input.size();
    for (int j = 0; j < n; ++j)
    {
        if (base + k >= 1)
            aggregate += min(input[j], base + k);
        if (base > input[j])
            aggregate += base - input[j];
        if (aggregate >= totalUnits)
            break;
    }
    return aggregate;
}

ll calculateCost(const vll &input, const vll &distribution, ll k)
{
    ll total = 0, extra = 0;
    int n = input.size();
    for (int j = 0; j < n; ++j)
    {
        total += distribution[j] * (distribution[j] + 1) / 2;
        if (input[j] > distribution[j])
            extra += input[j] - distribution[j];
    }
    return total + k * extra;
}

void solve()
{
    int n;
    ll k;
    cin >> n >> k;

    vll input(n);
    ll totalUnits = 0, highest = 0;

    for (int idx = 0; idx < n; ++idx)
    {
        cin >> input[idx];
        totalUnits += input[idx];
        highest = max(highest, input[idx]);
    }

    ll low = 1 - k;
    ll high = min(highest + totalUnits, 1000000000000LL);

    while (low < high)
    {
        ll mid = low + (high - low) / 2;
        if (computeContribution(input, k, mid, totalUnits) >= totalUnits)
            high = mid;
        else
            low = mid + 1;
    }

    ll optimalBase = low;
    vll distribution(n, 0);
    ll accumulated = 0;

    for (int j = 0; j < n; ++j)
    {
        ll threshold = optimalBase - 1, assign = 0;
        if (threshold + k >= 1)
            assign += min(input[j], threshold + k);
        if (threshold > input[j])
            assign += threshold - input[j];
        distribution[j] = assign;
        accumulated += assign;
    }

    ll pending = totalUnits - accumulated;

    for (int j = 0; j < n && pending > 0; ++j)
    {
        ll cost = (distribution[j] < input[j]) ? distribution[j] + 1 - k : distribution[j] + 1;
        if (cost == optimalBase)
        {
            ++distribution[j];
            --pending;
        }
    }

    cout << calculateCost(input, distribution, k) << '\n';
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
