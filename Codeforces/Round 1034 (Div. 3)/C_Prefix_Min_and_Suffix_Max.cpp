/**
 *    Name:    Ayush Yadav
 *    Author:  IndianTourist01
 *    Created: 2025-07-01 20:32:06
 *    Profile: https://codeforces.com/profile/IndianTourist01
 **/

#include <bits/stdc++.h>
using namespace std;

// Fast IO
#define fastio()                 \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);            \
    cout.tie(nullptr);

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
using i128 = __int128_t;
using u128 = __uint128_t;

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
#define SORT_BY(vec, key)        \
    sort(vec.begin(), vec.end(), \
         [&](auto &a, auto &b) { return a.key < b.key; })
#define UNIQUE(v) (v).erase(unique(all(v)), (v).end())
#define PERMUTE next_permutation
#define fi first
#define se second
#define YES cout << "YES\n"
#define NO cout << "NO\n"
#define FOR(a, b, c) for (int a = b; a < c; ++a)
#define FOR1(a, c) for (; a < c; ++a)
#define FORN(a, b, c) for (int a = b; a <= c; ++a)
#define FORD(a, b, c) for (int a = b; a >= c; --a)
#define FORSQ(a, b, c) for (int a = b; a * a <= c; ++a)
#define FORC(a, b, c) for (char a = b; a <= c; ++a)
#define FOREQ(a, b, c) for (int a = b; a <= c; a += b)
#define EACH(a, b) for (auto &a : b)
#define REP(i, n) FOR(i, 0, n)
#define REPN(i, n) FORN(i, 1, n)
#define CP_MAX(a, b) a = max(a, b)
#define CP_MIN(a, b) a = min(a, b)
#define CP_SQR(x) ((ll)(x) * (x))
#define CP_RESET(a, b) memset(a, b, sizeof(a))
#define nl '\n'
#define el cout << '\n'
#define print(x) cout << (x) << '\n'
#define flush cout << endl << flush
#define umap unordered_map
#define uset unordered_set
#define freq(v)       \
    map<ll, ll> freq; \
    for (auto x : v) freq[x]++;

#define lb lower_bound
#define ub upper_bound
#define bs binary_search
#define rev reverse
#define setbits(x) __builtin_popcountll(x)
#define parity(x) (__builtin_parityll(x))
#define clz(x) __builtin_clzll(x)
#define ctz(x) __builtin_ctzll(x)
#define ffs(x) __builtin_ffsll(x)

#define READVEC(vec) \
    for (auto &x : vec) cin >> x;
#define READARR(arr, n) \
    for (int i = 0; i < n; ++i) cin >> arr[i];
#define READ_VEC(vec, n) \
    vi vec(n);           \
    for (auto &x : vec) cin >> x;
#define READ_ARR(arr, n) \
    int arr[n];          \
    for (int i = 0; i < n; ++i) cin >> arr[i];
#define read_pair(a, b) cin >> a >> b
#define write_pair(p) cout << p.first << " " << p.second << '\n'

// For TESTING
inline void OPEN(string s) {
#ifndef ONLINE_JUDGE
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
#endif
}
// Debugging
#ifdef LOCAL
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "] = ", debug_out(__VA_ARGS__)
#define dbg_idx(v) cerr << "[" #v "] = ", _print_with_index(v), cerr << '\n'
#else
#define dbg(...)
#define dbg_idx(v)
#endif

// Debug print helpers for primitive and STL types
// Primitive types
void _print(int x) { cerr << x; }
void _print(bool x) { cerr << (x ? "true" : "false"); }
void _print(ll x) { cerr << x; }
void _print(char x) { cerr << x; }
void _print(string x) { cerr << x; }
void _print(const double &x) { cerr << x; }
void _print(ld x) { cerr << x; }
void _print(ull x) { cerr << x; }

// STL Containers
template <typename T, typename V>
void _print(const pair<T, V> &p) {
    cerr << "{";
    _print(p.fi);
    cerr << ", ";
    _print(p.se);
    cerr << "}";
}
template <typename T>
void _print(const vector<T> &v) {
    cerr << "[ ";
    for (const auto &i : v) {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <typename T>
void _print_with_index(const vector<T> &v) {
    cerr << "[\n";
    for (size_t i = 0; i < v.size(); ++i) {
        cerr << "  [" << i << "]: ";
        _print(v[i]);
        cerr << '\n';
    }
    cerr << "]";
}
template <typename T>
void _print(const vector<vector<T>> &v) {
    cerr << "[\n";
    for (const auto &row : v) {
        cerr << "  ";
        _print(row);
        cerr << "\n";
    }
    cerr << "]";
}
template <typename T>
void _print(const set<T> &s) {
    cerr << "{ ";
    for (const auto &i : s) {
        _print(i);
        cerr << " ";
    }
    cerr << "}";
}
template <typename T>
void _print(const unordered_set<T> &s) {
    cerr << "{ ";
    for (const auto &i : s) {
        _print(i);
        cerr << " ";
    }
    cerr << "}";
}
template <typename T>
void _print(const multiset<T> &s) {
    cerr << "{ ";
    for (const auto &i : s) {
        _print(i);
        cerr << " ";
    }
    cerr << "}";
}
template <typename K, typename V>
void _print(const map<K, V> &m) {
    cerr << "{ ";
    for (const auto &p : m) {
        cerr << "[";
        _print(p.first);
        cerr << ": ";
        _print(p.second);
        cerr << "] ";
    }
    cerr << "}";
}
template <typename K, typename V>
void _print(const unordered_map<K, V> &m) {
    cerr << "{ ";
    for (const auto &p : m) {
        cerr << "[";
        _print(p.first);
        cerr << ": ";
        _print(p.second);
        cerr << "] ";
    }
    cerr << "}";
}
template <typename T>
void _print(const deque<T> &d) {
    cerr << "[ ";
    for (const auto &i : d) {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <typename T>
void _print(queue<T> q) {
    cerr << "[ ";
    while (!q.empty()) {
        _print(q.front());
        cerr << " ";
        q.pop();
    }
    cerr << "]";
}
template <typename T>
void _print(priority_queue<T> pq) {
    vector<T> temp;
    while (!pq.empty()) {
        temp.push_back(pq.top());
        pq.pop();
    }
    _print(temp);
}
template <typename T>
void _print(stack<T> s) {
    vector<T> temp;
    while (!s.empty()) {
        temp.push_back(s.top());
        s.pop();
    }
    reverse(temp.begin(), temp.end());
    _print(temp);
}
// Other types
template <typename T1, typename T2, typename T3>
void _print(const tuple<T1, T2, T3> &t) {
    cerr << "(";
    _print(get<0>(t));
    cerr << ", ";
    _print(get<1>(t));
    cerr << ", ";
    _print(get<2>(t));
    cerr << ")";
}
template <size_t N>
void _print(const bitset<N> &b) {
    cerr << b.to_string();
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    _print(H);
    if (sizeof...(T)) cerr << ", ";
    debug_out(T...);
}

// Constants
#define USE_MOD1 1
#if USE_MOD1
const int MOD = 1e9 + 7;
#else
const int MOD = 998244353;
#endif
// const int N = 2e5 + 5;
const ll INFF = 1000000000000000005ll;
const double PI = acos(-1);
const double EPS = 1e-9;
const ll INF = 1e18;
const ll INF_INT = 1e9;
const int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const int dirx[8] = {-1, 0, 0, 1, -1, -1, 1, 1};
const int diry[8] = {0, 1, -1, 0, -1, 1, -1, 1};
#define in_bounds(x, y, n, m) (x >= 0 && x < n && y >= 0 && y < m)

// Modular arithmetic utils (optional)
ll mod_add(ll a, ll b) { return (a + b) % MOD; }
ll mod_sub(ll a, ll b) { return ((a - b) % MOD + MOD) % MOD; }
ll mod_mul(ll a, ll b) { return (a * b) % MOD; }
ll mod_pow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) res = mod_mul(res, a);
        a = mod_mul(a, a);
        b >>= 1;
    }
    return res;
}
ll mod_inv(ll a) { return mod_pow(a, MOD - 2); }
ll mod_div(ll a, ll b) { return mod_mul(a, mod_inv(b)); }
ll ceil_div(ll a, ll b) { return (a + b - 1) / b; }
bool is_power_of_two(ll x) { return x && !(x & (x - 1)); }
int digit_sum(ll x) {
    int sum = 0;
    while (x) sum += x % 10, x /= 10;
    return sum;
}
int digit_count(ll x) {
    int cnt = 0;
    while (x) ++cnt, x /= 10;
    return cnt;
}

vi prefix_sum(const vi &a) {
    vi ps(sz(a) + 1);
    for (int i = 0; i < sz(a); ++i) ps[i + 1] = ps[i] + a[i];
    return ps;
}

vvi prefix_sum_2d(const vvi &grid) {
    int n = grid.size(), m = grid[0].size();
    vvi ps(n + 1, vi(m + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            ps[i][j] = grid[i - 1][j - 1] + ps[i - 1][j] + ps[i][j - 1] -
                       ps[i - 1][j - 1];
    return ps;
}
ll floor_sqrt(ll x) { return (ll)sqrtl(x); }
ll ceil_sqrt(ll x) {
    ll r = (ll)ceil(sqrtl(x));
    while (r * r > x) --r;
    while ((r + 1) * (r + 1) <= x) ++r;
    return r;
}

// -------------------- Math Utils --------------------
// Check primality (trial division up to sqrt(n))
bool is_prime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

// GCD / LCM
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// Extended Euclidean Algorithm
ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Modular Inverse using Extended Euclidean (when MOD not prime)
ll mod_inv_general(ll a, ll m) {
    ll x, y;
    ll g = extended_gcd(a, m, x, y);
    if (g != 1) return -1;  // Inverse doesn't exist
    return (x % m + m) % m;
}

// nCr % MOD using Fermat's Little Theorem (MOD must be prime)
const int MAXN = 2e5 + 5;
#ifndef ONLINE_JUDGE
ll fact[MAXN], inv_fact[MAXN];
#else
static ll fact[MAXN], inv_fact[MAXN];
#endif

void precompute_factorials(int n) {
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = mod_mul(fact[i - 1], i);
    inv_fact[n] = mod_inv(fact[n]);
    for (int i = n - 1; i >= 1; --i)
        inv_fact[i] = mod_mul(inv_fact[i + 1], i + 1);
}

ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return mod_mul(fact[n], mod_mul(inv_fact[r], inv_fact[n - r]));
}

// Sieve of Eratosthenes (0-based)
vi sieve(int n) {
    vi is_prime(n + 1, 1);
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i * i <= n; ++i)
        if (is_prime[i])
            for (int j = i * i; j <= n; j += i) is_prime[j] = 0;
    return is_prime;
}

// Prime factorization in O(sqrt(n))
vl prime_factors(ll n) {
    vl factors;
    for (ll i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            factors.pb(i);
            n /= i;
        }
    }
    if (n > 1) factors.pb(n);
    return factors;
}

// Binary exponentiation for power (a^b)
ll binpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

// Sum of first N natural numbers
ll sum_n(ll n) { return n * (n + 1) / 2; }
// Sum of squares 1^2 + 2^2 + ... + n^2
ll sum_n2(ll n) { return n * (n + 1) * (2 * n + 1) / 6; }
// Sum of cubes: (1 + 2 + ... + n)^2
ll sum_n3(ll n) {
    ll s = sum_n(n);
    return s * s;
}

namespace CPUtils {
struct SegmentTree {
    int n;
    vector<ll> tree;

    SegmentTree(int _n) : n(_n), tree(4 * _n, 0) {}

    void build(const vector<ll> &a, int v = 1, int tl = 0, int tr = -1) {
        if (tr == -1) tr = n - 1;
        if (tl == tr) {
            tree[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2, tl, tm);
            build(a, v * 2 + 1, tm + 1, tr);
            tree[v] = tree[v * 2] + tree[v * 2 + 1];
        }
    }

    void update(int pos, ll val, int v = 1, int tl = 0, int tr = -1) {
        if (tr == -1) tr = n - 1;
        if (tl == tr) {
            tree[v] = val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(pos, val, v * 2, tl, tm);
            else
                update(pos, val, v * 2 + 1, tm + 1, tr);
            tree[v] = tree[v * 2] + tree[v * 2 + 1];
        }
    }

    ll query(int l, int r, int v = 1, int tl = 0, int tr = -1) {
        if (tr == -1) tr = n - 1;
        if (l > r) return 0;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        return query(l, min(r, tm), v * 2, tl, tm) +
               query(max(l, tm + 1), r, v * 2 + 1, tm + 1, tr);
    }

    ~SegmentTree() = default;
};
struct FenwickTree {
    int n;
    vector<ll> bit;

    FenwickTree(int _n) : n(_n + 1), bit(n, 0) {}

    void add(int index, ll delta) {
        for (; index < n; index += index & -index) bit[index] += delta;
    }

    ll sum(int index) const {
        ll res = 0;
        for (; index > 0; index -= index & -index) res += bit[index];
        return res;
    }

    ll range_sum(int l, int r) const { return sum(r) - sum(l - 1); }

    void clear() { fill(bit.begin(), bit.end(), 0); }

    ~FenwickTree() = default;
};
struct DSU {
    vector<int> parent, rank;

    DSU(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);  // self-parented
    }

    int find(int x) {
        if (x != parent[x]) parent[x] = find(parent[x]);  // path compression
        return parent[x];
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }

    ~DSU() = default;
};
}  // namespace CPUtils

void solve() {
    int n;
    cin >> n;
    vi a(n);
    READVEC(a);

    vi pre_min(n), suf_max(n);
    pre_min[0] = a[0];
    FOR(i, 1, n) { pre_min[i] = min(a[i], pre_min[i - 1]); }
    suf_max[n - 1] = a[n - 1];
    FORD(i, n - 2, 0) { suf_max[i] = max(a[i], suf_max[i + 1]); }

    string res = "";
    FOR(i, 0, n) {
        if (a[i] == pre_min[i] or a[i] == suf_max[i]) {
            res += '1';
        } else {
            res += '0';
        }
    }
    print(res);
}

int main() {
    fastio();
#ifdef LOCALCLK
    clock_t start = clock();
#endif

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

#ifdef LOCALCLK
    cerr << "\n[Execution Time]: " << fixed << setprecision(3)
         << 1000.0 * (clock() - start) / CLOCKS_PER_SEC << " ms\n";
#endif
    return 0;
}