#include <bits/stdc++.h>
using namespace std;

long long shashlik(long long k, long long a, long long b, long long x, long long y)
{
    long long res = 0;
    if (k >= a)
    {
        long long shash = (k - a) / x + 1;
        k -= shash * x;
        res += shash;
    }
    if (k >= b)
    {
        long long shash = (k - b) / y + 1;
        res += shash;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        long long k, a, b, x, y;
        cin >> k >> a >> b >> x >> y;
        long long res1 = shashlik(k, a, b, x, y);
        long long res2 = shashlik(k, b, a, y, x);
        cout << max(res1, res2) << endl;
    }
    return 0;
}