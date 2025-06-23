/**
 *    Name:    Ayush Yadav
 *    author:  blackphoenix42
 *    created: 2025-06-23 20:14:17
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
#define FORD(a, b, c) for (int a = (b); (a) >= (c); --(a))
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

// For TESTING
inline void OPEN(string s)
{
#ifndef TESTING
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
void _print(const pair<T, V> &p)
{
    cerr << "{";
    _print(p.fi);
    cerr << ", ";
    _print(p.se);
    cerr << "}";
}
template <typename T>
void _print(const vector<T> &v)
{
    cerr << "[ ";
    for (const auto &i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <typename T>
void _print_with_index(const vector<T> &v)
{
    cerr << "[\n";
    for (size_t i = 0; i < v.size(); ++i)
    {
        cerr << "  [" << i << "]: ";
        _print(v[i]);
        cerr << '\n';
    }
    cerr << "]";
}
template <typename T>
void _print(const vector<vector<T>> &v)
{
    cerr << "[\n";
    for (const auto &row : v)
    {
        cerr << "  ";
        _print(row);
        cerr << "\n";
    }
    cerr << "]";
}
template <typename T>
void _print(const set<T> &s)
{
    cerr << "{ ";
    for (const auto &i : s)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "}";
}
template <typename T>
void _print(const unordered_set<T> &s)
{
    cerr << "{ ";
    for (const auto &i : s)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "}";
}
template <typename T>
void _print(const multiset<T> &s)
{
    cerr << "{ ";
    for (const auto &i : s)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "}";
}
template <typename K, typename V>
void _print(const map<K, V> &m)
{
    cerr << "{ ";
    for (const auto &p : m)
    {
        cerr << "[";
        _print(p.first);
        cerr << ": ";
        _print(p.second);
        cerr << "] ";
    }
    cerr << "}";
}
template <typename K, typename V>
void _print(const unordered_map<K, V> &m)
{
    cerr << "{ ";
    for (const auto &p : m)
    {
        cerr << "[";
        _print(p.first);
        cerr << ": ";
        _print(p.second);
        cerr << "] ";
    }
    cerr << "}";
}
template <typename T>
void _print(const deque<T> &d)
{
    cerr << "[ ";
    for (const auto &i : d)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <typename T>
void _print(queue<T> q)
{
    cerr << "[ ";
    while (!q.empty())
    {
        _print(q.front());
        cerr << " ";
        q.pop();
    }
    cerr << "]";
}
template <typename T>
void _print(priority_queue<T> pq)
{
    vector<T> temp;
    while (!pq.empty())
    {
        temp.push_back(pq.top());
        pq.pop();
    }
    _print(temp);
}
template <typename T>
void _print(stack<T> s)
{
    vector<T> temp;
    while (!s.empty())
    {
        temp.push_back(s.top());
        s.pop();
    }
    reverse(temp.begin(), temp.end());
    _print(temp);
}
// Other types
template <typename T1, typename T2, typename T3>
void _print(const tuple<T1, T2, T3> &t)
{
    cerr << "(";
    _print(get<0>(t));
    cerr << ", ";
    _print(get<1>(t));
    cerr << ", ";
    _print(get<2>(t));
    cerr << ")";
}
template <size_t N>
void _print(const bitset<N> &b)
{
    cerr << b.to_string();
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T)
{
    _print(H);
    if (sizeof...(T))
        cerr << ", ";
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
const ll INF = 1e9;
const int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const int dirx[8] = {-1, 0, 0, 1, -1, -1, 1, 1};
const int diry[8] = {0, 1, -1, 0, -1, 1, -1, 1};
#define in_bounds(x, y, n, m) (x >= 0 && x < n && y >= 0 && y < m)

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
namespace CPUtils
{
    struct SegmentTree
    {
        int n;
        vector<ll> tree;

        SegmentTree(int _n) : n(_n), tree(4 * _n, 0) {}

        void build(const vector<ll> &a, int v = 1, int tl = 0, int tr = -1)
        {
            if (tr == -1)
                tr = n - 1;
            if (tl == tr)
            {
                tree[v] = a[tl];
            }
            else
            {
                int tm = (tl + tr) / 2;
                build(a, v * 2, tl, tm);
                build(a, v * 2 + 1, tm + 1, tr);
                tree[v] = tree[v * 2] + tree[v * 2 + 1];
            }
        }

        void update(int pos, ll val, int v = 1, int tl = 0, int tr = -1)
        {
            if (tr == -1)
                tr = n - 1;
            if (tl == tr)
            {
                tree[v] = val;
            }
            else
            {
                int tm = (tl + tr) / 2;
                if (pos <= tm)
                    update(pos, val, v * 2, tl, tm);
                else
                    update(pos, val, v * 2 + 1, tm + 1, tr);
                tree[v] = tree[v * 2] + tree[v * 2 + 1];
            }
        }

        ll query(int l, int r, int v = 1, int tl = 0, int tr = -1)
        {
            if (tr == -1)
                tr = n - 1;
            if (l > r)
                return 0;
            if (l == tl && r == tr)
                return tree[v];
            int tm = (tl + tr) / 2;
            return query(l, min(r, tm), v * 2, tl, tm) +
                   query(max(l, tm + 1), r, v * 2 + 1, tm + 1, tr);
        }

        ~SegmentTree() = default;
    };
    struct FenwickTree
    {
        int n;
        vector<ll> bit;

        FenwickTree(int _n) : n(_n + 1), bit(n, 0) {}

        void add(int index, ll delta)
        {
            for (; index < n; index += index & -index)
                bit[index] += delta;
        }

        ll sum(int index) const
        {
            ll res = 0;
            for (; index > 0; index -= index & -index)
                res += bit[index];
            return res;
        }

        ll range_sum(int l, int r) const
        {
            return sum(r) - sum(l - 1);
        }

        void clear() { fill(bit.begin(), bit.end(), 0); }

        ~FenwickTree() = default;
    };
    struct DSU
    {
        vector<int> parent, rank;

        DSU(int n) : parent(n), rank(n, 0)
        {
            iota(parent.begin(), parent.end(), 0); // self-parented
        }

        int find(int x)
        {
            if (x != parent[x])
                parent[x] = find(parent[x]); // path compression
            return parent[x];
        }

        bool unite(int x, int y)
        {
            x = find(x);
            y = find(y);
            if (x == y)
                return false;
            if (rank[x] < rank[y])
                swap(x, y);
            parent[y] = x;
            if (rank[x] == rank[y])
                rank[x]++;
            return true;
        }

        ~DSU() = default;
    };
}

void solve()
{
    int len;
    cin >> len;
    vi a(len);
    READVEC(a);

    if (len < 2)
    {
        print(-1);
        return;
    }

    bool nice = false;
    FOR(i, 0, len - 1)
    {
        if (abs(a[i] - a[i + 1]) <= 1)
        {
            nice = true;
            break;
        }
    }

    if (nice)
    {
        print(0);
        return;
    }

    int ans = INF;
    FOR(mid, 0, len - 1)
    {
        vi minR(len, INF), maxR(len, -INF);
        if (mid + 1 < len)
        {
            minR[mid + 1] = a[mid + 1];
            maxR[mid + 1] = a[mid + 1];
            FOR(i, mid + 2, len)
            {
                minR[i] = min(minR[i - 1], a[i]);
                maxR[i] = max(maxR[i - 1], a[i]);
            }
        }

        int lmin = a[mid], lmax = a[mid];
        int p1 = len - 1, p2 = len - 1;

        FORD(i, mid, 0)
        {
            lmin = min(lmin, a[i]);
            lmax = max(lmax, a[i]);

            while (p1 > mid + 1 && maxR[p1 - 1] >= lmin - 1)
                --p1;
            while (p2 > mid + 1 && minR[p2 - 1] <= lmax + 1)
                --p2;

            int c1 = (p1 >= mid + 1 && maxR[p1] >= lmin - 1) ? p1 : len;
            int c2 = (p2 >= mid + 1 && minR[p2] <= lmax + 1) ? p2 : len;
            int right = max(c1, c2);

            if (right < len)
            {
                ans = min(ans, (mid - i) + (right - (mid + 1)));
            }
        }
    }

    print(ans == INF ? -1 : ans);
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
