#include <bits/stdc++.h>
using namespace std;

void insertion_sort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int e = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > e)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = e;
    }
}

int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    insertion_sort(a, n);

    for (int i = 0; i < n; i++)
        cout << a[i] << endl;
    return 0;
}