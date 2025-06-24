#include <bits/stdc++.h>
using namespace std;

bool checkPowerOf2(int n)
{
    // n & (n-1) == 0 then power of 2
    if ((n & (n - 1)) == 0)
        return true;
    return false;
}

int main()
{
    int n = 16;
    cout << checkPowerOf2(n);
    return 0;
}