/*
    Print numbers 1...N recursively in
    - decreasing order
    - increasing order
*/

#include <bits/stdc++.h>
using namespace std;

void decreasing(int n)
{
    if (n == 0)
        return;

    cout << n << " ";
    decreasing(n - 1);
}

void increasing(int n)
{
    if (n == 0)
        return;

    increasing(n - 1);
    cout << n << " ";
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(int);
    decreasing(n);
    cout << endl;
    increasing(n);
    return 0;
}