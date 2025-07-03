#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Function to count number of 1's in binary
int beauty(int x)
{
    return __builtin_popcount(x);
}

// Function to get cost to next beauty increase
long long next_cost(int x)
{
    int lowest_zero_bit = 0;
    while ((x >> lowest_zero_bit) & 1)
    {
        lowest_zero_bit++;
    }
    return 1LL << lowest_zero_bit;
}

int main()
{
    // Hardcoded sample input
    int t = 5;
    vector<int> ns = {5, 5, 1, 3, 1};
    vector<long long> ks = {2, 3, 1, 0, 100000000000};
    vector<vector<int>> arrays = {
        {0, 1, 7, 2, 4},
        {0, 1, 7, 2, 4},
        {3},
        {2, 0, 3},
        {0}};

    for (int test = 0; test < t; ++test)
    {
        int n = ns[test];
        long long k = ks[test];
        vector<int> a = arrays[test];

        long long beauty_sum = 0;

        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

        // Initial beauty sum and first gains
        for (int i = 0; i < n; ++i)
        {
            beauty_sum += beauty(a[i]);
            long long cost = next_cost(a[i]);
            pq.push({cost, i});
        }

        // Process operations
        while (!pq.empty() && k > 0)
        {
            auto [cost, idx] = pq.top();
            pq.pop();

            if (k >= cost)
            {
                k -= cost;
                a[idx] += cost;
                beauty_sum += 1;

                // Push next gain for this number
                long long next = next_cost(a[idx]);
                pq.push({next, idx});
            }
            else
            {
                break;
            }
        }

        // Output the result for this test case
        cout << beauty_sum << '\n';
    }

    return 0;
}
