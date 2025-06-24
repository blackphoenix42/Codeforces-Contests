/*
Given a partially filled sudoku matrix 9x9
Write a function to fill the matrix using Sudoku Rules

Input 
2D Matrix

Output
Solved 2D Matrix

*/

#include <bits/stdc++.h>
using namespace std;

bool isSafe(int mat[][9],int i,int j,int no, int n){
    // check for row and col
    for(int k = 0; k < n; k++){
        if(mat[k][j] == no || mat[i][k] == no){
            return false;
        }
    }

    // check for subgrid
    int sx = (i / 3) * 3;
    int sy = (j / 3) * 3;
    for (int x = sx; x < sx + 3; x++)
    {
        for (int y = sy; y < sy + 3; y++)
        {
            if(mat[x][y] == no){
                return false;
            }
        }
        
    }
    


    return true;
}

bool solveSudoku(int mat[][9],int i,int j,int n){
    // Base Case
    if(i == n){
        // print the solution
        for(int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++)
            {
                cout<<mat[i][j]<< " ";
            }
            cout<<endl;
        }
        return true;
    }

    // Rec Case
    if(j==n){
        return solveSudoku(mat, i+1, 0, n);
    }


    //skip the prefilled cell
    if(mat[i][j] != 0){
        return solveSudoku(mat, i, j+1, n);
    }

    // cell to be filled
    // Try all posibilites
    for(int no = 1; no <=n; no++){
        // whether it is safe to place the number or not
        if(isSafe(mat,i,j,no,n)){
            
            mat[i][j] = no;
            bool solveSubproblem = solveSudoku(mat,i,j+1,n);
            if(solveSubproblem == true){
                return true;
            }
        }
    }
    // if no option works
    mat[i][j] = 0;
    return false;
}

int main()
{
    int n = 9;
    int mat[9][9] = {
        {5,3,0, 0,7,0, 0,0,0},
        {6,0,0, 1,9,5, 0,0,0},
        {0,9,8, 0,0,0, 0,6,0},

        {8,0,0, 0,6,0, 0,0,3},
        {4,0,0, 8,0,3, 0,0,1},
        {7,0,0, 0,2,0, 0,0,6},

        {0,6,0, 0,0,0, 2,8,0},
        {0,0,0, 4,1,9, 0,0,5},
        {0,0,0, 0,8,0, 0,7,9}
    };
    if(!solveSudoku(mat,0,0,n)){
        cout<<"No solution exists!";
    }
    return 0;
}