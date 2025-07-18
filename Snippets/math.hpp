#pragma once
#include "utils.hpp"

namespace CPUtils::math {
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
const ll INFINT = 1e9;
const int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const int dirx[8] = {-1, 0, 0, 1, -1, -1, 1, 1};
const int diry[8] = {0, 1, -1, 0, -1, 1, -1, 1};
#define in_bounds(x, y, n, m) (x >= 0 && x < n && y >= 0 && y < m)

const int MAXN = 2e5 + 5;
#ifndef ONLINE_JUDGE
ll fact[MAXN], inv_fact[MAXN];
#else
static ll fact[MAXN], inv_fact[MAXN];
#endif

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
// Modular Inverse using Extended Euclidean (when MOD not prime)
ll mod_inv_general(ll a, ll m) {
    ll x, y;
    ll g = extended_gcd(a, m, x, y);
    if (g != 1) return -1;  // Inverse doesn't exist
    return (x % m + m) % m;
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

bool is_power_of_two(ll x) { return x && !(x & (x - 1)); }
int digit_sum(ll x) {
    int sum = 0;
    while (x) sum += (int)x % 10, x /= 10;
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
    int n = sz(grid), m = sz(grid[0]);
    vvi ps(n + 1, vi(m + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            ps[i][j] = grid[i - 1][j - 1] + ps[i - 1][j] + ps[i][j - 1] -
                       ps[i - 1][j - 1];
    return ps;
}

ll ceil_div(ll a, ll b) { return (a + b - 1) / b; }
int floor_lg(long long x) { return x <= 0 ? -1 : 63 - __builtin_clzll(x); }
ll floor_sqrt(ll x) { return (ll)sqrtl(x); }
ll ceil_sqrt(ll x) {
    ll r = (ll)ceil(sqrtl(x));
    while (r * r > x) --r;
    while ((r + 1) * (r + 1) <= x) ++r;
    return r;
}
template <class T1, class T2>
T1 floor_div(T1 num, T2 den) {
    return (num > 0 ? num / den : -((-num + den - 1) / den));
}

// Check primality (trial division up to sqrt(n))
bool is_prime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}
vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i])
            for (int j = i * i; j <= n; j += i) is_prime[j] = false;
    }
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

// Sum of first N natural numbers
ll sum_n(ll n) { return n * (n + 1) / 2; }
// Sum of squares 1^2 + 2^2 + ... + n^2
ll sum_n2(ll n) { return n * (n + 1) * (2 * n + 1) / 6; }
// Sum of cubes: (1 + 2 + ... + n)^2
ll sum_n3(ll n) {
    ll s = sum_n(n);
    return s * s;
}

//  Description: Permutation -> integer conversion. (Not order preserving.).
//  Integer -> permutation can use a lookup table.
int permToInt(vi &v) {
    int use = 0, i = 0, r = 0;
    for (int x : v)
        r = r * ++i + __builtin_popcount(use & -(1 << x)),
        use |= 1 << x;  // (note: minus, not ~!)
    return r;
}

// Description: Computes $\displaystyle \binom{k_1 + \dots + k_n}{k_1, k_2,
// \dots, k_n} = \frac{(\sum k_i)!}{k_1!k_2!...k_n!}$.
ll multinomial(vi &v) {
    ll c = 1, m = v.empty() ? 1 : v[0];
    rep(i, 1, sz(v)) rep(j, 0, v[i]) c = c * ++m / (j + 1);
    return c;
}

}  // namespace CPUtils::math