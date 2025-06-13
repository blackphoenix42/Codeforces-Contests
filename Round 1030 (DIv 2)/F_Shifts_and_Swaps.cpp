#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<int> a(n), b(n);
        for (int &x : a)
            cin >> x;
        for (int &x : b)
            cin >> x;

        // For m >= 3, arbitrary reorder is possible
        if (m >= 3)
        {
            cout << "YES\n";
            continue;
        }

        // m == 2 case:
        // Check for duplicate
        bool has_duplicate = false;
        vector<int> cnt(m + 1, 0);
        for (int x : a)
        {
            cnt[x]++;
            if (cnt[x] >= 2)
                has_duplicate = true;
        }

        if (n > m && has_duplicate)
        {
            cout << "YES\n";
            continue;
        }

        // Otherwise check for rotation
        bool possible = false;
        for (int shift = 0; shift < n; ++shift)
        {
            bool match = true;
            for (int i = 0; i < n; ++i)
            {
                if (a[(i + shift) % n] != b[i])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                possible = true;
                break;
            }
        }

        cout << (possible ? "YES\n" : "NO\n");
    }

    return 0;
}
