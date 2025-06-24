#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cout << t << '\n';
    while (t--)
    {
        int n = rand() % 10 + 1;
        cout << n << '\n';
        for (int i = 0; i < n; ++i)
            cout << rand() % 100 << " ";
        cout << '\n';
    }
    return 0;
}
