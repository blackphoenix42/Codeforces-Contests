You are given a maze with N-cells. Each cell may have multiple entry points but not more than one exit (i.e. entry/exit points are unidirectional doors like valves).

The cells are named with an integer value from 0 to N-1.

You have to find: find the node number of maximum weigth node (Weight of a node is the sum of node numbers of all nodes pointing to that node)

INPUT FORMAT

An integer T, denoting the number of test cases, followed by 2T lines as the test case will contain 2 lines. The first line of each test case has the number of cells N. The second line of each test case has a list of N values of edge[] array.edge[] array.edge[i] contains the cell number that can be reached from cell “i” in one step. edge[i] is -1 if the "i"th cell doesn’t have an exit.

OUTPUT FORMAT

First-line denotes the node number with the maximum wight node.

Sample Input

1

23

4 4 1 4 13 8 8 8 0 8 14 9 15 11 -1 10 15 22 22 22 22 22 21

Sample output

22
