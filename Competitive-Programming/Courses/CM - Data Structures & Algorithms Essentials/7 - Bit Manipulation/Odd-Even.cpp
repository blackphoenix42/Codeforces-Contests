// WAF to check if a number is odd or even using bitwise operators

#include <bits/stdc++.h>
using namespace std;

string checkOddEven(int n)
{
    if (n & 1)
        return "Odd";
    else
        return "Even";
}

int main()
{
    int n;
    cin >> n;
    cout << checkOddEven(n);
    return 0;
}