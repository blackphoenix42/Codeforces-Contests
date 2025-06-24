#include <bits/stdc++.h>
using namespace std;

void bubbleSort(int arr[], int n)
{
    if (n == 1)
        return;

    for (int j = 0; j < n - 1; j++)
        if (arr[j] > arr[j + 1])
            swap(arr[j], arr[j + 1]);

    bubbleSort(arr, n - 1);
}

void bubbleSort2(int arr[], int n, int j)
{
    if (n == 1)
        return;

    if (j == n - 1)
    {
        bubbleSort2(arr, n - 1, 0);
        return;
    }

    if (arr[j] > arr[j + 1])
        swap(arr[j], arr[j + 1]);
    bubbleSort2(arr, n, j + 1);
}

int main()
{
    int arr[] = {1, 3, 2, 5, 4};
    int n = sizeof(arr) / sizeof(int);

    // bubbleSort(arr, n);
    bubbleSort2(arr, n, 0);

    for (int i = 0; i < n; i++)
        cout << arr[i] << endl;
    return 0;
}