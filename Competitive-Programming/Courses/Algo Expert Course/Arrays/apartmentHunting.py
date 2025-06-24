# Locations: [School, Gym, Store]
# Requiremnts/Locations given for every index []
# Rent an apartment at an index where it will be closest to all three

# O(B*R) Time | O(B*R) Space    Blocks = Given array of various locations, Requirements = Types of location array

def apartmentHunting(blocks, reqs):
    minDistancesFromBlocks = list(map(lambda req: getMinDistances(blocks, req), reqs))
    maxDistancesAtBlocks = getMaxDistancesAtBlocks(blocks, minDistancesFromBlocks)
    getIdxAtMinValue = maxDistancesAtBlocks.index(min(maxDistancesAtBlocks))
    return getIdxAtMinValue


def getMinDistances(blocks, req):
    minDistances = [0 for _ in blocks]
    closestReqIdx = float("inf")
    for i in range(len(blocks)):
        if blocks[i][req]:
            closestReqIdx = i
        minDistances[i] = abs(i - closestReqIdx)
    for i in reversed(range(len(blocks))):
        if blocks[i][req]:
            closestReqIdx = i
        minDistances[i] = min(minDistances[i], abs(i - closestReqIdx))
    return minDistances

def getMaxDistancesAtBlocks(blocks, minDistancesFromBlocks):
    maxDistancesAtBlocks = [0 for _ in blocks]
    for i in range(len(blocks)):
        minDistancesAtBlock = list(map(lambda distances: distances[i], minDistancesFromBlocks))
        maxDistancesAtBlocks[i] = max(minDistancesAtBlock)
    return maxDistancesAtBlocks

# print(apartmentHunting([{'sc': True, 'g': False, 'st': False}, {'sc': False, 'g': True, 'st': False}, {
#       'sc': True, 'g': True, 'st': False, }, {'sc': True, 'g': False, 'st': False}, {'sc': True, 'g': False, 'st': True}], ['sc', 'g', 'st']))
