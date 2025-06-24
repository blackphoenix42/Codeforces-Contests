/*
Read N Strings and print the largest string. Each string have upto 1000 characters.
*/

#include <bits/stdc++.h>
using namespace std;

void solution(char arr[])
{
}

int main()
{
    int n;
    cin >> n;

    cin.get();

    char sentence[1000];
    char largest[1000];

    int largest_len = 0;

    while (n--)
    {
        cin.getline(sentence, 1000);
        int len = strlen(sentence);

        if (len > largest_len)
        {
            strcpy(largest, sentence);
            largest_len = len;
        }
    }
    cout << largest;

    return 0;
}