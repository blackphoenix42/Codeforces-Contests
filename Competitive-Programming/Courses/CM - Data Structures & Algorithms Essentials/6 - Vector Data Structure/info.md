## Vectors

- Sequence Containers representing arrays that can change in size
- Vectors use contiguous memory allocations like arrays
- Its elements can also be accessed in `O(1)` time
- Their size can change dynamically with their storage being handled automatically by container unlike arrays

**Containers:** It represents a Data Structure. Ex: vector is a container or data structure

**STL:** Stndard Template Library

## How they grow?

- A n sized array is created in memory. If it gets full it is copied into 2n sized one and previous array is freed from memory.

## Complexity

- **push_back** => `O(1)` but for some cases when array gets full and it needs to be copied into bigger array `O(n)`

```cpp
vector <int> arr = {1,2,3,4,5};

// Size of the vector
cout << arr.size();

// It tells how many elelments can be inserted in vector.
// Capacity of vector prints the starting space that vector has. If it gets full it will double itself
cout << arr.capacity();

//push_back
arr.push_back(6);

//pop_back
arr.pop_back();

// Fill constructor
vector<int> arr(10,7);  // 10 elements with each element as 7

```

## 2D Vector

```cpp
vector < vector <int> > arr = {
    {1,2,3},
    {4,5},
    {6},
    {7,8,9}};

// Print
for (int i  = 0; i < arr.size(); i++) {
    for (int number : arr[i]) {
        cout << number;
    }
}

// To update
arr[0][0] += 10;
```

## Vector Data Structure Implementation

```cpp

template <typename T>
class Vector
{

    // Data Members
    T *arr;
    int cs; // current size
    int ms; // max size

public:
    Vector(int max_size = 1)
    {
        cs = 0;
        ms = max_size;
        arr = new T[ms];
    }

    void push_back(const T d)
    {
        if (cs == ms)
        {
            // Create a new array and delete old one, double the capacity
            T *oldArr = arr;
            ms = 2 * ms;
            arr = new T[ms];

            for (int i = 0; i < cs; i++)
            {
                arr[i] = oldArr[i];
            }

            delete[] oldArr;
        }
        arr[cs] = d;
        cs++;
    }

    void pop_back()
    {
        if (cs >= 0)
        {
            cs--;
        }
    }

    bool isEmpty() const
    {
        return cs == 0;
    }

    T front() const
    {
        return arr[0];
    }

    T back() const
    {
        return arr[cs - 1];
    }

    T at(int i) const
    {
        return arr[i];
    }

    int size() const
    {
        return cs;
    }

    int capacity() const
    {
        return ms;
    }

    T operator[](const int i) const
    {
        return arr[i];
    }
};

int main(){
    Vector<int> v(5);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    cout << v.size() << endl
         << v.capacity();

    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

```

## Good Practices while defining classes and objects

- When the value of `i` is not changing its better to make argument as `const`

```cpp
int operator[](const int i)
    {
        return arr[i];
    }
```

- When the function is not changing any attributes of a class, its better to make function a `const`

```cpp
    int size() const {
        return cs;
    }
```

## Header Files

- Cut the code for vector class and paste in file with name 'vector.h'

```cpp
// your own header file will have double quotes not angular brackets
#include "vector.h"
```

## Template Classes

- In this it can be used to make generic vectors meaning vectors out of anything

```cpp
//use before class
template <typename T>
class Vector{
    ....
};
```

## Inbuilt Searching

- `find` function in `algorithm` header file

````cpp

int main(){
    vector<int> arr = {10, 11, 2, 3, 4, 6, 7, 8};

    int key = 11;

    // end is not included
    vector<int>::iterator it = search(arr.begin(), arr.end(), key);

    // To find index = Address - BaseAddress
     if (it != arr.end())
        cout << it - arr.begin();
    else
        cout << "Not Found";
}

- `search` function serches for a subsequence in an array


```cpp
    vector<int> arr = {10, 11, 2, 3, 4, 6, 7, 8};

    int needle[] = {2, 3, 4, 6};

    // Can also give another optional argument as a function name to compare two integers in our own way
    vector<int>::iterator it = find(arr.begin(), arr.end(), needle, needle + 4);

    // Return an index hwere this sequence starts
    if (it != arr.end())
        cout << it - arr.begin();
    else
        cout << "Not Found";
````

- Some more: binary_search, lower_bound(Search for first occurrence of element)), upper_bound (Search for last occurrence of element)

## Sorting a Complex Vector

```cpp

int calcTotalMarks(vector<int> marks)
{
    return marks[0] + marks[1] + marks[2];
}

bool compare(pair<string, vector<int>> s1, pair<string, vector<int>> s2)
{
    vector<int> m1 = s1.second;
    vector<int> m2 = s2.second;
    return calcTotalMarks(m1) > calcTotalMarks(m2);
}

int main()
{
    vector<pair<string, vector<int>>> student_marks = {
        {"Rohan", {10, 20, 11}},
        {"Prateek", {10, 21, 3}},
        {"Vivek", {4, 5, 6}},
        {"Rijul", {10, 13, 20}}};

    // Sort in lexicographical Order
    sort(student_marks.begin(), student_marks.end());
    for (auto s : student_marks)
        cout << s.first << endl;

    // Sort in order of total marks
    sort(student_marks.begin(), student_marks.end(), compare);
    for (auto s : student_marks)
        cout << s.first << " " << calcTotalMarks(s.second) << endl;
}

```
