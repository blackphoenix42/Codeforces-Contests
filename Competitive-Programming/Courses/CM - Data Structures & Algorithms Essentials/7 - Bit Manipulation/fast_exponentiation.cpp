#include <bits/stdc++.h>
using namespace std;

// O(logN)
int fast_expo(int a, int n)
{
    int ans = 1;

    while (n > 0)
    {
        int last_bit = n & 1;
        if (last_bit)
            ans = ans * a;

        a = a * a;
        n = n >> 1;
    }
    return ans;
}

int main()
{
    int a = 2;
    int n = 3;
    cout << fast_expo(a, n);
    return 0;
}