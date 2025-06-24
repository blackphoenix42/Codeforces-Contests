/*
Run length encoding for string compression
If compressed string is biggeer than original return original string

Input: aaabbccddee
Output: a3b2c2d2e2

Input: abcd
Output: abcd
*/

#include <bits/stdc++.h>
using namespace std;

string compressString(string str)
{
    int n = str.length();

    string output;
    for (int i = 0; i < n; i++)
    {
        int count = 1;
        while (i < n - 1 and str[i + 1] == str[i])
        {
            count++;
            i++;
        }
        output += str[i];
        output += to_string(count);
    }

    if (output.length() > n)
        return str;
    return output;
}

int main()
{
    string s1 = "aaabbccddee";
    cout << compressString(s1) << endl;

    string s2 = "abcd";
    cout << compressString(s2) << endl;

    return 0;
}