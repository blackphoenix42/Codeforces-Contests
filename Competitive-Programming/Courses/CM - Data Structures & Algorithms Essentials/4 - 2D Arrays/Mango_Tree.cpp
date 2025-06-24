/*
Rahul's father has left a farm organized as an N x N grid. Each square in the grid either has or does not have a mango tree. He has to divide the farm with his three sisters as follows:
- He will draw one horizontal and one vertical line to divide the field into four rectangles.
- His friends will choose three of the four smaller fields and he gets the last one.

Check ./info.md for full documentation.
*/

#include <bits/stdc++.h>
using namespace std;

void mango_tree(char arr[][6], int n, int m)
{
    int M[6][6];
    M[0][0] = arr[0][0] == '#' ? 1 : 0;
    for (int j = 1; j < n; j++)
        M[0][j] = (arr[0][j] == '#' ? 1 : 0) + M[0][j - 1];
    for (int i = 1; i < n; i++)
        M[i][0] = (arr[i][0] == '#' ? 1 : 0) + M[i - 1][0];

    for (int x = 1; x < n; x++)
        for (int y = 1; y < m; y++)
            if (arr[x][y] == '#')
                M[x][y] = 1 + M[x - 1][y] + M[x][y - 1] - M[x - 1][y - 1];
            else
                M[x][y] = 0 + M[x - 1][y] + M[x][y - 1] - M[x - 1][y - 1];

    int max_tree = 0, cut_x = 0, cut_y = 0;
    for (int x = 0; x < n; x++)
    {
        int s1, s2, s3, s4, min_section = 0;
        for (int y = 0; y < m; y++)
        {
            s1 = M[x][y];
            s2 = M[x][m - 1] - s1;
            s3 = M[n - 1][y] - s1;
            s4 = M[n - 1][m - 1] - s1 - s2 - s3;

            min_section = min({s1, s2, s3, s4});
            if (min_section > max_tree)
            {
                cut_x = x;
                cut_y = y;
                // max_tree = max(max_tree, min_section);
                max_tree = min_section;
            }
        }
    }
    cout << max_tree << endl;
    cout << "Cut Position: " << cut_x << " " << cut_y;
}

int main()
{
    // int n, m;
    // cin >> n >> m;
    // char arr[n][m];
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         cin >> arr[i][j];
    //     }
    // }
    // mango_tree(arr, n, m);

    char arr[][6] = {{'.', '#', '#', '.', '.', '.'},
                     {'#', '.', '.', '#', '#', '.'},
                     {'.', '#', '.', '.', '.', '.'},
                     {'.', '#', '#', '.', '.', '#'},
                     {'#', '.', '.', '#', '#', '.'},
                     {'.', '#', '.', '.', '.', '.'}};
    mango_tree(arr, 6, 6);
    return 0;
}