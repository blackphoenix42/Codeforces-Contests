/*
    WAF that take input an sorted array of distinct integers, which is rotated about a pivot point and finds the index of any goven element.

    Input:
    7,9,10,1,2,3,4,5,6
    element = 4

    Output:
    6
*/

#include <bits/stdc++.h>
using namespace std;

int rotate_search(vector<int> arr, int key)
{
    int n = arr.size();
    int s = 0;
    int e = n - 1;

    while (s <= e)
    {
        int mid = (s + e) / 2;
        if (arr[mid] == key)
            return mid;

        if (arr[s] <= arr[mid])
        {
            if (key >= arr[s] and key <= arr[mid])
            {
                e = mid - 1;
            }
            else
            {
                s = mid + 1;
            }
        }
        else
        {
            if (key >= arr[mid] and key <= arr[e])
            {
                s = mid + 1;
            }
            else
            {
                e = mid - 1;
            }
        }
    }
    return -1;
}

int main()
{
    vector<int> arr{4, 5, 6, 7, 0, 1, 2, 3};
    int key;
    cin >> key;
    cout << rotate_search(arr, key);

    return 0;
}