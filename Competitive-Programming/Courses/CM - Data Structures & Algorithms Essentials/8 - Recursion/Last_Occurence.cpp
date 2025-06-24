/*
    WAF to find the last occurrence of an element in an array
*/

#include <bits/stdc++.h>
using namespace std;

int lastOcc(int arr[], int n, int key)
{
    if (n == 0)
        return -1;

    int subIndex = lastOcc(arr + 1, n - 1, key);

    if (arr[0] == key and subIndex < 0)
        return 0;

    if (subIndex != -1)
        return subIndex + 1;

    return -1;
}

int main()
{
    int arr[] = {1, 3, 5, 7, 6, 11, 11, 21};
    int n = sizeof(arr) / sizeof(int);
    int key = 11;
    cout << lastOcc(arr, n, key);

    return 0;
}