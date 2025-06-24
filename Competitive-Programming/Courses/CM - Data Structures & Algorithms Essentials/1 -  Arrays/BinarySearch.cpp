#include <bits/stdc++.h>
using namespace std;

// Time Complexity = O(logN)

int binary_search(int arr[], int n, int key)
{

    int start = 0, end = n - 1;

    while (start <= end)
    {
        int mid = (start + end) / 2;
        if (arr[mid] == key)
        {
            return mid;
        }
        else if (arr[mid] > key)
        {
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }

    return -1;
}

int main()
{
    int n, key;
    cin >> n >> key;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int index = binary_search(a, n, key);

    if (index != -1)
        cout << index;
    else
        cout << "Not Found";

    return 0;
}