#include <bits/stdc++.h>
using namespace std;

int linear_search(int arr[], int n, int key)
{
    for (int i = 0; i < n; i++)
        if (arr[i] == key)
            return i;

    return -1;
}

int main()
{
    int n, key;
    cin >> n >> key;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int index = linear_search(a, n, key);

    if (index != -1)
        cout << index;
    else
        cout << "Not Found";

    return 0;
}