#include <bits/stdc++.h>
using namespace std;

// TIme & Space - O(n)
int power(int a, int n)
{
    if (n == 0)
        return 1;
    return a * power(a, n - 1);
}

// Time & Space - O(log n)
int fastPower(int a, int n)
{
    if (n == 0)
        return 1;

    int subProb = fastPower(a, n / 2);
    int subProbSq = subProb * subProb;

    // if n is odd = a * (a^(n/2))^2
    // else (a^(n/2))^2
    if (n & 1)
        return a * subProbSq;
    return subProbSq;
}

int main()
{
    int a = 2, n = 3;
    cout << power(a, n) << endl;
    cout << fastPower(a, n) << endl;
    return 0;
}