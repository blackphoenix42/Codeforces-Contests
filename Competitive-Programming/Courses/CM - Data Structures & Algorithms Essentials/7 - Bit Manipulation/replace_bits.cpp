/*
Replace Bits in N by M

You are given two 32 bit numbers N and M, and two bit positions i and j
Write a method to set all bits between i and j in N equal to M.
M (becomes a substring of N locationed at and starting at j)

Example:
N = 10000000000;
M = 10101;
i = 2, j = 6
Output : 1001010100

*/

#include <bits/stdc++.h>
using namespace std;

int clearBitsInRange(int n, int i, int j)
{
    int a = -1 << (j + 1);
    int b = (1 << i) - 1;
    int mask = a | b;
    return n & mask;
}

int replaceBits(int n, int m, int i, int j)
{
    n = clearBitsInRange(n, i, j);
    int mask = m << i;
    return n | mask;
}

int main()
{
    int n = 15;
    int m = 2;
    int i = 1;
    int j = 3;

    cout << replaceBits(n, m, i, j);
    return 0;
}