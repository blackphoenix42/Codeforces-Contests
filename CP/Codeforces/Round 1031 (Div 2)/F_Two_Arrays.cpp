#include <bits/stdc++.h>
using namespace std;

const int MAX = 200005;

void solve()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        vector<int> a(n), b(n);
        for (int &x : a)
            cin >> x;
        for (int &x : b)
            cin >> x;

        int max_val = 2 * n + 1;

        vector<int> freqA(max_val, 0), freqB(max_val, 0);

        for (int i = 0; i < n; ++i)
        {
            freqA[a[i]]++;
            freqB[b[i]]++;
        }

        for (int i = 0; i < n; ++i)
        {
            int ai = a[i], bi = b[i];

            if ((freqA[ai] > 1 && freqB[bi] > 0 && freqA[bi] == 0) ||
                (freqB[bi] > 1 && freqA[ai] > 0 && freqB[ai] == 0) ||
                (freqA[ai] + freqB[ai] > 1 && freqA[bi] + freqB[bi] == 0))
            {

                swap(a[i], b[i]);

                freqA[a[i]]++;
                freqA[ai]--;
                freqB[b[i]]++;
                freqB[bi]--;
            }
        }

        bitset<MAX> seenA, seenB;
        int distinctA = 0, distinctB = 0;

        for (int x : a)
        {
            if (!seenA[x])
            {
                seenA[x] = 1;
                ++distinctA;
            }
        }

        for (int x : b)
        {
            if (!seenB[x])
            {
                seenB[x] = 1;
                ++distinctB;
            }
        }

        cout << distinctA + distinctB << '\n';
        for (int x : a)
            cout << x << ' ';
        cout << '\n';
        for (int x : b)
            cout << x << ' ';
        cout << '\n';
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
