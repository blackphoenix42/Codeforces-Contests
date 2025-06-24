/*
Write a function that searches for an element in row wise and column wise sorted 2D array.
EX:
int arr[][4] = { {10, 20, 30, 40},
                 {15, 25, 35, 45},
                 {27, 29, 37, 48},
                 {32, 33, 39, 50}};

Lets search for element 33

1. Brute Force Approach: Go through all elements. O(n*m)
2. Binary Search on Each row/column: As they are sorted
3. we can move from rightmost element and start comparing and move row and column wise like a staircase. As if we move left data decreases and if we move down it increases. but from leftmost it only increases

Traversal: 40 -> 30 -> 35 -> 25 -> 29 -> 33
*/

#include <bits/stdc++.h>
using namespace std;

pair<int, int> stair_case_search(int arr[][4], int n, int m, int key)
{
    int i = 0, j = m - 1;

    while (i < n and j >= 0)
    {
        if (arr[i][j] == key)
            return {i, j};
        else if (key > arr[i][j])
            i++;
        else if (key < arr[i][j])
            j--;
    }
    return {-1, -1};
}

int main()
{
    // int n, m, key;
    // cin >> n >> m >> key;
    // int arr[n][m];
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         cin >> arr[i][j];
    //     }
    // }
    // stair_case_search(arr, n, m, key);

    int arr[][4] = {{10, 20, 30, 40},
                    {15, 25, 35, 45},
                    {27, 29, 37, 48},
                    {32, 33, 39, 50}};

    pair<int, int> coords = stair_case_search(arr, 4, 4, 33);
    cout << coords.first << " " << coords.second;

    return 0;
}