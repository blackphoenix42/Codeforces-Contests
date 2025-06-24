#include <bits/stdc++.h>
using namespace std;

string spells[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

void printSpell(int n)
{
    if (n == 0)
        return;

    int m = n % 10;
    printSpell(n / 10);

    cout << spells[m] << " ";
}

int main()
{
    int n = 2022;
    printSpell(n);
    return 0;
}