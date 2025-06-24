/*
Find Displacement: Given a long route containing N,S,E,W directions, find the shortest path to reach the location.

Input:
SNNNEWE

Output:
NNE

Solution: When going north increment y, east increment x, south decrement y, west decrement x.
*/

#include <bits/stdc++.h>
using namespace std;

void solution(char arr[])
{
    int n = strlen(arr);
    int x = 0, y = 0;
    
    for (int i = 0; i < n; i++)
    {
        switch (arr[i])
        {
        case 'N':
            y++;
            break;
        case 'S':
            y--;
            break;
        case 'E':
            x++;
            break;
        case 'W':
            x--;
            break;
        }
    }

    if (y >= 0)
    {
        for (int i = 0; i < y; i++)
        {
            cout << "N";
        }
    }
    else
    {
        for (int i = 0; i < (-1 * y); i++)
        {
            cout << "S";
        }
    }

    if (x >= 0)
    {
        for (int i = 0; i < x; i++)
        {
            cout << "E";
        }
    }
    else
    {
        for (int i = 0; i < (-1 * x); i++)
        {
            cout << "W";
        }
    }
}

int main()
{
    char arr[1000];
    cin.getline(arr, 1000);
    solution(arr);

    return 0;
}