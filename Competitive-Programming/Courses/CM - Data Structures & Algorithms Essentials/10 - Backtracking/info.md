## Subsets / Subsequence (Not Continuous)

- Total Subsets of a string

```
Length - n

Total Subsets - 2^n
```

```
Example:
    Input
    abc

    Output
    "",a,b,c,ab,ac,bc,abc

```

## Permutations

```
Length - n
Permutaions - n!
```

- Rstore original array while going back using backtracking as arrays are passed by reference so it may change

## Sudoku Solver

- 9 x 9 Grid

- Every row must have numbers 1 to 9
- Every column must have numbers 1 to 9

- Every subgrid of 3x3 must have 1 to 9

- No number must repeat in subgrid or row or column

- Multiple solutions possible

```
Try all possibilities

Stop when we get 1 valid solution

Check i,j if a no. (1 to 9) can be placed
    - means it doesnt occur in col, row , subgrid

if Yes :
    Place it
        a[i][j] = no.
Solve (i, j+1)
Try next if solve return false
Return true


Base Case:
    if j == 9:  // col reached at the end go to next row
        i = i+1, j = 0
    if i == 9:
        return true
    if u tried all above possibilites and no number is suited in that false then go back and do some corrections by changing number


5,3,0, 0,7,0, 0,0,0
6,0,0, 1,9,5, 0,0,0
0,9,8, 0,0,0, 0,6,0

8,0,0, 0,6,0, 0,0,3
4,0,0, 8,0,3, 0,0,1
7,0,0, 0,2,0, 0,0,6

0,6,0, 0,0,0, 2,8,0
0,0,0, 4,1,9, 0,0,5
0,0,0, 0,8,0, 0,7,9

```
- Formula to find a subgrid for x,y

```
Sx = (x/3) * 3

Sy = (y/3) * 3

```