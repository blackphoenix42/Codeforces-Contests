// WAF to count set bits in a number i.e. all the 1s.

#include <bits/stdc++.h>
using namespace std;

// Run for atmost O(log n)
int countSetBits(int n)
{
    int count = 0;
    while (n > 0)
    {
        int last_bit = n & 1;
        count += last_bit;
        n = n >> 1;
    }
    return count;
}

// Faster Method
int count_bits_hack(int n)
{
    int ans = 0;
    while (n > 0)
    {
        // Removes the last set bit in the number i.e. only 1s will be removed in every iteration
        n = n & (n - 1);
        ans++;
    }
    return ans;
}

int main()
{
    int n = 15;
    cout << countSetBits(n) << endl;
    cout << count_bits_hack(n);
    return 0;
}