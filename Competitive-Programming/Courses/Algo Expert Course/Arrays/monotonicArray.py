# O(n) Time | O(1) Space

def monotonicArray(array):
    isIncreasing = True
    isDecreasing = True
    for i in range(1, len(array)):
        if array[i-1] < array[i]:
            isDecreasing = False
        if array[i-1] > array[i]:
            isIncreasing = False
    return isIncreasing or isDecreasing
