#include <bits/stdc++.h>
using namespace std;

pair<int, string> readTestCase()
{
    int len;
    string str;
    cin >> len >> str;
    return {len, str};
}

bool hasMiddleRepeatingChar(int len, const string &str)
{
    vector<int> charCount(26, 0);
    for (char ch : str)
    {
        charCount[ch - 'a']++;
    }

    for (int i = 1; i <= len - 2; ++i)
    {
        if (charCount[str[i] - 'a'] >= 2)
        {
            return true;
        }
    }

    return false;
}

void solve()
{
    int t;
    cin >> t;
    while (t--)
    {
        auto [length, inputStr] = readTestCase();
        bool result = hasMiddleRepeatingChar(length, inputStr);
        cout << (result ? "Yes\n" : "No\n");
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
