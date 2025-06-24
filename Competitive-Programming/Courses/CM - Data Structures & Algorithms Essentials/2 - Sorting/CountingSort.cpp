#include <bits/stdc++.h>
using namespace std;

void counting_sort(int arr[], int n)
{
    int largest = -1;
    for (int i = 0; i < n; i++)
        largest = max(largest, arr[i]);

    vector<int> freq(largest + 1, 0);

    for (int i = 0; i < n; i++)
        freq[arr[i]]++;

    int j = 0;
    for (int i = 0; i <= largest; i++)
    {
        while (freq[i] > 0)
        {
            arr[j] = i;
            freq[i]--;
            j++;
        }
    }
}

int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    counting_sort(a, n);

    for (int i = 0; i < n; i++)
        cout << a[i] << endl;
    return 0;
}