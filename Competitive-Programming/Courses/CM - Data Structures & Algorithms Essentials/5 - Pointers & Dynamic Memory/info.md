## Address

- Address Operator: `&`
- It will print in hexadecimal

```cpp
int p = 5;
int *q = &p;
// Assign address of p in q
```

## Pointers

- A variable that holds address of another variable
- Example: `int *ptr = &x;`
- Various Syntaxes are allowded:

```cpp
int *ptr1;
int * ptr2;
int* ptr3;
```

- pointer to a pointer variable:

```cpp
int x = 5;
int *ptr = &x;
int ** ptr2 = &ptr;
```

## Dereference Operator

- Also denoted by `*`
- Also known as _value pointed to by_
- If we do \* of some address it will give us the value stored in that address

**&Bucket(storing value) => Address**

**\*Address => Bucket**

```cpp
int x = 5;
int * ptr = &x;

cout << ptr;   // Address
cout << *ptr;  // 5
```

## Null Ptr

- You **cannot dereference a null ptr**, else you will get an error of segmentation fault.
- Ways to initialise Null Pointer

```cpp
int * p = 0;
int * q = NULL;
```

## Reference Variables

- Pass objects by reference to other functions
- Above thing can be done in two ways:
  1. Pointers-Dereference
  2. Reference Vatiables
- Always need to be initalised

```cpp
int x = 10;
int &y = x;     // x,y are name of same bucket like different aliases
```

#### Pass By reference:

```cpp
// Pass By Reference
void applyTax(int &income){
    float tax = 0.10;
    income = income - income*tax;
}
int main(){
    int income = 100;
    applyTax(income);
    cout << income;     // 90

}

```

#### Using Pointers-Dereference:

```cpp
void watchVideo(int *viewsPtr){
    *viewsPtr = *viewsPtr + 1;
}
int main(){
    int views = 100;
    watchVideo(&views);
    cout << views;  // 101

}
```

- Reference Variables are much easier than using Pointers-Dereference

## Dynamic Memory Allocation

```cpp
int n;
cin >> n;

int *arr = new int[n];
// int *arr will be created in stack memory and store some address from heap memory
// new int[n] will be created in heap memory

*arr = 100;     // Means *(arr + 0) = arr[0] = 100
arr[1] = 50;    // Can also be written as *(arr + 1) = 50;

// When function ends stack memory will be erased but heap memory will remain
// When program ends all memory gets deleted
// So free memory for every Dynamic Mmeory Allocation else memory leak
delete [] arr;

// For Variables
int * x = new int;  // Basically it creates an array of size 1
*x = 10;
cout << x[0];       // To access value or *x = *(x + 0) => 10

```

- Representation: `arr[2] = *(arr + 2)`

## 2D Dynamic Array

- Not simple like static memory 2d array
- One by One we have to iterate over all rows of 1D array and store address of these rows

```cpp

int ** create2DArray(int rows, int cols){

    int **arr = new int*[rows];
    for(int i = 0; i< rows;i++){
        arr[i] = new int[cols];
    }
    return arr;
}


```
