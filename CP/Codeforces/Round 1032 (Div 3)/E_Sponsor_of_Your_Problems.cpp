#include <bits/stdc++.h>
using namespace std;

const int DIG = 20;
const int INF = 1e9;

int findMinimumCost(const string &lower, const string &upper)
{
    int n = lower.size();
    static int dp[DIG][2][2];

    for (int i = 0; i <= n; i++)
    {
        for (int l = 0; l < 2; l++)
        {
            for (int r = 0; r < 2; r++)
            {
                dp[i][l][r] = INF;
            }
        }
    }

    dp[0][1][1] = 0;

    for (int pos = 0; pos < n; pos++)
    {
        int minDigit = lower[pos] - '0';
        int maxDigit = upper[pos] - '0';

        for (int isLow = 0; isLow < 2; isLow++)
        {
            for (int isUp = 0; isUp < 2; isUp++)
            {
                if (dp[pos][isLow][isUp] == INF)
                    continue;
                int start = isLow ? minDigit : 0;
                int end = isUp ? maxDigit : 9;

                for (int digit = start; digit <= end; digit++)
                {
                    int nextLow = isLow && (digit == minDigit);
                    int nextUp = isUp && (digit == maxDigit);
                    int transitionCost = 0;
                    if (digit == minDigit)
                        transitionCost++;
                    if (digit == maxDigit)
                        transitionCost++;

                    dp[pos + 1][nextLow][nextUp] = min(
                        dp[pos + 1][nextLow][nextUp],
                        dp[pos][isLow][isUp] + transitionCost);
                }
            }
        }
    }

    int minCost = INF;
    for (int isLow = 0; isLow < 2; isLow++)
    {
        for (int isUp = 0; isUp < 2; isUp++)
        {
            minCost = min(minCost, dp[n][isLow][isUp]);
        }
    }
    return minCost;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        string l, r;
        cin >> l >> r;
        cout << findMinimumCost(l, r) << "\n";
    }
    return 0;
}
