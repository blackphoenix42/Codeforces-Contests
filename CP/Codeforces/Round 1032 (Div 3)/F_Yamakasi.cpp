#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

long long countSubarraysWithSum(const vector<int> &arr, int fromIdx, int toIdx, long long targetSum)
{
    if (fromIdx >= toIdx)
        return 0;

    unordered_map<long long, int> prefixFreq;
    prefixFreq[0] = 1;
    long long currentPrefixSum = 0;
    long long matchingCount = 0;

    for (int idx = fromIdx; idx < toIdx; ++idx)
    {
        currentPrefixSum += arr[idx];
        if (prefixFreq.count(currentPrefixSum - targetSum))
        {
            matchingCount += prefixFreq[currentPrefixSum - targetSum];
        }
        prefixFreq[currentPrefixSum]++;
    }
    return matchingCount;
}

void solve()
{
    int numElements;
    long long targetSum;
    int maxElementAllowed;
    cin >> numElements >> targetSum >> maxElementAllowed;

    vector<int> inputArr(numElements);
    for (int i = 0; i < numElements; ++i)
    {
        cin >> inputArr[i];
    }

    long long totalValidSubarrays = 0;
    int left = 0;

    for (int right = 0; right <= numElements; ++right)
    {
        if (right == numElements || inputArr[right] > maxElementAllowed)
        {
            if (left < right)
            {
                totalValidSubarrays += countSubarraysWithSum(inputArr, left, right, targetSum);

                int excludeStart = left;
                for (int mid = left; mid <= right; ++mid)
                {
                    if (mid == right || inputArr[mid] == maxElementAllowed)
                    {
                        if (excludeStart < mid)
                        {
                            totalValidSubarrays -= countSubarraysWithSum(inputArr, excludeStart, mid, targetSum);
                        }
                        excludeStart = mid + 1;
                    }
                }
            }
            left = right + 1;
        }
    }
    cout << totalValidSubarrays << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
