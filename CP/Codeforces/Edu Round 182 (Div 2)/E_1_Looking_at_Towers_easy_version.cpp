#include <bits/stdc++.h>
using namespace std;

static const int MOD = 998244353;

struct BIT {
    int n;
    vector<int> f;
    BIT() {}
    BIT(int n_) { init(n_); }
    void init(int n_) {
        n = n_;
        f.assign(n + 1, 0);
    }
    void add(int i, int v) {  // 1..n
        for (; i <= n; i += i & -i) f[i] += v;
    }
    int sum(int i) const {  // 1..i
        int s = 0;
        for (; i > 0; i -= i & -i) s += f[i];
        return s;
    }
    int pref(int k) const {  // # in first k positions (0..k-1)
        return sum(k);
    }
};

inline int addmod(int a, int b) {
    int s = a + b;
    if (s >= MOD) s -= MOD;
    return s;
}
inline int submod(int a, int b) {
    int s = a - b;
    if (s < 0) s += MOD;
    return s;
}
inline int mulmod(long long a, long long b) { return int((a * b) % MOD); }
int modpow(long long a, long long e = MOD - 2) {
    long long r = 1;
    while (e) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return int(r);
}

// Core DP for one side (prefix-style):
// H: values of all a[i] < M in order of appearance (size S)
// rec: strictly increasing record heights to realize (may be empty)
// Returns W of size S+1: W[t] = #ways using first t items of H to realize exactly 'rec'
static vector<int> solve_prefix_dp(const vector<long long>& H,
                                   const vector<long long>& rec,
                                   const vector<int>& pow2,
                                   const vector<int>& inv2pow) {
    int S = (int)H.size();
    int K = (int)rec.size();
    vector<int> W(S + 1, 0);
    if (K == 0) {
        // empty record set: any subset works
        for (int t = 0; t <= S; ++t) W[t] = 1;
        return W;
    }

    // positions of each layer value
    unordered_map<long long, int> idxOf;
    idxOf.reserve(K * 2);
    for (int i = 0; i < K; ++i) idxOf[rec[i]] = i + 1;  // layers 1..K

    vector<vector<int>> pos(K + 1);
    pos.reserve(K + 1);
    for (int i = 0; i < S; ++i) {
        auto it = idxOf.find(H[i]);
        if (it != idxOf.end()) pos[it->second].push_back(i);
    }

    // sort (value, index) to activate eligibility by threshold
    vector<pair<long long, int>> byVal(S);
    for (int i = 0; i < S; ++i) byVal[i] = {H[i], i};
    sort(byVal.begin(), byVal.end());

    BIT bit(S);
    int act = 0;  // pointer in byVal

    // f[i] only meaningful at indices that belong to the current layer
    vector<int> f(S, 0);

    // layer 1: choose first record positions; weight = 1 (normalization handled later)
    for (int id : pos[1]) f[id] = 1;

    // layers 2..K
    for (int j = 2; j <= K; ++j) {
        long long thr = rec[j - 2];  // previous record value

        // activate eligibility (<= thr)
        while (act < S && byVal[act].first <= thr) {
            bit.add(byVal[act].second + 1, 1);
            ++act;
        }

        const auto& prevL = pos[j - 1];
        const auto& currL = pos[j];

        // weights for prev (divide by 2^{eligible up to and including prev})
        vector<int> w(prevL.size());
        for (size_t p = 0; p < prevL.size(); ++p) {
            int idx = prevL[p];
            int elig_incl = bit.pref(idx + 1);
            w[p] = mulmod(f[idx], inv2pow[elig_incl]);
        }

        // prefix sums over prev positions
        vector<int> prefW(prevL.size() + 1, 0);
        for (size_t p = 0; p < prevL.size(); ++p)
            prefW[p + 1] = addmod(prefW[p], w[p]);

        // two-pointer: for each current idx, sum weights of prev with index < idx
        size_t pptr = 0;
        for (int idx : currL) {
            while (pptr < prevL.size() && prevL[pptr] < idx) ++pptr;
            int elig_before = bit.pref(idx);  // strictly before idx
            int sumw = prefW[pptr];
            f[idx] = mulmod(sumw, pow2[elig_before]);
        }
    }

    // Final combine to boundaries t: multiply by 2^{eligible (<= rec[K-1]) before t}
    // using only last-layer positions, dividing by eligible up to and including their pos.
    long long lastVal = rec[K - 1];
    vector<int> isOk(S, 0), prefOk(S + 1, 0);
    for (int i = 0; i < S; ++i) isOk[i] = (H[i] <= lastVal);
    for (int i = 0; i < S; ++i) prefOk[i + 1] = prefOk[i] + isOk[i];

    const auto& lastPos = pos[K];
    vector<int> contrib(lastPos.size());
    for (size_t i = 0; i < lastPos.size(); ++i) {
        int p = lastPos[i];
        int elig_incl = prefOk[p + 1];
        contrib[i] = mulmod(f[p], inv2pow[elig_incl]);
    }

    int run = 0;
    size_t lp = 0;
    for (int t = 0; t <= S; ++t) {
        while (lp < lastPos.size() && lastPos[lp] < t) {
            run = addmod(run, contrib[lp]);
            ++lp;
        }
        W[t] = mulmod(run, pow2[prefOk[t]]);
    }
    return W;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    // precompute pow2 up to max n (sum n <= 3e5)
    const int MAXN = 300000 + 5;
    vector<int> pow2(MAXN), inv2pow(MAXN);
    pow2[0] = 1;
    for (int i = 1; i < MAXN; ++i) pow2[i] = addmod(pow2[i - 1], pow2[i - 1]);
    int inv2 = modpow(2);
    inv2pow[0] = 1;
    for (int i = 1; i < MAXN; ++i) inv2pow[i] = mulmod(inv2pow[i - 1], inv2);

    while (T--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        // left record heights (increasing)
        vector<long long> Lrec;
        {
            long long mx = LLONG_MIN;
            for (int i = 0; i < n; ++i) {
                if (a[i] > mx) {
                    mx = a[i];
                    Lrec.push_back(mx);
                }
            }
        }
        // right record heights (as seen from right; increasing)
        vector<long long> Rrec;
        {
            long long mx = LLONG_MIN;
            for (int i = n - 1; i >= 0; --i) {
                if (a[i] > mx) {
                    mx = a[i];
                    Rrec.push_back(mx);
                }
            }
            reverse(Rrec.begin(),
                    Rrec.end());  // now increasing along the array
        }

        long long M = Lrec.back();

        // positions of M
        vector<int> posM;
        for (int i = 0; i < n; ++i)
            if (a[i] == M) posM.push_back(i);
        int q = (int)posM.size();

        // indices of values < M (in order) and their values
        vector<int> idxLT;
        vector<long long> H;
        idxLT.reserve(n);
        H.reserve(n);
        for (int i = 0; i < n; ++i)
            if (a[i] < M) {
                idxLT.push_back(i);
                H.push_back(a[i]);
            }
        int S = (int)H.size();

        // L' = L \ {M}
        vector<long long> Lprime(Lrec.begin(), Lrec.end() - 1);
        // R' = R \ {M} (Rrec is increasing already)
        vector<long long> Rprime(Rrec.begin(), Rrec.end() - 1);

        // prefix DP on H with L'
        vector<int> Wleft = solve_prefix_dp(H, Lprime, pow2, inv2pow);

        // for right side, reverse the <M sequence and use R'
        vector<long long> Hrev(H.rbegin(), H.rend());
        vector<int> Wright = solve_prefix_dp(Hrev, Rprime, pow2, inv2pow);

        // map boundaries to ways
        vector<int> Lways(q), Rways(q);

        for (int t = 0; t < q; ++t) {
            int i = posM[t];
            int cntBefore =
                int(lower_bound(idxLT.begin(), idxLT.end(), i) - idxLT.begin());
            Lways[t] = Wleft[cntBefore];
        }
        for (int t = 0; t < q; ++t) {
            int j = posM[t];
            int firstAfter =
                int(upper_bound(idxLT.begin(), idxLT.end(), j) - idxLT.begin());
            int lenSuffix = S - firstAfter;  // how many <M elements after j
            Rways[t] = Wright[lenSuffix];
        }

        // sum over pairs (alpha <= beta):
        // diag: alpha==beta
        int diag = 0;
        for (int i = 0; i < q; ++i)
            diag = addmod(diag, mulmod(Lways[i], Rways[i]));

        // off-diagonal using prefix trick:
        // sum_{a<b} L[a] * 2^{pos[b]-pos[a]-1} * R[b]
        // = (1/2) * sum_b R[b]*2^{pos[b]} * (sum_{a<b} L[a]*2^{-pos[a]})
        int off = 0, pref = 0;
        for (int b = 0; b < q; ++b) {
            int term = mulmod(Rways[b], pow2[posM[b]]);
            off = addmod(off, mulmod(term, pref));
            int addS = mulmod(Lways[b], inv2pow[posM[b]]);
            pref = addmod(pref, addS);
        }
        off = mulmod(off, inv2);

        int ans = addmod(diag, off);
        cout << ans << '\n';
    }
    return 0;
}
