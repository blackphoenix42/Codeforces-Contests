#include <bits/stdc++.h>
using namespace std;

void printAllPairs(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            cout << arr[i] << " " << arr[j] << endl;
}

int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    printAllPairs(a, n);

    return 0;
}