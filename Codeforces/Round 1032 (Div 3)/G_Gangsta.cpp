#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class FenwickTree
{
    int length;
    vector<ll> data;

public:
    FenwickTree(int size) : length(size), data(size + 1, 0) {}

    void add(int pos, ll val)
    {
        for (; pos <= length; pos += pos & -pos)
            data[pos] += val;
    }

    ll prefixSum(int pos) const
    {
        ll result = 0;
        for (; pos > 0; pos -= pos & -pos)
            result += data[pos];
        return result;
    }

    ll rangeSum(int left, int right) const
    {
        if (left > right)
            return 0;
        return prefixSum(right) - prefixSum(left - 1);
    }
};

vector<int> compressPrefix(const vector<int> &prefixArr)
{
    vector<int> sorted = prefixArr;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    return sorted;
}

int getCompressedIdx(const vector<int> &compressed, int value)
{
    return int(lower_bound(compressed.begin(), compressed.end(), value) - compressed.begin()) + 1;
}

ll solve(int n, const string &binaryStr)
{
    vector<int> prefixBalance(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        prefixBalance[i] = prefixBalance[i - 1] + (binaryStr[i - 1] == '1' ? 1 : -1);
    }

    vector<int> compressed = compressPrefix(prefixBalance);
    int compSize = compressed.size();

    FenwickTree fenwick(compSize);
    fenwick.add(getCompressedIdx(compressed, prefixBalance[0]), 1);

    ll contrib = 0;
    for (int i = 2; i <= n; i++)
    {
        int prevPrefix = prefixBalance[i - 1];
        int idx = getCompressedIdx(compressed, prevPrefix);
        ll count;
        ll weight = (ll)(n - i + 1);

        if (binaryStr[i - 1] == '1')
        {
            count = fenwick.prefixSum(idx);
        }
        else
        {
            ll total = fenwick.prefixSum(compSize);
            count = total - fenwick.prefixSum(idx - 1);
        }
        contrib += count * weight;
        fenwick.add(idx, 1);
    }

    ll totalSubstr = (ll)n * (n + 1) / 2;
    return totalSubstr + contrib;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        int len;
        string str;
        cin >> len >> str;
        cout << solve(len, str) << "\n";
    }
    return 0;
}
