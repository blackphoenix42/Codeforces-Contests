### Size of an array

```cpp
int arr[] = {1,2,3,4,5};
int n = sizeof(arr)/sizeof(int);
```

### Passing Arrays to functions

```cpp
// or can use this coid printArray(int * arr)
void printArray(int arr[])
{
    cout << "In Function " << sizeof(arr) << endl;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(int);

    cout << "In Main " << sizeof(arr) << endl;
    printArray(arr);
}
```

#### Output:

```
In Main 24
In Function 4
```

- This is because in function we just have address of array which is stored in pointers.
- Array in functions are passed by reference
- Always pass array and its size to the function

### Binary Search

- Array should always be sorted

### Cummulative Sum ( Max Sum from all subarrays)

- It is used to print sum of a subarray between a given range
- Ex: Print sum between index 2 to 5. So, csum till 5 - csum till 2
- For first element csum will be equal to that only.
- Formula to calculate Cummulative Sum: `csum[i] = csum[i-1] + arr[i]` for `i >= 1`
- Formula to calculate Sum between a range: `sum = csum[j] - csum[i - 1];`
- Time Complexity: `O(n + n^2)`

### Kadane's Algorithm ( Max Sum from all subarrays)

- Time Complexity: `O(n)`
