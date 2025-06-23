/**
 *    Name:    Ayush Yadav
 *    author:  blackphoenix42
 *    created: 2025-06-23 20:19:59
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
using pss = pair<string, string>;
using pll = pair<ll, ll>;
using vs = vector<string>;
using vvs = vector<vector<string>>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vi = vector<int>;
using vvi = vector<vi>;
using vpii = vector<pii>;
using vpll = vector<pll>;

// Macros
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()
#define ALL(v) v.begin(), v.end()
#define ALLA(arr, sz) arr, arr + sz
#define sz(x) int((x).size())
#define SIZE(v) (int)v.size()
#define SORT(v) sort(ALL(v))
#define SORTA(arr, sz) sort(ALLA(arr, sz))
#define REVERSE(v) reverse(ALL(v))
#define REVERSEA(arr, sz) reverse(ALLA(arr, sz))
#define SORT_BY(vec, key) sort(vec.begin(), vec.end(), [&](auto &a, auto &b) { return a.key < b.key; })
#define UNIQUE(v) (v).erase(unique(all(v)), (v).end())
#define PERMUTE next_permutation
#define fi first
#define se second
#define YES cout << "YES\n"
#define NO cout << "NO\n"
#define FOR(a, b, c) for (int a = (b); (a) < (c); ++(a))
#define FOR1(a, c) for (; (a) < (c); ++(a))
#define FORN(a, b, c) for (int(a) = (b); (a) <= (c); ++(a))
#define FORD(a, b, c) for (int(a) = (b); (a) >= (c); --(a))
#define FORSQ(a, b, c) for (int(a) = (b); (a) * (a) <= (c); ++(a))
#define FORC(a, b, c) for (char(a) = (b); (a) <= (c); ++(a))
#define EACH(a, b) for (auto &(a) : (b))
#define REP(i, n) FOR(i, 0, n)
#define REPN(i, n) FORN(i, 1, n)
#define MAX(a, b) a = max(a, b)
#define MIN(a, b) a = min(a, b)
#define SQR(x) ((ll)(x) * (x))
#define RESET(a, b) memset(a, b, sizeof(a))
#define nl '\n'
#define el cout << '\n'
#define print(x) cout << (x) << '\n'
#define flush cout << endl \
                   << flush
#define umap unordered_map
#define uset unordered_set
#define freq(v)       \
    map<ll, ll> freq; \
    for (auto x : v)  \
    freq[x]++

#define lb lower_bound
#define ub upper_bound
#define bs binary_search
#define rev reverse
#define setbits(x) __builtin_popcountll(x)
#define parity(x) (__builtin_parityll(x))
#define clz(x) __builtin_clzll(x)
#define ctz(x) __builtin_ctzll(x)
#define ffs(x) __builtin_ffsll(x)

#define READVEC(vec)    \
    for (auto &x : vec) \
        cin >> x;
#define READARR(arr, n)         \
    for (int i = 0; i < n; ++i) \
        cin >> arr[i];
#define READ_VEC(vec, n) \
    vi vec(n);           \
    for (auto &x : vec)  \
        cin >> x;
#define READ_ARR(arr, n)        \
    int arr[n];                 \
    for (int i = 0; i < n; ++i) \
        cin >> arr[i];
#define read_pair(a, b) cin >> a >> b
#define write_pair(p) cout << p.first << " " << p.second << '\n'

// Constants
#define USE_MOD1 1
#if USE_MOD1
const int MOD = 1e9 + 7;
#else
const int MOD = 998244353;
#endif
const ll INFF = 1000000000000000005ll;
const double PI = acos(-1);
const double EPS = 1e-9;
const ll INF = 1e18;
const int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const int dirx[8] = {-1, 0, 0, 1, -1, -1, 1, 1};
const int diry[8] = {0, 1, -1, 0, -1, 1, -1, 1};
#define in_bounds(x, y, n, m) (x >= 0 && x < n && y >= 0 && y < m)

void solve()
{
    int n;
    cin >> n;
    vi a(n);
    READVEC(a);
    SORT(a);

    int max1 = a[n - 1];
    int max2 = a[n - 2];
    ll total = 0;

    FOR(k, 2, n)
    {
        ll x = 2LL * a[k];
        ll y = (k == n - 1) ? max2 : max1;
        ll threshold = max(x, y) - a[k];

        int l = 0, r = k - 1;
        while (l < r)
        {
            if (a[l] + a[r] > threshold)
            {
                total += (r - l);
                --r;
            }
            else
            {
                ++l;
            }
        }
    }
    print(total);
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
