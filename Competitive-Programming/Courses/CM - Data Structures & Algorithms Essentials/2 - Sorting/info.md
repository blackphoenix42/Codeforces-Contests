### Inbuilt Sort

- In the header file `<algorithm>`
- Works in O(NLogN)
- Syntax: `sort(arr,arr + n)`
- Custom Compartor Function Syntax for descending order: `sort(a, a + n, comparator)`

```cpp
bool comparator(int a, int b)
{
    return a > b;
}
```

- Using inbuilt comparator function: `sort(arr, arr+n, greater<int>())`

- We can also reverse sorted array to make it in descending order: `reverse(arr, arr + n)`

### Counting Sort

- For data in a particular range, like student getting marks between 0 - 100
- Almost works in linear time O(N)
- TIme Complexity: `O(Range + N)`
