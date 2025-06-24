# Heaps / Priority Queue

- Priority Queue which is implemented using heap data structure
- Use heap when there are large number of elements and you need to get min / max
- Either a heap can be max heap or min heap but not both

## Heap

1. **Binary Tree:** At most 2 children per node
2. **Complete Binary Tree (CBT):**

- All levels of tree should be completely filled
- Excpet last level which can be partially filled
- But must be filled in left to right order

3. **Heap Order Property:**
   - Max Heap: Each node must be greater than or equal to its both children
   - Min Heap: Each node must be smaller than or equal to its both children

```
                    100
            40                  50
        10      15          50

```

## Heap as an Array

- A heap can be easily flattened out in an array
- Child `i` has children at `2i`, `2i+1` in an array
- Parent can also be found by `i/2`

## Heap Concepts

1. Push: O(logn)

2. Pop Min/Max: O(logn)

3. Get Min/Max: O(1)

## Max Heap

- From which we can extract max element

## Custom Comparator for min Heap

```cpp

class Compare{
  public:
  bool operator()(int a, int b){
    // Less than creates Max Heap and greater than creates Min Heap
    return a > b;
  }
};

int main()
{
    int arr [] = {10,15,20,13,6,90};

    priority_queue<int, vector<int>, Compare> heap;

    for (int x : arr){
        heap.push(x);
    }

    while(!heap.empty()){
        cout<<heap.top()<<endl;
        heap.pop();
    }

    return 0;
}

```
