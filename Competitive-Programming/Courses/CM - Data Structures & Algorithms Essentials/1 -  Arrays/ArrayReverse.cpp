#include <bits/stdc++.h>
using namespace std;

void reverse_array(int arr[], int n)
{
    int s = 0, e = n - 1;
    while (s < e)
        swap(arr[s++], arr[e--]);
}

int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    reverse_array(a, n);

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << endl;
    }

    return 0;
}