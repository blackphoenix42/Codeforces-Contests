Problem statement: You are given a maze with N cells. Each cell may have multiple entry points but not more than one exit (ie. entry/exit points are unidirectional doors like valves). The cells are named with an integer value from 0 to N-1. You need to find the following :
Nearest meeting cell: Given any two cells - C1,C2, find the closest cell Cm that can be reached from both C1 and C2.
Note: Aim for O(Log(N)) solution.
INPUT FORMAT - First line has the number of cells N
Second line has list of N values of the edge[] array. edge[i] contains the cell number that can be reached from of cell ‘i’ in one step. edge[i] is -1 if the ‘i’th cell doesn’t have an exit.
Third line contains two cell numbers whose nearest meeting cell needs to be found. (return -1 if there is no meeting cell from the two given cells) .
OUTPUT FORMAT - Find nearest meeting cell (NMC).
