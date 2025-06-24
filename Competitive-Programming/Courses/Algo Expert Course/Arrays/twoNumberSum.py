# O(n) Time | O(n) Space

def twoNumberSum(array, targetSum):
    nums = {}
    for num in array:
        match = targetSum - num
        if match in nums:
            return [match, num]
        else:
            nums[num] = True
    return []


# O(nlog(n)) Time | O(1) Space

def checkPairs(array, targetSum):
    array.sort()
    left = 0
    right = len(array)-1
    while left < right:
        match = array[left] + array[right]
        if match == targetSum:
            return[array[left], array[right]]
        elif match < targetSum:
            left += 1
        elif match > targetSum:
            right -= 1
    return []
