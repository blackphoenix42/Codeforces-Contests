/*
Write a function that takes in n x m 2D Array, and prints the all array elements in a spiral order. Start from top left corner, goes to right, proceeds in a spiral pattern until every element is visited

Input:
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16

Output:
1 2 3 4 8 12 16 15 14 13 9 5 6 7 11 10

*/

#include <bits/stdc++.h>
using namespace std;

void spiral_print(int arr[][4], int n, int m)
{
    int startRow = 0, endCol = m - 1, endRow = n - 1, startCol = 0;

    while (startRow < endRow)
    {
        for (int col = startCol; col <= endCol; col++)
            cout << arr[startRow][col] << " ";
        startRow++;

        for (int row = startRow; row <= endRow; row++)
            cout << arr[row][endCol] << " ";
        endCol--;

        for (int col = endCol; col >= startCol; col--)
            cout << arr[endRow][col] << " ";
        endRow--;

        for (int row = endRow; row >= startRow; row--)
            cout << arr[row][startCol] << " ";
        startCol++;
    }
}

int main()
{
    // int n, m;
    // cin >> n >> m;
    // int arr[n][m];
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         cin >> arr[i][j];
    //     }
    // }
    // spiral_print(arr, n, m);

    int arr[][4] = {{1, 2, 3, 4},
                    {5, 6, 7, 8},
                    {9, 10, 11, 12},
                    {13, 14, 15, 16}};

    spiral_print(arr, 4, 4);

    return 0;
}