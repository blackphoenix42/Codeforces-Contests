#include <bits/stdc++.h>
using namespace std;

void merge(vector<int> &arr, int s, int e)
{
    int i = s;
    int m = (s + e) / 2;
    int j = m + 1;

    vector<int> temp;

    while (i <= m and j <= e)
    {
        if (arr[i] < arr[j])
        {
            temp.push_back(arr[i]);
            i++;
        }
        else
        {
            temp.push_back(arr[j]);
            j++;
        }
    }

    while (i <= m)
    {
        temp.push_back(arr[i++]);
    }
    while (j <= e)
    {
        temp.push_back(arr[j++]);
    }

    int k = 0;
    for (int i = s; i <= e; i++)
    {
        arr[i] = temp[k++];
    }
    return;
}

void mergeSort(vector<int> &arr, int s, int e)
{
    if (s >= e)
        return;

    int mid = (s + e) / 2;

    mergeSort(arr, s, mid);
    mergeSort(arr, mid + 1, e);
    return merge(arr, s, e);
}

int main() 
{
    vector<int> arr{1, 3, 2, 5, 4};
    int s = 0;
    int e = arr.size() - 1;

    mergeSort(arr, s, e);

    for (int x : arr)
        cout << x << endl;
    return 0;
}