#pragma once
#include <bits/stdc++.h>
using namespace std;

#define fastio()                 \
    ios::sync_with_stdio(false); \
    cin.exceptions(cin.failbit); \
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
using vc = vector<char>;
using vvc = vector<vector<char>>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vll = vector<vl>;
using vi = vector<int>;
using vvi = vector<vi>;
using vpii = vector<pii>;
using vpll = vector<pll>;
using qs = queue<string>;
using ql = queue<ll>;
using qi = queue<int>;
using qpii = queue<pii>;
using qpll = queue<pll>;
using sts = stack<string>;
using stl = stack<ll>;
using sti = stack<int>;
using stpii = stack<pii>;
using stpll = stack<pll>;
using i128 = __int128_t;
using u128 = __uint128_t;

// Macros
#define umap1 unordered_map
#define uset1 unordered_set
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
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define CP_MAX(a, b) a = max(a, b)
#define CP_MIN(a, b) a = min(a, b)
#define CP_SQR(x) ((ll)(x) * (x))
#define CP_RESET(a, b) memset(a, b, sizeof(a))
#define nl '\n'
#define el cout << '\n'
#define print(x) cout << (x) << '\n'
#define print1(x) cout << (x) << ' '
#define flush cout << endl << flush
#define freq(v)       \
    map<ll, ll> freq; \
    for (auto x : v) freq[x]++;

#define lb lower_bound
#define ub upper_bound
#define bs binary_search
#define rev reverse
#define rv(vec) \
    for (auto &x : vec) cin >> x;
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
#define rp(a, b) cin >> a >> b
#define write_pair(p) cout << p.first << " " << p.second << '\n'