#include <bits/stdc++.h>
using namespace std;

void revereString(string str)
{
    int i = 0, j = str.length() - 1;

    while (i < j)
    {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
    cout << str;
}

int main()
{
    string str;
    getline(cin, str);
    revereString(str);
    return 0;
}