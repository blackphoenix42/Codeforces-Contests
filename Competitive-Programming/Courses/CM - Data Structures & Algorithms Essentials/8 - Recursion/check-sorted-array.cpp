#include <bits/stdc++.h>
using namespace std;

bool checkSorted(int arr[], int n)
{
    if (n == 1 or n == 0)
        return true;

    if (arr[0] < arr[1] and checkSorted(arr + 1, n - 1))
    {
        return true;
    }
    return false;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(int);
    cout << checkSorted(arr, n);
    return 0;
}