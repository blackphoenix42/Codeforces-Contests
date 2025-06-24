# O(n) Time | O(n) Space

def spiralTraverse(array):
    startRow = 0
    endRow = len(array) - 1
    startCol = 0
    endCol = len(array)-1
    result = []
    while startRow <= endRow and startCol <= endCol:
        for col in range(startCol, endCol+1):
            result.append(array[startRow][col])

        for row in range(startRow+1, endRow+1):
            result.append(array[row][endRow])

        for col in reversed(range(startCol, endCol)):
            result.append(array[endRow][col])

        for row in reversed(range(startRow+1, endRow)):
            result.append(array[row][startCol])
        startRow += 1
        endRow -= 1
        startCol += 1
        endCol -= 1
    return result
