#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
public:
    int length;
    vector<int> maxVals, lazyVals;

    SegmentTree(int len) : length(len), maxVals(4 * len, 0), lazyVals(4 * len, 0) {}

    void push(int node)
    {
        if (lazyVals[node])
        {
            for (int child : {node << 1, node << 1 | 1})
            {
                maxVals[child] += lazyVals[node];
                lazyVals[child] += lazyVals[node];
            }
            lazyVals[node] = 0;
        }
    }

    void addRange(int node, int left, int right, int queryLeft, int queryRight, int value)
    {
        if (queryLeft > right || queryRight < left)
            return;
        if (queryLeft <= left && right <= queryRight)
        {
            maxVals[node] += value;
            lazyVals[node] += value;
            return;
        }
        push(node);
        int mid = (left + right) >> 1;
        addRange(node << 1, left, mid, queryLeft, queryRight, value);
        addRange(node << 1 | 1, mid + 1, right, queryLeft, queryRight, value);
        maxVals[node] = max(maxVals[node << 1], maxVals[node << 1 | 1]);
    }

    int queryMax(int node, int left, int right, int queryLeft, int queryRight)
    {
        if (queryLeft > right || queryRight < left)
            return 0;
        if (queryLeft <= left && right <= queryRight)
            return maxVals[node];
        push(node);
        int mid = (left + right) >> 1;
        return max(queryMax(node << 1, left, mid, queryLeft, queryRight),
                   queryMax(node << 1 | 1, mid + 1, right, queryLeft, queryRight));
    }

    void updateRange(int left, int right, int value)
    {
        addRange(1, 0, length - 1, left, right, value);
    }

    int getRangeMax(int left, int right)
    {
        return left > right ? 0 : queryMax(1, 0, length - 1, left, right);
    }

    int getPointValue(int position)
    {
        return queryMax(1, 0, length - 1, position, position);
    }
};

void processTestCase()
{
    int numSegments;
    cin >> numSegments;
    vector<long long> segmentLefts(numSegments), segmentRights(numSegments), allCoords;
    for (int i = 0; i < numSegments; ++i)
    {
        cin >> segmentLefts[i] >> segmentRights[i];
        allCoords.push_back(segmentLefts[i]);
    }
    sort(allCoords.begin(), allCoords.end());
    allCoords.erase(unique(allCoords.begin(), allCoords.end()), allCoords.end());
    int coordCount = allCoords.size();
    SegmentTree segTree(coordCount);
    vector<int> answers(numSegments);

    for (int i = 0; i < numSegments; ++i)
    {
        int leftIdx = lower_bound(allCoords.begin(), allCoords.end(), segmentLefts[i]) - allCoords.begin();
        int rightIdx = upper_bound(allCoords.begin(), allCoords.end(), segmentRights[i]) - allCoords.begin() - 1;
        if (rightIdx >= leftIdx)
            segTree.updateRange(leftIdx, rightIdx, 1);
        int bestBefore = leftIdx ? segTree.getRangeMax(0, leftIdx - 1) : 0;
        int newLen = bestBefore + 1;
        int curVal = segTree.getPointValue(leftIdx);
        if (newLen > curVal)
            segTree.updateRange(leftIdx, leftIdx, newLen - curVal);
        answers[i] = segTree.getRangeMax(0, coordCount - 1);
    }
    for (int i = 0; i < numSegments; ++i)
    {
        if (i)
            cout << ' ';
        cout << answers[i];
    }
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    while (testCases--)
    {
        processTestCase();
    }
    return 0;
}
