#include <bits/stdc++.h>
using namespace std;

int convertToBinary(int n)
{
    int ans = 0;
    int p = 1;
    while (n > 0)
    {
        int last_bit = n & 1;
        ans += p * last_bit;
        p = p * 10;
        n = n >> 1;
    }
    return ans;
}

int main()
{
    int n = 10;
    cout << convertToBinary(n);
    return 0;
}