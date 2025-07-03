#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Reads the grid and collects positions of the max value
void readGrid(int &numRows, int &numCols, int &maxValue, vector<pair<int, int>> &maxValuePositions)
{
    cin >> numRows >> numCols;
    maxValue = 0;
    maxValuePositions.clear();
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0, val; col < numCols; ++col)
        {
            cin >> val;
            if (val > maxValue)
            {
                maxValue = val;
                maxValuePositions.clear();
                maxValuePositions.emplace_back(row, col);
            }
            else if (val == maxValue)
            {
                maxValuePositions.emplace_back(row, col);
            }
        }
    }
}

// Checks if all max value positions can be covered as per the problem
bool checkCoverable(const vector<pair<int, int>> &maxValuePositions)
{
    unordered_set<int> candidateRows;
    for (const auto &cell : maxValuePositions)
    {
        candidateRows.insert(cell.first);
    }
    for (int row : candidateRows)
    {
        int colCandidate = -1;
        bool canCover = true;
        for (const auto &[r, c] : maxValuePositions)
        {
            if (r == row)
                continue;
            if (colCandidate == -1)
                colCandidate = c;
            else if (c != colCandidate)
            {
                canCover = false;
                break;
            }
        }
        if (canCover)
            return true;
    }
    return false;
}

void solve()
{
    int numRows, numCols, maxValue;
    vector<pair<int, int>> maxValuePositions;
    readGrid(numRows, numCols, maxValue, maxValuePositions);
    bool isCoverable = checkCoverable(maxValuePositions);
    cout << (isCoverable ? maxValue - 1 : maxValue) << "\n";
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
