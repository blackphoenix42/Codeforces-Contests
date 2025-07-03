#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> petrol(n), cost(n);
    for (int i = 0; i < n; i++)
    {
        cin >> petrol[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> cost[i];
    }

    int total_surplus = 0, surplus = 0, start = 0;
    for (int i = 0; i < n; i++)
    {
        int diff = petrol[i] - cost[i];
        total_surplus += diff;
        surplus += diff;
        if (surplus < 0)
        {
            surplus = 0;
            start = i + 1;
        }
    }

    cout << (total_surplus >= 0 ? start : -1) << endl;
    return 0;
}
