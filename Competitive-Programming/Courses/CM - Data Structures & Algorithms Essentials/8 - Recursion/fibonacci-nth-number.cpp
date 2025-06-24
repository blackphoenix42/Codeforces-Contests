#include <bits/stdc++.h>
using namespace std;

// Time =  O(2 ^ N)  Space = O(N)
int fib(int n)
{
    if (n == 0 or n == 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

int main()
{
    int n = 7;
    cout << fib(n);
    return 0;
}