#include <bits/stdc++.h>
using namespace std;

struct Operation
{
    int opType, index;
};

void applySwap(int opType, int index, vector<int> &arrA, vector<int> &arrB, vector<Operation> &operations)
{
    if (opType == 1)
        swap(arrA[index - 1], arrA[index]);
    else if (opType == 2)
        swap(arrB[index - 1], arrB[index]);
    else
        swap(arrA[index - 1], arrB[index - 1]);
    operations.push_back({opType, index});
}

void solve()
{
    int arrayLength;
    cin >> arrayLength;
    vector<int> sequenceA(arrayLength), sequenceB(arrayLength);
    for (int &val : sequenceA)
        cin >> val;
    for (int &val : sequenceB)
        cin >> val;

    vector<Operation> operationList;

    for (int idx = 0; idx < arrayLength; ++idx)
    {
        int desiredA = idx + 1, desiredB = arrayLength + idx + 1;

        int posA = idx;
        while (posA < arrayLength && sequenceA[posA] != desiredA && sequenceB[posA] != desiredA)
            ++posA;
        if (posA < arrayLength && sequenceB[posA] == desiredA)
            applySwap(3, posA + 1, sequenceA, sequenceB, operationList);
        while (posA > idx)
        {
            applySwap(1, posA, sequenceA, sequenceB, operationList);
            --posA;
        }

        int posB = idx;
        while (posB < arrayLength && sequenceA[posB] != desiredB && sequenceB[posB] != desiredB)
            ++posB;
        if (posB < arrayLength && sequenceA[posB] == desiredB)
            applySwap(3, posB + 1, sequenceA, sequenceB, operationList);
        while (posB > idx)
        {
            applySwap(2, posB, sequenceA, sequenceB, operationList);
            --posB;
        }
    }

    cout << operationList.size() << '\n';
    for (const auto &op : operationList)
    {
        cout << op.opType << ' ' << op.index << '\n';
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
