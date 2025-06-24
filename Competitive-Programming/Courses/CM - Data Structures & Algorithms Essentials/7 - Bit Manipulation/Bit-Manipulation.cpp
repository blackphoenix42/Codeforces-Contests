#include <bits/stdc++.h>
using namespace std;

int getIthBit(int n, int i)
{
    int mask = 1 << i;
    return (n & mask) > 0 ? 1 : 0;
}

// Change a bit from 1 to 0
int clearIthBit(int n, int i)
{
    int mask = ~(1 << i);
    return n & mask;
}

// Change a bit from 0 to 1
int setIthBit(int n, int i)
{
    int mask = 1 << i;
    return n | mask;
}

// CHnage ith bit according to value passed
int updateIthBit(int n, int i, int v)
{
    n = clearIthBit(n, i);
    int mask = (v << i);
    return n | mask;
}

// Clear ith bits from right or make them 0
int clearLastIBits(int n, int i)
{
    // -1 or ~0
    int mask = -1 << i;
    return n & mask;
}

// Clear bits in range i (right one) to j (left one)
int clearBitsInRange(int n, int i, int j)
{
    int a = -1 << (j + 1);
    int b = (1 << i) - 1;
    int mask = a | b;
    return n & mask;
}

int main()
{
    // Number
    int n = 15;

    // Ith bit from right, starts from 0
    int i = 2;

    // Value to be put in ith bit i.e. 1 or 0
    int v = 1;

    // cout << getIthBit(n, i) << endl;
    // cout << clearIthBit(n, i) << endl;
    // cout << setIthBit(n, i) << endl;
    // cout << updateIthBit(n, i, v) << endl;
    // cout << clearLastIBits(n, i) << endl;
    // cout << clearLastIBits(n, i) << endl;
    cout << clearBitsInRange(31, 1, 3) << endl;

    return 0;
}