#include <bits/stdc++.h>
using namespace std;

// Kadane's Algo - O(n)
void maxSubarraySum1(int arr[], int n)
{
    int maxSum = INT_MIN;
    int currentSum = 0;

    for (int i = 0; i < n; i++)
    {
        currentSum += arr[i];
        if (currentSum < 0)
        {
            currentSum = 0;
        }
        maxSum = max(currentSum, maxSum);
    }
    cout << maxSum << endl;
}

// Cummulative Sum or Precomputing - O(n + n^2)
void maxSubarraySum2(int arr[], int n)
{
    int csum[n] = {0};
    csum[0] = arr[0];

    for (int i = 1; i < n; i++)
        csum[i] = csum[i - 1] + arr[i];

    int maxSum = INT_MIN;
    // int left, right = 0;

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
        {
            int currentSum = i > 0 ? csum[j] - csum[i - 1] : csum[j];
            if (maxSum < currentSum)
            {
                maxSum = currentSum;
                // left = i;
                // right = j;
            }
        }

    cout << maxSum << endl;
    // for (int i = left; i <= right; i++)
    //     cout << arr[i] << " ";
}

//Brute Force - O(n^3)
void maxSubarraySum3(int arr[], int n)
{
    int maxSum = INT_MIN;
    // int left, right = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int currentSum = 0;
            for (int k = i; k <= j; k++)
                currentSum += arr[k];
            if (maxSum < currentSum)
            {
                maxSum = currentSum;
                // left = i;
                // right = j;
            }
        }
    }

    cout << maxSum << endl;
    // Print subarray
    // for (int i = left; i <= right; i++)
    //     cout << a[i] << " ";
}

int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    maxSubarraySum1(a, n);
    maxSubarraySum2(a, n);
    maxSubarraySum3(a, n);

    return 0;
}