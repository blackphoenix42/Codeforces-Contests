## Core Algorithms (Fundamentals You Must Know Cold)

## 📚 Section: Sorting Algorithms

**🎯 Category:** Core Algorithms (Fundamentals You Must Know Cold)

This section covers **seven essential sorting algorithms** you must master for interviews. Each algorithm is described with complete detail: concepts, usage, algorithmic steps, code (recursive + iterative if applicable), time/space complexities, pros/cons, applications, and visual understanding.

---

## 🔁 1. Merge Sort

### 🧠 Concept:

Merge Sort is a **Divide and Conquer** algorithm. It recursively splits the array into halves until subarrays of size 1 are reached and then merges them in sorted order.

### 🧰 Usage:

- Stable sort
- Used in external sorting (on large datasets)
- Guarantees O(n log n) time

### 🧩 Algorithm Steps:

1. Divide the array into halves recursively.
2. Merge the sorted halves.

### 📟 Recursive Code:

```cpp
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
```

### 🔁 Iterative Code:

```cpp
void mergeSortIterative(vector<int>& arr) {
    int n = arr.size();
    for (int curr_size = 1; curr_size <= n-1; curr_size *= 2) {
        for (int left_start = 0; left_start < n-1; left_start += 2*curr_size) {
            int mid = min(left_start + curr_size - 1, n-1);
            int right_end = min(left_start + 2*curr_size - 1, n-1);
            merge(arr, left_start, mid, right_end);
        }
    }
}
```

### ⏱️ Time Complexity:

- Best: **\Theta(n log n)**
- Average: **O(n log n)**
- Worst: **O(n log n)**

### 🧮 Space Complexity:

- **O(n)** (auxiliary space)

### ✅ Pros:

- Stable
- Consistent O(n log n)
- Good for linked lists

### ❌ Cons:

- Extra memory needed
- Poor cache performance

### 🚀 Applications:

- Sorting large datasets on disk
- Merging sorted files

---

## ⚡ 2. Quick Sort

### 🧠 Concept:

Quick Sort is a **Divide and Conquer** algorithm that picks a pivot and partitions the array such that elements smaller than pivot are on the left, larger on the right. It then recursively sorts the partitions.

### 🧰 Usage:

- Fastest average case sort
- Used in STL `std::sort()` (Introsort variant)

### 🧩 Algorithm Steps:

1. Choose pivot
2. Partition array
3. Recursively sort left and right parts

### 📟 Recursive Code:

```cpp
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
```

### 🔁 Iterative Code:

```cpp
void quickSortIterative(vector<int>& arr, int l, int h) {
    stack<pair<int, int>> stk;
    stk.push({l, h});
    while (!stk.empty()) {
        auto [low, high] = stk.top(); stk.pop();
        if (low < high) {
            int pi = partition(arr, low, high);
            stk.push({low, pi - 1});
            stk.push({pi + 1, high});
        }
    }
}
```

### ⏱️ Time Complexity:

- Best: **\Omega(n log n)**
- Average: **\Theta(n log n)**
- Worst: **O(n^2)**

### 🧮 Space Complexity:

- Worst-case stack: **O(n)**
- Average case: **O(log n)**

### ✅ Pros:

- In-place
- Faster in practice than Merge Sort

### ❌ Cons:

- Not stable
- Worst-case quadratic

### 🚀 Applications:

- Internal sorting
- STL `std::sort`

---

## ✅ 3. Counting Sort

### 🧠 Concept:

Counting Sort is a non-comparison-based sorting algorithm that works by counting the frequency of each element and placing them in the correct position.

### 📌 Usage:

- Only works for integers or discrete values within a known range.
- Best when input range is small.

### ⚙️ Algorithm:

1. Find the range (max value)
2. Create a count array and store frequency of each element
3. Transform count array to hold actual positions
4. Build output array using count array

### 💻 Code:

```cpp
void countingSort(vector<int>& arr) {
    int maxEl = *max_element(arr.begin(), arr.end());
    vector<int> count(maxEl + 1, 0);
    for (int x : arr) count[x]++;
    for (int i = 1; i <= maxEl; i++) count[i] += count[i - 1];
    vector<int> output(arr.size());
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    arr = output;
}
```

### ⏱ Time & Space Complexity:

- Time: O(n + k), where k is max value
- Space: O(n + k)
- Stable: Yes

### ✅ Pros:

- Linear time for small range
- Stable sort

### ❌ Cons:

- Not suitable for large range
- Only for integers

### 🔧 Applications:

- Sort grades, ages, fixed-range integers

---

## ✅ 4. Radix Sort

### 🧠 Concept:

Sort numbers digit-by-digit using Counting Sort as a subroutine. Works from Least Significant Digit (LSD) to Most.

### 📌 Usage:

- Works for fixed-length integers or strings
- Non-comparison-based

### ⚙️ Algorithm:

1. Find max number to determine digit count
2. Apply Counting Sort for each digit (LSD to MSD)

### 💻 Code:

```cpp
void countingSortExp(vector<int>& arr, int exp) {
    vector<int> output(arr.size());
    int count[10] = {0};
    for (int i = 0; i < arr.size(); i++) count[(arr[i]/exp)%10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i-1];
    for (int i = arr.size()-1; i >= 0; i--) {
        output[count[(arr[i]/exp)%10]-1] = arr[i];
        count[(arr[i]/exp)%10]--;
    }
    arr = output;
}

void radixSort(vector<int>& arr) {
    int maxEl = *max_element(arr.begin(), arr.end());
    for (int exp = 1; maxEl/exp > 0; exp *= 10)
        countingSortExp(arr, exp);
}
```

### ⏱ Time & Space Complexity:

- Time: O(n \* d) where d = number of digits
- Space: O(n + k)
- Stable: Yes

### ✅ Pros:

- Linear time if digit count is small

### ❌ Cons:

- Only works on fixed-length representations
- Extra space needed

### 🔧 Applications:

- Telephone numbers, zip codes, large ID arrays

---

## ✅ 5. Heap Sort

### 🧠 Concept:

Heap Sort uses a binary heap to repeatedly extract the maximum (or minimum) element and build a sorted array.

### 📌 Usage:

- In-place, comparison-based
- Efficient in scenarios requiring guaranteed O(n log n)

### ⚙️ Algorithm:

1. Build a max-heap
2. Extract max and heapify repeatedly

### 💻 Code:

```cpp
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n/2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
```

### ⏱ Time & Space Complexity:

- Time: O(n log n)
- Space: O(1)
- Stable: No

### ✅ Pros:

- No extra space
- Predictable worst-case time

### ❌ Cons:

- Not stable
- Slower than quicksort in practice

### 🔧 Applications:

- Priority queues
- Embedded systems

---

## ✅ 6. Bucket Sort

### 🧠 Concept:

Distribute elements into buckets, sort each bucket, then concatenate.

### 📌 Usage:

- Effective when input is uniformly distributed
- Works best on floating point numbers

### ⚙️ Algorithm:

1. Create buckets
2. Distribute elements
3. Sort each bucket
4. Concatenate all

### 💻 Code:

```cpp
void bucketSort(vector<float>& arr) {
    int n = arr.size();
    vector<vector<float>> buckets(n);
    for (int i = 0; i < n; i++) {
        int bi = n * arr[i];
        buckets[bi].push_back(arr[i]);
    }
    for (int i = 0; i < n; i++)
        sort(buckets[i].begin(), buckets[i].end());
    int idx = 0;
    for (int i = 0; i < n; i++)
        for (float x : buckets[i])
            arr[idx++] = x;
}
```

### ⏱ Time & Space Complexity:

- Time: O(n + k)
- Space: O(n)
- Stable: Depends on sorting inside bucket

### ✅ Pros:

- Fast for uniformly distributed input

### ❌ Cons:

- Overhead for bucket management
- Needs uniform distribution

### 🔧 Applications:

- Sorting floating point values in range [0, 1)

---

## ✅ 7. Cyclic Sort

### 🧠 Concept:

Place each element at its correct index assuming range is 0 to n-1 (or 1 to n).

### 📌 Usage:

- Detecting duplicates
- Finding missing numbers

### ⚙️ Algorithm:

1. Traverse the array
2. Swap elements to their correct positions

### 💻 Code:

```cpp
void cyclicSort(vector<int>& arr) {
    int i = 0;
    while (i < arr.size()) {
        int correct = arr[i] - 1;
        if (arr[i] != arr[correct])
            swap(arr[i], arr[correct]);
        else
            i++;
    }
}
```

### ⏱ Time & Space Complexity:

- Time: O(n)
- Space: O(1)
- Stable: No

### ✅ Pros:

- Constant space
- Linear time for specific input range

### ❌ Cons:

- Only works on continuous range data

### 🔧 Applications:

- Finding duplicates, missing numbers in array

---

## 📚 Section: Searching Algorithms

**🎯 Category:** Core Algorithms (Fundamentals You Must Know Cold)

This section covers the two most foundational and interview-relevant searching strategies:

- Binary Search (in both recursive and boundary forms)
- Ternary Search (for unimodal function optimization)

Each algorithm is explained in-depth, including concept, application, visual behavior, pseudocode, full C++ implementation, and analysis.

---

## 🔍 1. Binary Search

### 🧠 Concept:

Binary Search is a **Divide and Conquer** strategy. Given a **sorted** array, it efficiently narrows down the search space by half at each step.

### Key Idea:

In a sorted array:

- If `target == mid`, return it.
- If `target < mid`, search left half.
- If `target > mid`, search right half.

Works only if the array is **monotonic (non-decreasing or non-increasing)**.

### 🧰 Usage:

- Search for existence of a value
- Find lower/upper bounds, first/last occurrences
- Binary Search on answer in problems with monotonicity

---

### 🧩 Algorithm (Recursive):

```cpp
int binarySearchRecursive(vector<int>& arr, int low, int high, int target) {
    if (low > high) return -1;
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) return mid;
    else if (arr[mid] > target)
        return binarySearchRecursive(arr, low, mid - 1, target);
    else
        return binarySearchRecursive(arr, mid + 1, high, target);
}
```

### 🧩 Algorithm (Iterative – Boundary Style):

```cpp
int binarySearch(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
```

---

### ⏱️ Time Complexity:

- **Best Case (Ω):** O(1) if mid == target
- **Average Case (Θ):** Θ(log n)
- **Worst Case (O):** O(log n)

### 🧮 Space Complexity:

- Recursive: O(log n) (due to stack)
- Iterative: O(1)

### ✅ Pros:

- Extremely fast (logarithmic)
- Simple and widely applicable
- Works with minimal memory

### ❌ Cons:

- Requires sorted input
- Careful implementation needed to avoid off-by-one / overflow

### 🚀 Applications:

- Search operations in sorted arrays/lists
- Answer-based binary search in competitive programming
- Lower/upper bound queries
- Integer search over large range with decision predicate (e.g., capacity, feasibility, etc.)

---

## 🎯 2. Ternary Search

### 🧠 Concept:

Ternary Search is an optimization technique used on **unimodal functions** – where a function strictly increases then decreases (or vice versa). It finds the **maximum or minimum** in such a domain.

### Key Idea:

- Divide range into 3 parts: `m1`, `m2`
- Evaluate `f(m1)` and `f(m2)`
- Discard the worse half

Unimodal => only one local min or max ⇒ safe to ignore one segment entirely.

### 🧰 Usage:

- Optimization problems
- Continuous or discrete integer range
- Applicable to geometry, time-cost minimization

---

### 🧩 Algorithm (Double Precision / Continuous Domain):

```cpp
double ternarySearch(double l, double r, function<double(double)> f) {
    double eps = 1e-7;  // Required precision
    while (r - l > eps) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if (f(m1) < f(m2)) l = m1;  // If minimizing
        else r = m2;
    }
    return f(l); // or return l itself
}
```

### 🧩 Algorithm (Integer Domain):

```cpp
int ternarySearchInt(int l, int r, function<int(int)> f) {
    while (r - l > 3) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        if (f(m1) < f(m2)) l = m1;
        else r = m2;
    }
    int best = l;
    for (int i = l + 1; i <= r; ++i)
        if (f(i) < f(best)) best = i;
    return best;
}
```

---

### ⏱️ Time Complexity:

- **O(log n)** (base 1.5 ≈ tighter than binary search)

### 🧮 Space Complexity:

- O(1) (iterative)

### ✅ Pros:

- Works on real number domains (with eps)
- Precise for mathematical function minima/maxima
- Simple logic for unimodal problems

### ❌ Cons:

- Works **only on unimodal** functions
- Cannot be applied to arbitrary datasets

### 🚀 Applications:

- Geometry: Closest point, minimal distance
- Physics: Minimizing time, energy
- Discrete search when cost function is unimodal
- Competitive programming: function optimization on constraints

---

## 🧾 Section: Hashing

**🎯 Category:** Core Algorithms (Fundamentals You Must Know Cold)

Hashing provides **constant average time** operations (lookup, insert, delete) using a key-value mapping. Hash-based structures are core to efficient lookups, frequency counting, memoization, and more.

---

## 🗂️ 1. HashMap (Unordered Map)

### 🧠 Concept:

A **HashMap** is a key-value store using a hash function to index keys into buckets, allowing constant average-time operations.

### 🧰 Usage:

- Frequency count
- Caching results
- Maps with custom keys (e.g., pair, string)
- Memoization

### 🧩 Code (C++):

```cpp
unordered_map<string, int> freq;
freq["apple"]++;
cout << freq["apple"]; // 1
```

### ⏱️ Time Complexity:

- Best/Average (Ω/Θ): O(1)
- Worst (O): O(n) in case of collisions (rare in practice)

### 🧮 Space Complexity:

- O(n)

### ✅ Pros:

- Constant time lookup
- Built-in in most languages
- Versatile for key types

### ❌ Cons:

- No guaranteed order
- Can degrade to O(n)
- Not thread-safe

### 🚀 Applications:

- Frequency counting
- Memoization in DP
- Caching, LRU Cache
- Storing visited states

---

## 📚 2. HashSet (Unordered Set)

### 🧠 Concept:

A **HashSet** stores **only keys**, similar to a HashMap with `value = true`. Ensures uniqueness and allows quick lookup.

### 🧰 Usage:

- Track visited elements
- Detect duplicates
- Set union/intersection/difference

### 🧩 Code (C++):

```cpp
unordered_set<int> seen;
seen.insert(5);
if (seen.count(5)) cout << "Found";
```

### ⏱️ Time Complexity:

- Best/Average (Ω/Θ): O(1)
- Worst (O): O(n)

### 🧮 Space Complexity:

- O(n)

### ✅ Pros:

- Fast duplicate detection
- Cleaner interface for sets
- Uses hash map internally

### ❌ Cons:

- No order
- Hash collisions
- Cannot store duplicates

### 🚀 Applications:

- Remove duplicates
- Fast membership test
- Cycle detection in graphs
- Word search/dictionary lookup

---

## 🧪 3. Custom Hash Functions

### 🧠 Concept:

When default hash doesn't handle custom keys well (e.g., pair<int,int>, tuple, or when inputs are adversarial), define a **custom hash function**.

### 🧰 Usage:

- Hashing structs, pairs, or composite objects
- Avoiding collisions with large integers
- Competitive programming optimizations

### 🧩 Code (Custom Hash for pair<int,int>):

```cpp
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(pair<int,int> x) const {
        return splitmix64(x.first ^ (x.second << 32));
    }
};

// Usage:
unordered_map<pair<int,int>, int, custom_hash> mp;
```

### ⏱️ Time Complexity:

- Same as HashMap (O(1) avg)

### ✅ Pros:

- Avoids collisions
- Supports custom keys

### ❌ Cons:

- More verbose
- Debugging hash issues can be tricky

### 🚀 Applications:

- 2D grids
- Caching composite states
- Reducing TLEs in contests

---

## 🔁 4. Rolling Hash (Polynomial Hashing)

### 🧠 Concept:

A **rolling hash** is a hash function designed for **substring hashing** in constant time. Used in Rabin-Karp, string matching, and duplicate substring problems.

Hash of string:  
`H(s) = s[0] * p^0 + s[1] * p^1 + ... + s[n-1] * p^{n-1}` mod `MOD`  
Allows fast hash computation of substrings using prefix hashes.

### 🧰 Usage:

- Compare substrings efficiently
- Detect duplicate substrings
- Hashing entire ranges of strings

### 🧩 Code (Prefix Hash + Range Hash):

```cpp
const int P = 31; // or 131, 13331
const int MOD = 1e9 + 9;

vector<long long> p_pow, prefix;

void precompute_hash(const string &s) {
    int n = s.size();
    p_pow.resize(n+1, 1);
    prefix.resize(n+1, 0);
    for (int i = 1; i <= n; i++)
        p_pow[i] = (p_pow[i-1] * P) % MOD;
    for (int i = 0; i < n; i++)
        prefix[i+1] = (prefix[i] + (s[i] - 'a' + 1) * p_pow[i]) % MOD;
}

long long substring_hash(int l, int r) {
    return (prefix[r+1] - prefix[l] + MOD) * p_pow[prefix.size() - l - 1] % MOD;
}
```

### ⏱️ Time Complexity:

- Preprocessing: O(n)
- Hash query: O(1)

### 🧮 Space Complexity:

- O(n) for prefix and power arrays

### ✅ Pros:

- Fast substring comparison
- Useful for pattern matching
- Avoids string copies

### ❌ Cons:

- Collisions (rare but possible)
- Sensitive to base `P` and `MOD`
- Requires care for modular arithmetic

### 🚀 Applications:

- Rabin-Karp algorithm
- Longest common substring
- Detecting duplicate substrings
- Efficient suffix comparisons

---

## ⚡ Section: Greedy Algorithms

**🎯 Category:** Core Algorithms (Fundamentals You Must Know Cold)

Greedy algorithms build solutions **step-by-step**, always choosing the **locally optimal** move with the hope that it leads to a **globally optimal** solution. They are highly efficient and frequently used in scheduling, optimization, and graph problems.

---

## 🕒 1. Activity Selection Problem

### 🧠 Concept:

Given `n` activities with start and end times, select the **maximum number of non-overlapping activities**. Greedy solution chooses the activity with **earliest finishing time**.

### 🧰 Usage:

- Interval scheduling
- CPU/machine job scheduling
- Greedy foundation problem

### 🧩 Algorithm:

1. Sort activities by ending time.
2. Select the first activity.
3. For each next activity, if it starts after the last selected one ends, pick it.

### 📟 Code:

```cpp
bool comp(pair<int,int>& a, pair<int,int>& b) {
    return a.second < b.second; // sort by end time
}

int activitySelection(vector<pair<int,int>>& activities) {
    sort(activities.begin(), activities.end(), comp);
    int count = 1;
    int lastEnd = activities[0].second;

    for (int i = 1; i < activities.size(); i++) {
        if (activities[i].first >= lastEnd) {
            count++;
            lastEnd = activities[i].second;
        }
    }
    return count;
}
```

### ⏱️ Time Complexity:

- Sorting: **Θ(n log n)**
- Selection loop: **Θ(n)**

### 🧮 Space Complexity:

- O(1)

### ✅ Pros:

- Optimal for non-overlapping scheduling
- Very fast and intuitive
- Basis for complex interval problems

### ❌ Cons:

- Only works when greedy choice property is valid

### 🚀 Applications:

- Task scheduling
- Interval covering
- Event conflict resolution

---

## 🏗️ 2. Job Sequencing with Deadlines

### 🧠 Concept:

Given jobs with profits and deadlines, schedule them to maximize total profit. Each job takes 1 unit time and must be completed before its deadline.

### 🧰 Usage:

- CPU/OS task assignment
- Project delivery optimization

### 🧩 Algorithm:

1. Sort jobs by **profit descending**.
2. For each job, assign it to the latest available time slot before its deadline.

### 📟 Code:

```cpp
struct Job {
    int id, deadline, profit;
};

bool cmp(Job a, Job b) {
    return a.profit > b.profit;
}

int jobSequencing(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), cmp);
    int maxDeadline = 0;
    for (auto& job : jobs) maxDeadline = max(maxDeadline, job.deadline);

    vector<bool> slot(maxDeadline + 1, false);
    int totalProfit = 0;

    for (auto& job : jobs) {
        for (int t = job.deadline; t >= 1; t--) {
            if (!slot[t]) {
                slot[t] = true;
                totalProfit += job.profit;
                break;
            }
        }
    }
    return totalProfit;
}
```

### ⏱️ Time Complexity:

- Sorting: **Θ(n log n)**
- Slot finding: **O(n \* d)** (d = max deadline)

### 🧮 Space Complexity:

- O(d)

### ✅ Pros:

- Maximizes reward/profit
- Efficient greedy fit

### ❌ Cons:

- Each job takes 1 unit time
- May require union-find for O(log n) slot assignment

### 🚀 Applications:

- Deadline-bound scheduling
- Delivery optimization
- Job reward systems

---

## 🎒 3. Fractional Knapsack

### 🧠 Concept:

Maximize value for given weight capacity by taking **fractions** of items. Sort items by **value/weight ratio**.

### 🧰 Usage:

- Real-time data transfer
- Investment allocation

### 🧩 Algorithm:

1. Sort items by `value / weight` in descending order.
2. Take full items until full capacity, then fractionally take the next.

### 📟 Code:

```cpp
struct Item {
    int value, weight;
};

bool cmp(Item a, Item b) {
    return (double)a.value / a.weight > (double)b.value / b.weight;
}

double fractionalKnapsack(int capacity, vector<Item>& items) {
    sort(items.begin(), items.end(), cmp);
    double totalValue = 0;

    for (auto& item : items) {
        if (capacity >= item.weight) {
            totalValue += item.value;
            capacity -= item.weight;
        } else {
            totalValue += (double)item.value * capacity / item.weight;
            break;
        }
    }
    return totalValue;
}
```

### ⏱️ Time Complexity:

- Sorting: **Θ(n log n)**
- Fill loop: **Θ(n)**

### 🧮 Space Complexity:

- O(1)

### ✅ Pros:

- Maximizes utility/value
- Fast greedy solution

### ❌ Cons:

- Only works when fractional taking is allowed
- Cannot be used for 0/1 Knapsack

### 🚀 Applications:

- Logistics and shipment
- Bandwidth allocation
- Greedy budgeting

---

## 🧾 4. Huffman Coding

### 🧠 Concept:

Builds an optimal prefix code based on frequency of characters. Lower frequency → longer codes. Greedy approach using a priority queue.

### 🧰 Usage:

- Data compression (zip, jpeg, etc.)
- Entropy encoding in file systems

### 🧩 Algorithm:

1. Create a min-heap with frequencies.
2. While heap has >1 node:
   - Extract two smallest nodes.
   - Combine them into a new node.
   - Push combined node back into heap.
3. Final node is root of Huffman tree.

### 📟 Code:

```cpp
struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

Node* buildHuffmanTree(vector<pair<char, int>>& freqList) {
    priority_queue<Node*, vector<Node*>, compare> pq;
    for (auto& p : freqList)
        pq.push(new Node(p.first, p.second));

    while (pq.size() > 1) {
        Node* l = pq.top(); pq.pop();
        Node* r = pq.top(); pq.pop();
        Node* parent = new Node('$', l->freq + r->freq);
        parent->left = l;
        parent->right = r;
        pq.push(parent);
    }
    return pq.top(); // root of Huffman Tree
}
```

### ⏱️ Time Complexity:

- **Θ(n log n)** (heap operations)

### 🧮 Space Complexity:

- O(n) for tree and heap

### ✅ Pros:

- Produces optimal prefix code
- Widely used in real-world systems

### ❌ Cons:

- Requires tree traversal to decode
- Not suitable for dynamic streams (use arithmetic coding)

### 🚀 Applications:

- File compression (e.g., .zip, .gz)
- Network data encoding
- DNA sequence compression

---

## 🧠 Section: Bit Manipulation

**🎯 Category:** Core Algorithms (Fundamentals You Must Know Cold)

Bit manipulation is the art of using binary operators (AND, OR, XOR, SHIFT) to perform optimized operations on integers. It enables space-efficient and fast computations for mathematical, logical, and set-based problems.

---

## 🧮 1. Bitmasking

### 🧠 Concept:

Bitmasking uses bits to represent **states** (on/off) compactly. For example, `5` in binary `101` can represent a set containing indices {0, 2}. You can test, set, clear, or toggle any bit using bit operations.

### 🧰 Usage:

- Subset generation
- State DP (Bitmask DP)
- Representing sets (0-31 elements)
- Combinatorial problems (e.g., Traveling Salesman)

### 🧩 Common Operations:

```cpp
int x = 5; // 0101

x & (1 << i);    // Test i-th bit
x | (1 << i);    // Set i-th bit
x & ~(1 << i);   // Clear i-th bit
x ^ (1 << i);    // Toggle i-th bit
```

### 🧩 Subset Generation Example (0 to 2^n - 1):

```cpp
int n = 3;
for (int mask = 0; mask < (1 << n); mask++) {
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            cout << i << " ";
        }
    }
    cout << "\n";
}
```

### ⏱️ Time Complexity:

- Generating all subsets: **Θ(2ⁿ \* n)**

### ✅ Pros:

- Extremely fast set representation
- Space-efficient (32 or 64 bits)
- Enables elegant DP/state transitions

### ❌ Cons:

- Limited to ≤ 32 or 64 elements
- Logic can get tricky
- Debugging binary logic is hard

### 🚀 Applications:

- TSP, Subset Sum
- Bitmask DP
- K-subset problems

---

## 🔢 2. Counting Set Bits

### 🧠 Concept:

Count the number of `1`s in the binary representation of a number.

### 🧰 Usage:

- Population count
- Hamming weight/distance
- Preprocessing states
- Optimization decisions

### 🧩 Algorithms:

#### Method 1: Brian Kernighan's (Fast)

```cpp
int countSetBits(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1); // removes last set bit
        count++;
    }
    return count;
}
```

#### Method 2: \_\_builtin_popcount (GCC only)

```cpp
int count = __builtin_popcount(n);       // for int
int count64 = __builtin_popcountll(n);   // for long long
```

### ⏱️ Time Complexity:

- **Best/Avg/Worst (Θ/Ω/O):** O(k), where k = number of set bits
- Built-in: O(1) (hardware optimized)

### ✅ Pros:

- Essential in bitmask DP
- Prevalent in competitive problems

### ❌ Cons:

- Language/compiler dependent (for builtins)

### 🚀 Applications:

- Subset size
- Combinatorics
- Bit compression schemes

---

## ❌ 3. XOR Tricks

### 🧠 Concept:

XOR (`^`) is a bitwise operation where `a ^ b` flips the bits where `a` and `b` differ. It’s useful for **cancellation**, **toggle**, and **bit parity** logic.

### 🧰 Usage:

- Finding unique number
- Swapping without temp
- Prefix XOR trick
- Parity checks

### 🧩 Common Patterns:

#### a. Finding a Single Unique Element (All others appear twice)

```cpp
int findUnique(const vector<int>& arr) {
    int x = 0;
    for (int num : arr) x ^= num;
    return x;
}
```

#### b. XOR Swap

```cpp
a = a ^ b;
b = a ^ b;
a = a ^ b;
```

#### c. Prefix XOR Array

```cpp
vector<int> prefixXor(n+1, 0);
for (int i = 0; i < n; i++)
    prefixXor[i+1] = prefixXor[i] ^ arr[i];
```

### ⏱️ Time Complexity:

- **Θ(n)** for prefix XOR or finding unique

### 🧮 Space Complexity:

- O(n) if prefix array needed

### ✅ Pros:

- Clean logic for parity
- No extra space (in swap)
- Very fast (O(1))

### ❌ Cons:

- Can be unintuitive
- Only works in specific parity-based problems

### 🚀 Applications:

- XOR subarrays
- Leetcode/Codeforces "odd-one-out" problems
- Subset XOR sum
- Security + checksum computations

---

## 🔁 Section: Basic Recursion

**🎯 Category:** Core Algorithms (Fundamentals You Must Know Cold)

Recursion solves problems by breaking them into smaller subproblems and calling the same function recursively. It is the backbone of **backtracking**, **divide-and-conquer**, **DFS**, and **dynamic programming**.

---

## 🗼 1. Tower of Hanoi

### 🧠 Concept:

Move `n` disks from source rod to destination rod using an auxiliary rod. Only one disk can be moved at a time, and no disk can be placed on top of a smaller one.

This is a classic **divide-and-conquer** recursive problem.

### 🧰 Usage:

- Teaching recursion
- Demonstrating divide-and-conquer

### 🧩 Recursive Algorithm:

```cpp
void towerOfHanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        cout << "Move disk 1 from " << from << " to " << to << endl;
        return;
    }
    towerOfHanoi(n - 1, from, aux, to);
    cout << "Move disk " << n << " from " << from << " to " << to << endl;
    towerOfHanoi(n - 1, aux, to, from);
}
```

### ⏱️ Time Complexity:

- **Best/Avg/Worst (Θ, Ω, O):** Θ(2ⁿ)

### 🧮 Space Complexity:

- O(n) (call stack depth)

### ✅ Pros:

- Clear recursive logic
- Strong base case + divide step

### ❌ Cons:

- Exponential growth
- No iterative form

### 🚀 Applications:

- Stack recursion problems
- Proof-of-concept for recursion

---

## 🔄 2. Permutations of a String or Array

### 🧠 Concept:

Generate all permutations using **recursive backtracking** by swapping characters/elements in place.

### 🧰 Usage:

- Rearrangement problems
- Generating all orders/combinations

### 🧩 Optimized Recursive Algorithm (In-place):

```cpp
void permute(string &s, int l, int r) {
    if (l == r) {
        cout << s << endl;
        return;
    }
    unordered_set<char> used;
    for (int i = l; i <= r; i++) {
        if (used.count(s[i])) continue;  // optimization: skip duplicates
        used.insert(s[i]);
        swap(s[l], s[i]);
        permute(s, l + 1, r);
        swap(s[l], s[i]);  // backtrack
    }
}
```

### ⏱️ Time Complexity:

- **Θ(n × n!)** — total permutations of length `n`

### 🧮 Space Complexity:

- O(n) (call stack), plus O(n) extra for `used` set

### ✅ Pros:

- Backtrack optimized with pruning
- No extra array needed

### ❌ Cons:

- Costly for large inputs

### 🚀 Applications:

- Anagram problems
- Generating test cases
- Ordering search

---

## 📚 3. Subsets / Power Set

### 🧠 Concept:

Generate all possible subsets (power set) using **include/exclude** recursive pattern. Each element is either **included or excluded**, leading to `2ⁿ` subsets.

### 🧰 Usage:

- Subset sum
- DP initialization
- Backtracking states

### 🧩 Recursive Code:

```cpp
void generateSubsets(vector<int>& nums, int index, vector<int>& current) {
    if (index == nums.size()) {
        for (int val : current) cout << val << " ";
        cout << endl;
        return;
    }
    // Include nums[index]
    current.push_back(nums[index]);
    generateSubsets(nums, index + 1, current);
    current.pop_back();
    // Exclude nums[index]
    generateSubsets(nums, index + 1, current);
}
```

### 🧩 Iterative Code (Using Bitmask):

```cpp
void iterativeSubsets(vector<int>& nums) {
    int n = nums.size();
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) cout << nums[i] << " ";
        }
        cout << endl;
    }
}
```

### ⏱️ Time Complexity:

- Recursive: **Θ(2ⁿ)**
- Iterative: **Θ(2ⁿ \* n)**

### 🧮 Space Complexity:

- O(n) (stack or subset array)

### ✅ Pros:

- Recursive: simple and elegant
- Iterative: memory-safe and explicit

### ❌ Cons:

- Exponential growth

### 🚀 Applications:

- Knapsack variants
- Combinatorics
- Decision trees

---

## 🧭 4. Recursive Backtracking

### 🧠 Concept:

Backtracking is about exploring all valid configurations and **undoing** choices that lead to dead ends. It follows a recursive pattern with “make a choice, explore, undo choice.”

### 🧰 Usage:

- Constraint satisfaction
- AI game search
- Combinatorics

### 🧩 General Backtracking Template:

```cpp
void backtrack(vector<int>& state, int step) {
    if (is_solution(state)) {
        output(state);
        return;
    }
    for (int choice : get_choices(step)) {
        if (is_valid(state, choice)) {
            state.push_back(choice);
            backtrack(state, step + 1);
            state.pop_back();  // undo
        }
    }
}
```

### 🧩 Example: N-Queens Backtracking

```cpp
bool isSafe(vector<string>& board, int row, int col, int n) {
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') return false;
        if (col - (row - i) >= 0 && board[i][col - (row - i)] == 'Q') return false;
        if (col + (row - i) < n && board[i][col + (row - i)] == 'Q') return false;
    }
    return true;
}

void solveNQueens(int row, vector<string>& board, vector<vector<string>>& result, int n) {
    if (row == n) {
        result.push_back(board);
        return;
    }
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 'Q';
            solveNQueens(row + 1, board, result, n);
            board[row][col] = '.';  // backtrack
        }
    }
}
```

### ⏱️ Time Complexity:

- Varies: usually **Θ(Bⁿ)**, B = branching factor

### 🧮 Space Complexity:

- O(n) depth + O(n) board

### ✅ Pros:

- Explores all possible paths
- Works for constrained problems

### ❌ Cons:

- Can be slow (exponential)
- Needs pruning for efficiency

### 🚀 Applications:

- Sudoku solver
- Crossword builder
- Subset & permutation pruning

---

## Dynamic Programming

## 📚 Section: 1D Dynamic Programming (DP)

Dynamic Programming solves problems by **breaking them into overlapping subproblems** and **storing results** to avoid recomputation. 1D DP problems typically involve a single variable like index, position, or step count.

---

## 🔢 1. Fibonacci Numbers

### 🧠 Concept:

Compute the `n`th Fibonacci number:  
`F(n) = F(n-1) + F(n-2)` with base cases `F(0)=0`, `F(1)=1`.

### 🧰 Usage:

- Teaching recursion + memoization
- Base for many DP formulations

---

### Recursive (Exponential – Brute Force):

```cpp
int fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}
```

### Memoized Recursive (Top-down DP):

```cpp
int fibMemo(int n, vector<int>& dp) {
    if (n <= 1) return n;
    if (dp[n] != -1) return dp[n];
    return dp[n] = fibMemo(n-1, dp) + fibMemo(n-2, dp);
}
```

### Tabulation (Bottom-up):

```cpp
int fibTab(int n) {
    vector<int> dp(n+1);
    dp[0] = 0; dp[1] = 1;
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i-1] + dp[i-2];
    return dp[n];
}
```

### Space Optimized:

```cpp
int fibOpt(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        int c = a + b;
        a = b;
        b = c;
    }
    return b;
}
```

### ⏱️ Time Complexity:

- Brute: **Θ(2ⁿ)**
- Memo / Tabulation / Optimized: **Θ(n)**

### 🧮 Space Complexity:

- Recursive: O(n) (stack)
- Tabulation: O(n)
- Optimized: O(1)

---

## 🪜 2. Climbing Stairs

### 🧠 Concept:

You can climb 1 or 2 steps at a time. Count number of distinct ways to climb to the top (n steps).  
Essentially: `ways(n) = ways(n-1) + ways(n-2)`

### 🧰 Usage:

- Introduction to recurrence + DP
- Paths, steps, ladders

---

### Tabulated Approach:

```cpp
int climbStairs(int n) {
    if (n <= 2) return n;
    int a = 1, b = 2;
    for (int i = 3; i <= n; i++) {
        int c = a + b;
        a = b;
        b = c;
    }
    return b;
}
```

### ⏱️ Time Complexity:

- **Θ(n)**

### 🧮 Space Complexity:

- O(1)

### ✅ Pros:

- Simple DP transition
- Same as Fibonacci

### 🚀 Applications:

- Variants: k steps, obstacles, variable jumps

---

## 📈 3. Longest Increasing Subsequence (LIS)

### 🧠 Concept:

Find the **length** of the longest strictly increasing subsequence in an array.

### 🧰 Usage:

- Subsequence analysis
- Stock prices, versioning, grading systems

---

### Brute Force (Recursive):

```cpp
int lis(int i, int prev, vector<int>& nums) {
    if (i == nums.size()) return 0;
    int take = 0;
    if (nums[i] > prev)
        take = 1 + lis(i + 1, nums[i], nums);
    int notTake = lis(i + 1, prev, nums);
    return max(take, notTake);
}
```

### DP Tabulated (O(n²)):

```cpp
int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1);
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (nums[i] > nums[j])
                dp[i] = max(dp[i], dp[j] + 1);
    return *max_element(dp.begin(), dp.end());
}
```

### Optimized (O(n log n)) – Patience Sorting:

```cpp
int lengthOfLIS(vector<int>& nums) {
    vector<int> tails;
    for (int num : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), num);
        if (it == tails.end()) tails.push_back(num);
        else *it = num;
    }
    return tails.size();
}
```

### ⏱️ Time Complexity:

- Brute: **Θ(2ⁿ)**
- DP: **Θ(n²)**
- Optimized: **Θ(n log n)**

### 🧮 Space Complexity:

- DP: O(n)

### ✅ Pros:

- Strong example of DP + binary search
- Foundational for advanced LIS variations

### ❌ Cons:

- Requires intuition + multiple methods

### 🚀 Applications:

- Sequence compression
- Event scheduling
- Sorting violations

---

## 📉 4. Maximum Subarray (Kadane's Algorithm)

### 🧠 Concept:

Find the **maximum sum** of a contiguous subarray in a given array (can include negatives).

### 🧰 Usage:

- Stock trading (max profit)
- Heatmap / signal processing

---

### Kadane’s Algorithm:

```cpp
int maxSubArray(vector<int>& nums) {
    int maxSum = nums[0], curSum = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        curSum = max(nums[i], curSum + nums[i]);
        maxSum = max(maxSum, curSum);
    }
    return maxSum;
}
```

### ⏱️ Time Complexity:

- **Θ(n)**

### 🧮 Space Complexity:

- O(1)

### ✅ Pros:

- Optimal and clean
- Linear time, no DP table needed

### ❌ Cons:

- Doesn’t return the subarray itself (needs tracking)

### 🚀 Applications:

- Financial data
- Genomic sequence scoring
- Max window problems

---

## 🧮 Section: 2D Dynamic Programming (DP)

**🎯 Category:** Dynamic Programming

2D DP problems involve **two input dimensions** (like indices `i` and `j` of two strings, or coordinates in a grid). The state depends on a 2D array where `dp[i][j]` represents an answer to a subproblem involving the first `i` and `j` elements or rows/columns.

---

## 🧭 1. Unique Paths in a Grid

### 🧠 Concept:

Given an `m x n` grid, count how many unique paths exist from **top-left** to **bottom-right**, moving only **right or down**.

### 🧰 Usage:

- Robot path planning
- Grid traversal
- Combinatorial counting

---

### Recursive + Memoization:

```cpp
int uniquePathsMemo(int m, int n, vector<vector<int>>& dp) {
    if (m == 0 || n == 0) return 0;
    if (m == 1 && n == 1) return 1;
    if (dp[m][n] != -1) return dp[m][n];
    return dp[m][n] = uniquePathsMemo(m-1, n, dp) + uniquePathsMemo(m, n-1, dp);
}
```

### Iterative Tabulation:

```cpp
int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 1));
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++)
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
    }
    return dp[m-1][n-1];
}
```

### Space Optimized:

```cpp
int uniquePaths(int m, int n) {
    vector<int> prev(n, 1);
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++)
            prev[j] += prev[j-1];
    }
    return prev[n-1];
}
```

### ⏱️ Time Complexity:

- Recursive: **Θ(2^(m+n))**
- DP: **Θ(m × n)**

### 🧮 Space Complexity:

- Tabulated: O(m × n)
- Optimized: O(n)

---

## 📘 2. Longest Common Subsequence (LCS)

### 🧠 Concept:

Given two strings `A` and `B`, find the **length** of the longest subsequence present in **both**. Characters must appear in order but not necessarily contiguously.

### 🧰 Usage:

- DNA/sequence comparison
- Diff tools (git diff)
- Edit distance foundation

---

### Recursive + Memoization:

```cpp
int lcsMemo(int i, int j, string &a, string &b, vector<vector<int>>& dp) {
    if (i == 0 || j == 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    if (a[i-1] == b[j-1])
        return dp[i][j] = 1 + lcsMemo(i-1, j-1, a, b, dp);
    return dp[i][j] = max(lcsMemo(i-1, j, a, b, dp), lcsMemo(i, j-1, a, b, dp));
}
```

### Iterative Tabulation:

```cpp
int lcsTab(string &a, string &b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i-1] == b[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    return dp[n][m];
}
```

### Space Optimized:

```cpp
int lcsOpt(string &a, string &b) {
    int n = a.size(), m = b.size();
    vector<int> prev(m+1, 0), curr(m+1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1])
                curr[j] = 1 + prev[j-1];
            else
                curr[j] = max(prev[j], curr[j-1]);
        }
        swap(prev, curr);
    }
    return prev[m];
}
```

### ⏱️ Time Complexity:

- **Θ(n × m)**

### 🧮 Space Complexity:

- Tabulated: O(n × m)
- Optimized: O(m)

---

## ✏️ 3. Edit Distance (Levenshtein Distance)

### 🧠 Concept:

Find the **minimum number of operations** (insert, delete, replace) to convert string `A` to string `B`.

### 🧰 Usage:

- Spell checkers
- DNA comparison
- Auto-correct

---

### Recursive + Memoization:

```cpp
int editDist(int i, int j, string &a, string &b, vector<vector<int>>& dp) {
    if (i == 0) return j;
    if (j == 0) return i;
    if (dp[i][j] != -1) return dp[i][j];
    if (a[i-1] == b[j-1])
        return dp[i][j] = editDist(i-1, j-1, a, b, dp);
    int insert = 1 + editDist(i, j-1, a, b, dp);
    int del = 1 + editDist(i-1, j, a, b, dp);
    int replace = 1 + editDist(i-1, j-1, a, b, dp);
    return dp[i][j] = min({insert, del, replace});
}
```

### Tabulation:

```cpp
int editDistTab(string &a, string &b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i][j-1], dp[i-1][j], dp[i-1][j-1]});
        }
    }
    return dp[n][m];
}
```

### ⏱️ Time Complexity:

- **Θ(n × m)**

### 🧮 Space Complexity:

- O(n × m)

---

## 🔗 4. Matrix Chain Multiplication (MCM)

### 🧠 Concept:

Given an array `arr[]` of size `n` where the `i`th matrix has dimensions `arr[i-1] x arr[i]`, find the **minimum number of scalar multiplications** needed to multiply the chain.

### 🧰 Usage:

- Optimal parenthesization
- Parsing expressions

---

### Recursive + Memoization:

```cpp
int mcm(int i, int j, vector<int>& arr, vector<vector<int>>& dp) {
    if (i == j) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    int ans = INT_MAX;
    for (int k = i; k < j; k++) {
        int cost = mcm(i, k, arr, dp) + mcm(k+1, j, arr, dp) + arr[i-1]*arr[k]*arr[j];
        ans = min(ans, cost);
    }
    return dp[i][j] = ans;
}
```

### Tabulation (Bottom-up):

```cpp
int matrixChain(vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int len = 2; len < n; len++) {
        for (int i = 1; i < n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] + arr[i-1]*arr[k]*arr[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return dp[1][n-1];
}
```

### ⏱️ Time Complexity:

- **Θ(n³)**

### 🧮 Space Complexity:

- O(n²)

### ✅ Pros:

- Classic recursive + DP example
- Substructure + overlapping optimality

### ❌ Cons:

- No iterative version with O(n² log n)

### 🚀 Applications:

- Matrix chain products
- Polynomial evaluation
- Expression parsing

---

## 🎒 Section: Knapsack Problems

**🎯 Category:** Dynamic Programming

Knapsack-type problems involve selecting items with weights and values to **maximize value under constraints**, typically using dynamic programming to evaluate all viable sub-solutions.

---

## 🧳 1. 0/1 Knapsack

### 🧠 Concept:

Given `n` items with `weight[i]` and `value[i]`, and a knapsack of capacity `W`, maximize total value.  
Each item can be picked **at most once** (0 or 1 times).

### 🧰 Usage:

- Budget planning
- Subset selection under constraints

---

### Recursive + Memoization:

```cpp
int knapsack(int i, int W, vector<int>& wt, vector<int>& val, vector<vector<int>>& dp) {
    if (i == 0)
        return (wt[0] <= W) ? val[0] : 0;
    if (dp[i][W] != -1) return dp[i][W];

    int notTake = knapsack(i-1, W, wt, val, dp);
    int take = (wt[i] <= W) ? val[i] + knapsack(i-1, W-wt[i], wt, val, dp) : 0;

    return dp[i][W] = max(take, notTake);
}
```

### Iterative Tabulation:

```cpp
int knapsackTab(int n, int W, vector<int>& wt, vector<int>& val) {
    vector<vector<int>> dp(n, vector<int>(W+1, 0));
    for (int w = wt[0]; w <= W; w++)
        dp[0][w] = val[0];

    for (int i = 1; i < n; i++) {
        for (int w = 0; w <= W; w++) {
            int notTake = dp[i-1][w];
            int take = (wt[i] <= w) ? val[i] + dp[i-1][w-wt[i]] : 0;
            dp[i][w] = max(take, notTake);
        }
    }
    return dp[n-1][W];
}
```

### Space Optimized:

```cpp
int knapsackSpace(int n, int W, vector<int>& wt, vector<int>& val) {
    vector<int> prev(W+1, 0);
    for (int w = wt[0]; w <= W; w++) prev[w] = val[0];

    for (int i = 1; i < n; i++) {
        for (int w = W; w >= 0; w--) {
            int notTake = prev[w];
            int take = (wt[i] <= w) ? val[i] + prev[w-wt[i]] : 0;
            prev[w] = max(take, notTake);
        }
    }
    return prev[W];
}
```

### ⏱️ Time Complexity:

- **Θ(n × W)**

### 🧮 Space Complexity:

- Tabulated: O(n × W)
- Optimized: O(W)

---

## 🔁 2. Unbounded Knapsack

### 🧠 Concept:

Same as 0/1 Knapsack, but **you can take unlimited instances** of each item.

### 🧰 Usage:

- Rod cutting
- Coin change

---

### Tabulated Version:

```cpp
int unboundedKnapsack(int n, int W, vector<int>& wt, vector<int>& val) {
    vector<int> dp(W+1, 0);
    for (int w = 0; w <= W; w++) {
        for (int i = 0; i < n; i++) {
            if (wt[i] <= w)
                dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
        }
    }
    return dp[W];
}
```

### ⏱️ Time Complexity:

- **Θ(n × W)**

### 🧮 Space Complexity:

- O(W)

### ✅ Pros:

- Solves unlimited-use item cases

### 🚀 Applications:

- Coin Change (min ways)
- Cutting problems

---

## 🔢 3. Bounded Knapsack (Limited Item Count)

### 🧠 Concept:

Each item has a limit `count[i]` on how many times it can be chosen.

### 🧰 Usage:

- Item stock with constraints
- Realistic resource-limited packing

---

### Tabulated Version:

```cpp
int boundedKnapsack(int n, int W, vector<int>& wt, vector<int>& val, vector<int>& count) {
    vector<int> dp(W+1, 0);
    for (int i = 0; i < n; i++) {
        for (int w = W; w >= 0; w--) {
            for (int k = 1; k <= count[i]; k++) {
                if (k * wt[i] <= w)
                    dp[w] = max(dp[w], k * val[i] + dp[w - k * wt[i]]);
                else
                    break;
            }
        }
    }
    return dp[W];
}
```

### ⏱️ Time Complexity:

- Worst: **Θ(n × W × max_count)**

### 🧮 Space Complexity:

- O(W)

---

## 🧱 4. Multidimensional Knapsack

### 🧠 Concept:

Each item has multiple constraints (e.g., **weight and volume**). Goal is to **maximize value** under **multiple capacities**.

### 🧰 Usage:

- Cloud resource planning
- Multi-constrained optimization

---

### Tabulation (2D):

```cpp
int multiKnapsack(int n, int W, int V, vector<int>& wt, vector<int>& vol, vector<int>& val) {
    vector<vector<int>> dp(W+1, vector<int>(V+1, 0));
    for (int i = 0; i < n; i++) {
        for (int w = W; w >= wt[i]; w--) {
            for (int v = V; v >= vol[i]; v--) {
                dp[w][v] = max(dp[w][v], val[i] + dp[w - wt[i]][v - vol[i]]);
            }
        }
    }
    return dp[W][V];
}
```

### ⏱️ Time Complexity:

- **Θ(n × W × V)**

### 🧮 Space Complexity:

- O(W × V)

---

### ✅ Pros:

- Models real-world packing constraints

### ❌ Cons:

- High dimensional DP = large memory usage

---

## 🧮 Section: Bitmask Dynamic Programming (Bitmask DP)

**🎯 Category:** Advanced Dynamic Programming

Bitmask DP is used when the **state space is exponential (2ⁿ subsets)** but can be encoded compactly using **bitmasks**, allowing efficient DP memoization or tabulation.

---

## 🧳 1. Traveling Salesman Problem (TSP)

### 🧠 Concept:

Find the **minimum cost** to visit all cities exactly once and return to the starting city.

Given a distance matrix `dist[i][j]` for a complete graph of `n` cities, compute the minimal cost tour.

### 🧰 Usage:

- Routing and logistics
- Path optimization
- Circuit design

---

### Recursive + Bitmask Memoization:

```cpp
const int INF = 1e9;
int tsp(int mask, int pos, vector<vector<int>>& dist, vector<vector<int>>& dp, int n) {
    if (mask == (1 << n) - 1) return dist[pos][0]; // All visited

    if (dp[mask][pos] != -1) return dp[mask][pos];

    int ans = INF;
    for (int city = 0; city < n; city++) {
        if (!(mask & (1 << city))) {
            int newCost = dist[pos][city] + tsp(mask | (1 << city), city, dist, dp, n);
            ans = min(ans, newCost);
        }
    }
    return dp[mask][pos] = ans;
}
```

### Initialization:

```cpp
int solveTSP(vector<vector<int>>& dist) {
    int n = dist.size();
    vector<vector<int>> dp(1 << n, vector<int>(n, -1));
    return tsp(1, 0, dist, dp, n); // Start at city 0, mask = 000...1
}
```

### ⏱️ Time Complexity:

- **Θ(n² × 2ⁿ)** — each subset × each node
- **Ω(n × 2ⁿ)** — best case, still exponential

### 🧮 Space Complexity:

- O(n × 2ⁿ)

### ✅ Pros:

- Elegant, clean solution to TSP
- Bitmasking ensures compact representation

### ❌ Cons:

- Not scalable for n > 20

---

## 🔣 2. Subset DP

### 🧠 Concept:

Solve problems where each DP state depends on a subset of items. Use **bitmasks (integers)** to represent subsets of size `n` (from 0 to 2ⁿ - 1).

### 🧰 Usage:

- Counting valid assignments
- Minimizing/maximizing over subsets
- Team selections, graph coloring

---

### Example: Sum of Subset Min Costs

```cpp
int subsetDP(vector<int>& cost, int n) {
    int total = 1 << n;
    vector<int> dp(total, INT_MAX);
    dp[0] = 0; // Empty set

    for (int mask = 1; mask < total; mask++) {
        for (int j = 0; j < n; j++) {
            if (mask & (1 << j)) {
                int prevMask = mask ^ (1 << j);
                dp[mask] = min(dp[mask], dp[prevMask] + cost[j]);
            }
        }
    }
    return dp[total - 1];
}
```

### Common Transition:

- Use `mask ^ (1 << i)` to remove an element
- Use `mask | (1 << i)` to add an element
- Iterate over submasks with:

```cpp
for (int submask = mask; submask; submask = (submask - 1) & mask) {
    // process submask
}
```

### ⏱️ Time Complexity:

- **Θ(2ⁿ × n)**

### 🧮 Space Complexity:

- O(2ⁿ)

---

### ✅ Pros:

- Efficient for subset-heavy problems
- Great for team DP, state compression

### ❌ Cons:

- Requires good understanding of bit operations
- Not scalable beyond ~20 elements

---

## 🌲 Section: Tree Dynamic Programming (Tree DP)

**🎯 Category:** Advanced Dynamic Programming

Tree DP is used to compute optimal results over tree structures (acyclic connected graphs) using **DFS-based recursion**. The main patterns are:

- **Post-order DP** (bottom-up): compute values from children up to the root.
- **Rerooting DP** (top-down): efficiently compute DP for all roots using results from one root.

---

## 🧩 1. DP on Post-order (Subtree DP)

### 🧠 Concept:

Perform DFS from the root. After visiting all children of a node, compute the result for the current node using its children's results.

### 🧰 Usage:

- Maximum subtree sum
- Diameter of tree
- Subtree size/count/depth

---

### Example: Largest Subtree Sum

```cpp
int maxSubtree = INT_MIN;

int dfs(int node, int parent, vector<vector<int>>& adj, vector<int>& val) {
    int sum = val[node];
    for (int child : adj[node]) {
        if (child != parent)
            sum += dfs(child, node, adj, val);
    }
    maxSubtree = max(maxSubtree, sum);
    return sum;
}
```

### Example: Diameter of Tree (Post-order)

```cpp
int diameter = 0;

int dfs(int node, int parent, vector<vector<int>>& adj) {
    int max1 = 0, max2 = 0;
    for (int child : adj[node]) {
        if (child != parent) {
            int depth = dfs(child, node, adj) + 1;
            if (depth > max1) swap(depth, max1);
            if (depth > max2) max2 = depth;
        }
    }
    diameter = max(diameter, max1 + max2);
    return max1;
}
```

### ⏱️ Time Complexity:

- **Θ(n)** — single DFS

### 🧮 Space Complexity:

- O(n) (recursion + adjacency list)

### ✅ Pros:

- Simple to implement
- Optimal for subtree-based results

### ❌ Cons:

- Only works for root-centric computations

---

## 🔁 2. Rerooting DP

### 🧠 Concept:

You precompute results for one root using post-order DP, then **reroot** the tree recursively by transferring values between parent and child.

Useful for:

- DP results needed for **every possible root**
- Global optimization over rooted trees

---

### Example: Sum of Distances to All Nodes

Let:

- `dp[u]` = sum of distances from node `u` to all its descendants
- `sz[u]` = size of subtree rooted at `u`

### Step 1: Post-order DP

```cpp
void dfs1(int u, int p, vector<vector<int>>& adj, vector<int>& dp, vector<int>& sz) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs1(v, u, adj, dp, sz);
        sz[u] += sz[v];
        dp[u] += dp[v] + sz[v];
    }
}
```

### Step 2: Rerooting

```cpp
void dfs2(int u, int p, vector<vector<int>>& adj, vector<int>& dp, vector<int>& sz) {
    for (int v : adj[u]) {
        if (v == p) continue;

        dp[v] = dp[u] - sz[v] + (sz.size() - sz[v]);
        dfs2(v, u, adj, dp, sz);
    }
}
```

### Initialization:

```cpp
int n = adj.size();
vector<int> dp(n, 0), sz(n, 0);
dfs1(0, -1, adj, dp, sz); // compute for root
dfs2(0, -1, adj, dp, sz); // reroot
```

### ⏱️ Time Complexity:

- **Θ(n)** — each edge processed once in both dfs1 and dfs2

### 🧮 Space Complexity:

- O(n)

### ✅ Pros:

- Computes answer for all possible roots in linear time
- Very elegant once understood

### ❌ Cons:

- Logic is tricky and unintuitive
- Careful handling of sizes and transitions needed

---

## 🧠 Section: Memoization Strategies

**🎯 Category:** Dynamic Programming Techniques

Memoization stores the results of expensive function calls based on **state parameters** to avoid recomputation. When problems involve **multiple state variables** or subsets, we use either **tuples** or **bitmasks** as keys in hash maps or DP tables.

---

## 🧩 1. Memoization Using State Tuples

### 🧠 Concept:

Use **`unordered_map<tuple<...>, int>`** or nested arrays to store computed results for a function with **multiple arguments**.

### 🧰 Usage:

- Multi-variable DP problems
- Recursion with changing indices, counts, flags

---

### Example: Palindrome Partitioning (i, j, isPalindrome)

```cpp
unordered_map<tuple<int, int, bool>, int> dp;

int solve(int i, int j, bool flag, string& s) {
    auto state = make_tuple(i, j, flag);
    if (dp.count(state)) return dp[state];

    // base case logic...

    return dp[state] = ...;
}
```

### Cleaner Alternative (C++17 or higher):

```cpp
map<tuple<int, int, bool>, int> memo;
```

### ⏱️ Time Complexity:

- Depends on number of valid `(i, j, flag)` states
- For 2D: **Θ(n²)**
- For 3D: **Θ(n³)** if all states used

### 🧮 Space Complexity:

- O(# of unique state tuples)

### ✅ Pros:

- Flexible for any number/type of parameters
- Intuitive and readable

### ❌ Cons:

- Slightly slower due to hashing tuples
- Can grow large if not pruned

---

## 🔣 2. Memoization Using Bitmask

### 🧠 Concept:

Use an `int` to represent a **bitmask of used elements**, typically in **subset** or **permutation** problems. Combine this with other state variables like current position.

### 🧰 Usage:

- Traveling Salesman Problem
- Subset DP
- Assignment problems

---

### Example: Count Valid Permutations

```cpp
int dp[1 << 15][15]; // memo[mask][pos]

int solve(int mask, int pos, vector<vector<int>>& valid) {
    if (mask == (1 << valid.size()) - 1) return 1;
    if (dp[mask][pos] != -1) return dp[mask][pos];

    int res = 0;
    for (int i = 0; i < valid.size(); i++) {
        if (!(mask & (1 << i)) && valid[pos][i])
            res += solve(mask | (1 << i), i, valid);
    }
    return dp[mask][pos] = res;
}
```

### ⏱️ Time Complexity:

- **Θ(n × 2ⁿ)**
- Each subset × each position

### 🧮 Space Complexity:

- O(n × 2ⁿ)

### ✅ Pros:

- Efficient for small n ≤ 20
- Avoids unordered_map overhead

### ❌ Cons:

- Not applicable for large `n`
- Logic is harder to debug

---

## 🧮 Summary Table

| Strategy     | When to Use                 | Time       | Space      | Pros                         | Cons                      |
| ------------ | --------------------------- | ---------- | ---------- | ---------------------------- | ------------------------- |
| State Tuples | Multiple unrelated params   | Θ(#states) | O(#states) | Flexible, readable           | May be slower, hash-heavy |
| Bitmask Memo | Subset/Permutation tracking | Θ(n × 2ⁿ)  | O(n × 2ⁿ)  | Fast lookup, space-efficient | Only works for n ≤ 20     |

---

## 🚀 Section: DP Optimization Techniques

**🎯 Category:** Advanced DP Optimizations

Some dynamic programming problems have naïve solutions with **Θ(n²)** or worse complexity. These **optimization techniques** exploit the properties of the recurrence or monotonicity to reduce the complexity significantly.

---

## 🪟 1. Sliding Window Optimization

### 🧠 Concept:

If your DP recurrence is of the form:

```
dp[i] = min(dp[i-k] + cost), for k in [1, W]
```

Then you can maintain the best values in a sliding window (usually using deque or prefix sums) to optimize to O(n).

### 🧰 Usage:

- Maximum/Minimum in last W elements
- K-sized intervals
- DP with fixed-range dependency

---

### Example: Max Sum of Sliding Window Size `k`

```cpp
int maxSlidingWindowSum(vector<int>& nums, int k) {
    deque<int> dq;
    int n = nums.size();
    vector<int> dp(n);

    for (int i = 0; i < n; i++) {
        if (!dq.empty() && dq.front() < i - k) dq.pop_front();

        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        dq.push_back(i);

        dp[i] = nums[dq.front()];
    }
    return *max_element(dp.begin(), dp.end());
}
```

### ⏱️ Time Complexity:

- **Θ(n)**

### 🧮 Space Complexity:

- O(k)

### ✅ Pros:

- Great for fixed window transitions
- Efficient linear time implementation

### ❌ Cons:

- Only works for monotonic transitions

---

## 📉 2. Monotonic Queue Optimization

### 🧠 Concept:

Used when the DP state transition is **monotonic** (increasing or decreasing). We can maintain a monotonic deque to get the min/max in O(1) amortized time.

### 🧰 Usage:

- Convex/concave optimization
- Linearly sliding window over convex values

---

### Example: Sliding Window Minimum DP

```cpp
void monotonicQueueDP(vector<int>& cost, int k) {
    int n = cost.size();
    deque<int> dq;
    vector<int> dp(n);

    for (int i = 0; i < n; i++) {
        if (!dq.empty() && dq.front() < i - k) dq.pop_front();
        while (!dq.empty() && dp[dq.back()] >= dp[i]) dq.pop_back();
        dq.push_back(i);

        dp[i] = cost[i] + dp[dq.front()];
    }
}
```

### ⏱️ Time Complexity:

- **Θ(n)**

### 🧮 Space Complexity:

- O(k)

### ✅ Pros:

- Powerful in time-series/interval DP
- Simple once learned

### ❌ Cons:

- Requires special monotonic structure

---

## 🪓 3. Divide and Conquer Optimization

### 🧠 Concept:

If your DP recurrence is of the form:

```
dp[i] = min_{k < i} (dp[k] + C(k, i))
```

and **C(a, c) + C(b, d) ≤ C(a, d) + C(b, c)** for all `a ≤ b ≤ c ≤ d`  
(Quadrangle Inequality + Monotonicity of Optimal `k`),  
then you can solve using divide & conquer in O(n log n).

---

### 🧰 Usage:

- Knuth’s optimization
- Matrix Chain Multiplication
- MCM, Range DP

---

### Recursive D&C Optimization:

```cpp
void compute(int l, int r, int optL, int optR, vector<int>& dp, vector<int>& prev) {
    if (l > r) return;
    int mid = (l + r) / 2;
    pair<int, int> best = {INT_MAX, -1};

    for (int k = optL; k <= min(mid, optR); k++) {
        int cost = prev[k] + C(k, mid); // define your cost
        if (cost < best.first)
            best = {cost, k};
    }

    dp[mid] = best.first;
    int optM = best.second;

    compute(l, mid - 1, optL, optM, dp, prev);
    compute(mid + 1, r, optM, optR, dp, prev);
}
```

### ⏱️ Time Complexity:

- **Θ(n log n)** or **Θ(k × n log n)**

### 🧮 Space Complexity:

- O(n)

---

### ✅ Pros:

- Reduces quadratic DP to log factor
- Crucial in high-constraint problems

### ❌ Cons:

- Requires strict recurrence conditions
- Error-prone if cost function assumptions fail

---

## 🧮 Summary Table

| Technique              | Applicable Recurrence              | Time       | Space | Best Use Case                            |
| ---------------------- | ---------------------------------- | ---------- | ----- | ---------------------------------------- |
| Sliding Window         | `dp[i] = f(dp[i-k..i-1])`          | Θ(n)       | O(k)  | Fixed range dependency                   |
| Monotonic Queue        | Monotonic transition cost          | Θ(n)       | O(k)  | Time-series DP with min/max requirements |
| Divide & Conquer (D&C) | Convex/Quadrangle inequality holds | Θ(n log n) | O(n)  | Range DP / Knuth / Segment recurrence    |

---

## Tree Algorithms

## 🌲 Section: Tree Traversals

Traversing trees is the foundation for many tree-related algorithms. Each traversal follows a specific node visiting order and is useful for different types of tree operations.

---

## 🔁 1. Preorder Traversal

### 🧠 Concept:

Visit: **Root → Left → Right**

### 🔧 Recursive:

```cpp
void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}
```

### 🔧 Iterative:

```cpp
void preorderIter(TreeNode* root) {
    stack<TreeNode*> st;
    if (root) st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top(); st.pop();
        cout << node->val << " ";
        if (node->right) st.push(node->right);
        if (node->left) st.push(node->left);
    }
}
```

---

## 🔁 2. Inorder Traversal

### 🧠 Concept:

Visit: **Left → Root → Right**

### 🔧 Recursive:

```cpp
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}
```

### 🔧 Iterative:

```cpp
void inorderIter(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* curr = root;
    while (curr || !st.empty()) {
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top(); st.pop();
        cout << curr->val << " ";
        curr = curr->right;
    }
}
```

---

## 🔁 3. Postorder Traversal

### 🧠 Concept:

Visit: **Left → Right → Root**

### 🔧 Recursive:

```cpp
void postorder(TreeNode* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
}
```

### 🔧 Iterative:

```cpp
void postorderIter(TreeNode* root) {
    stack<TreeNode*> st1, st2;
    if (root) st1.push(root);
    while (!st1.empty()) {
        TreeNode* node = st1.top(); st1.pop();
        st2.push(node);
        if (node->left) st1.push(node->left);
        if (node->right) st1.push(node->right);
    }
    while (!st2.empty()) {
        cout << st2.top()->val << " ";
        st2.pop();
    }
}
```

---

## 🌐 4. Level-order Traversal (BFS)

### 🧠 Concept:

Visit nodes **level by level** using a queue.

### 🔧 BFS Approach:

```cpp
void levelOrder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front(); q.pop();
        cout << node->val << " ";
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}
```

---

## ✂️ 5. Morris Inorder Traversal (O(1) Space)

### 🧠 Concept:

- Uses **threaded binary tree** structure.
- Temporarily modifies the tree to avoid stack/recursion.

### 🔧 Code:

```cpp
void morrisInorder(TreeNode* root) {
    TreeNode* curr = root;
    while (curr) {
        if (!curr->left) {
            cout << curr->val << " ";
            curr = curr->right;
        } else {
            TreeNode* pred = curr->left;
            while (pred->right && pred->right != curr)
                pred = pred->right;

            if (!pred->right) {
                pred->right = curr;
                curr = curr->left;
            } else {
                pred->right = nullptr;
                cout << curr->val << " ";
                curr = curr->right;
            }
        }
    }
}
```

---

### ⏱️ Time Complexity:

- All traversals: **Θ(n)**

### 🧮 Space Complexity:

- Recursive: O(h) stack
- Iterative: O(h) stack
- Level-order: O(w) queue
- Morris: O(1) extra

---

## 🔍 Section: Lowest Common Ancestor (LCA)

**🎯 Category:** Tree Algorithms

The **Lowest Common Ancestor (LCA)** of two nodes in a tree is the deepest node that is an ancestor of both. Efficient LCA computation is critical for many tree, graph, and range query problems.

---

## 📶 1. Binary Lifting (Online LCA Queries)

### 🧠 Concept:

Preprocess a tree so that for any two nodes `u` and `v`, the LCA can be computed in **O(log N)** time by jumping 2ᵏ ancestors using binary powers.

---

### ✅ Requirements:

- Rooted tree
- Preprocessing in O(N log N)
- Efficient for **online multiple queries**

---

### 🔧 Preprocessing Code:

```cpp
const int LOG = 20;
const int N = 1e5;
vector<int> adj[N];
int up[N][LOG];  // up[u][j] = 2^j-th ancestor of u
int depth[N];

void dfs(int u, int p) {
    up[u][0] = p;
    for (int j = 1; j < LOG; j++) {
        if (up[u][j - 1] != -1)
            up[u][j] = up[up[u][j - 1]][j - 1];
        else
            up[u][j] = -1;
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
}
```

### 🔧 LCA Query Code:

```cpp
int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    // Lift u up
    for (int j = LOG - 1; j >= 0; j--)
        if (up[u][j] != -1 && depth[up[u][j]] >= depth[v])
            u = up[u][j];

    if (u == v) return u;

    // Lift both until their parents match
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != -1 && up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}
```

---

### ⏱️ Time Complexity:

- Preprocessing: **Θ(N log N)**
- Query: **Θ(log N)**
- Best Case (depth diff 0): **Ω(1)**

### 🧮 Space Complexity:

- O(N log N)

### ✅ Pros:

- Fast online queries
- Easy to implement with DFS

### ❌ Cons:

- Needs fixed root
- Cannot handle dynamic tree updates

### 🚀 Applications:

- Tree queries in contests
- Shortest path problems
- Range ancestor checks

---

## 🧠 2. Tarjan's Offline LCA Algorithm

### 🧠 Concept:

Handles **multiple offline LCA queries** in a **single DFS traversal** using **Union-Find (Disjoint Set Union)** and coloring.

---

### ✅ Requirements:

- Batch query input known beforehand
- Faster than multiple LCA queries

---

### 🔧 Code Overview:

```cpp
vector<int> adj[N], ancestor(N), parent(N), color(N);
vector<pair<int, int>> queries[N];
vector<int> answer;

int find(int u) {
    return parent[u] == u ? u : parent[u] = find(parent[u]);
}

void tarjanLCA(int u) {
    ancestor[u] = u;
    parent[u] = u;
    for (int v : adj[u]) {
        tarjanLCA(v);
        parent[v] = u;
        ancestor[find(u)] = u;
    }
    color[u] = 1;
    for (auto [v, qid] : queries[u]) {
        if (color[v])
            answer[qid] = ancestor[find(v)];
    }
}
```

---

### Initialization:

```cpp
// For each query (u, v), add to both u and v's query list
queries[u].emplace_back(v, query_id);
queries[v].emplace_back(u, query_id);
```

---

### ⏱️ Time Complexity:

- **Θ(N + Q α(N))** — using Union-Find with path compression  
  (α is inverse Ackermann function)

### 🧮 Space Complexity:

- O(N + Q)

### ✅ Pros:

- Very fast for batch queries
- Efficient with Disjoint Set

### ❌ Cons:

- Only works for **offline queries**
- Harder to implement/debug

### 🚀 Applications:

- Batch LCA queries
- Heavy tree analytics
- Offline processing in compilers/static analysis

---

## 🧮 Comparison Summary

| Method           | Type    | Preprocess | Query    | Space      | Use Case                     |
| ---------------- | ------- | ---------- | -------- | ---------- | ---------------------------- |
| Binary Lifting   | Online  | Θ(N log N) | Θ(log N) | O(N log N) | Fast multiple online queries |
| Tarjan’s Offline | Offline | Θ(N + Q)   | O(1)     | O(N + Q)   | Batch queries, faster total  |

---

## 🌳 Section: Tree Types & Properties

**🎯 Category:** Tree Algorithms

Understanding different types of binary trees is crucial for identifying when optimizations apply, and how data is organized structurally.

---

## 🌲 1. Height-Balanced Binary Tree

### 🧠 Definition:

A **Height-Balanced Tree** is a binary tree where the difference in height between the left and right subtree of any node is **at most 1**.

Formally:

```
|height(left subtree) - height(right subtree)| ≤ 1
```

### 🔧 Properties:

- Subtree heights differ by ≤1
- Can be used in AVL Trees, Red-Black Trees

### ✅ Pros:

- Ensures balanced structure
- Guarantees O(log n) search time

### ❌ Cons:

- Requires rebalancing on insert/delete

### 🚀 Applications:

- AVL Trees
- Self-balancing BSTs
- Memory-efficient search trees

---

## 🧱 2. Complete Binary Tree

### 🧠 Definition:

A **Complete Binary Tree** is a binary tree in which all levels are **completely filled** except possibly the last, and the last level has all keys as **left as possible**.

### 🔧 Properties:

- Nodes filled from left to right
- Common in array-represented trees (e.g., heaps)

### ✅ Pros:

- Compact memory representation
- Great for heap storage in arrays

### ❌ Cons:

- No constraint on sortedness or height

### 🚀 Applications:

- Binary Heaps (Min-Heap, Max-Heap)
- Priority queues

---

## 🎯 3. Perfect Binary Tree

### 🧠 Definition:

A **Perfect Binary Tree** is a binary tree in which all **internal nodes have exactly two children** and all **leaves are at the same level**.

### 🔧 Properties:

- Number of nodes: `2^h - 1` for height `h`
- Completely balanced and full

### ✅ Pros:

- Mathematically clean and ideal
- All paths are equal length

### ❌ Cons:

- Strict constraint; rare in practice

### 🚀 Applications:

- Theoretical problems
- Efficient memory hierarchy modeling

---

## 📦 4. Full Binary Tree

### 🧠 Definition:

A **Full Binary Tree** is a tree in which every node has **0 or 2 children** (no nodes with only 1 child).

### 🔧 Properties:

- May not be complete or perfect
- Every node has either 2 or 0 children

### ✅ Pros:

- Balanced recursive structure
- Common in parsing expressions, segment trees

### ❌ Cons:

- Can still be skewed

### 🚀 Applications:

- Expression trees
- Decision trees
- Segment and binary indexed trees

---

## 📊 Summary Table

| Tree Type       | Definition                                                   | Complete? | Balanced? | Applications                    |
| --------------- | ------------------------------------------------------------ | --------- | --------- | ------------------------------- |
| Height-Balanced | Height diff ≤ 1 at every node                                | ❌        | ✅        | AVL, Red-Black Trees            |
| Complete Binary | All levels filled, last filled left to right                 | ✅        | ❌        | Binary Heaps                    |
| Perfect Binary  | All internal nodes have 2 children, all leaves at same level | ✅        | ✅        | Theoretical Trees               |
| Full Binary     | Every node has 0 or 2 children                               | ❌        | ❌        | Expression Trees, Segment Trees |

---

## 🌲 Section: AVL Tree (Adelson-Velsky and Landis Tree)

**🎯 Category:** Tree Algorithms

An **AVL Tree** is a **self-balancing binary search tree** where the difference between the heights of left and right subtrees (balance factor) is at most 1 for all nodes.

---

## ⚖️ Balance Factor

### 🧠 Concept:

For any node `N`, define the **Balance Factor** as:

```
BF(N) = height(left subtree) - height(right subtree)
```

- Valid if BF ∈ {–1, 0, 1}
- Imbalance triggers **rotation**

---

## 🔄 AVL Tree Rotations

When balance factor becomes outside the range [–1, 1], rebalancing is done using rotations:

| Case | Condition (after insertion) | Fix                                     |
| ---- | --------------------------- | --------------------------------------- |
| LL   | Left of Left                | Right Rotation                          |
| RR   | Right of Right              | Left Rotation                           |
| LR   | Right of Left               | Left on Left child, then Right on root  |
| RL   | Left of Right               | Right on Right child, then Left on root |

---

### 🔁 Right Rotation (LL Case)

```cpp
TreeNode* rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}
```

---

### 🔁 Left Rotation (RR Case)

```cpp
TreeNode* leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}
```

---

## 🌱 AVL Insertion (with Balancing)

### 🔧 Code:

```cpp
int height(TreeNode* node) {
    return node ? node->height : 0;
}

int getBalance(TreeNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

void updateHeight(TreeNode* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

TreeNode* insert(TreeNode* node, int key) {
    if (!node) return new TreeNode(key);

    if (key < node->val) node->left = insert(node->left, key);
    else if (key > node->val) node->right = insert(node->right, key);
    else return node;

    updateHeight(node);
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->val)
        return rightRotate(node);
    if (balance < -1 && key > node->right->val)
        return leftRotate(node);
    if (balance > 1 && key > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}
```

---

### ⏱️ Time Complexity:

- Insertion/Deletion: **Θ(log n)**
- Search: **Θ(log n)**
- Worst Case: **Θ(log n)** (tree remains balanced)

### 🧮 Space Complexity:

- O(log n) recursive stack (insertion)

---

### ✅ Pros:

- Guarantees log-time operations
- Self-balancing

### ❌ Cons:

- Complex to implement
- Frequent rebalancing can hurt performance

---

### 🚀 Applications:

- Databases / Indexing
- Real-time systems
- Range queries where strict balancing is important

---

## 🌿 Section: AVL Tree – Rotations & Balance

**🎯 Category:** Tree Algorithms

**AVL Tree** is a **self-balancing binary search tree** where the balance factor (height difference between left and right subtrees) is maintained to be **-1, 0, or +1** for every node.

---

## ⚖️ Balance Factor

### 🧠 Definition:

Balance Factor = `height(left subtree) - height(right subtree)`

- BF ∈ { -1, 0, 1 } → ✅ Balanced
- If outside this range → requires **rotation**

### 🧮 Example:

```
     5
    / \
   3   8

Balance Factor(5) = height(3) - height(8) = 1 - 1 = 0
```

---

## 🔁 Rotations in AVL Tree

### 🌀 Purpose:

To **restore balance** when BF becomes -2 or +2 after insertion/deletion.

---

### 🔁 1. Right Rotation (LL Case)

**When:** Left child has a left-heavy subtree

```
      z                              y
     / \                            / \
    y   T4   → RightRotate(z) →   x   z
   / \                                / \
  x   T3                            T3  T4
```

```cpp
TreeNode* rightRotate(TreeNode* z) {
    TreeNode* y = z->left;
    TreeNode* T3 = y->right;
    y->right = z;
    z->left = T3;
    updateHeight(z);
    updateHeight(y);
    return y;
}
```

---

### 🔁 2. Left Rotation (RR Case)

**When:** Right child has a right-heavy subtree

```
    z                             y
   / \                           / \
  T1  y       → LeftRotate(z) → z   x
     / \                       / \
    T2  x                     T1 T2
```

```cpp
TreeNode* leftRotate(TreeNode* z) {
    TreeNode* y = z->right;
    TreeNode* T2 = y->left;
    y->left = z;
    z->right = T2;
    updateHeight(z);
    updateHeight(y);
    return y;
}
```

---

### 🔁 3. Left-Right Rotation (LR Case)

**When:** Left child has a right-heavy subtree  
→ First do left rotation on child, then right rotation on node.

```
      z                         z                         x
     / \                       / \                      /   \
    y   T4 → LeftRotate(y) →  x   T4 → RightRotate(z)→ y     z
     \                           /                      / \   / \
      x                         y                      T1 T2 T3 T4
     /                         / \
    T1                        T1 T2
```

```cpp
TreeNode* leftRightRotate(TreeNode* z) {
    z->left = leftRotate(z->left);
    return rightRotate(z);
}
```

---

### 🔁 4. Right-Left Rotation (RL Case)

**When:** Right child has a left-heavy subtree  
→ First do right rotation on child, then left rotation on node.

```
      z                           z                           x
     / \                         / \                         /   \
    T1  y    → RightRotate(y) → T1  x     → LeftRotate(z) → z     y
        /                            \                    / \   / \
       x                              y                  T1 T2 T3 T4
      / \                            / \
     T2 T3                          T3 T4
```

```cpp
TreeNode* rightLeftRotate(TreeNode* z) {
    z->right = rightRotate(z->right);
    return leftRotate(z);
}
```

---

## 🌱 AVL Tree Insertion

### 🧩 Steps:

1. Do normal BST insertion
2. Update height of ancestors
3. Check balance factor
4. Perform required rotation

---

### 🔧 AVL Insert Function:

```cpp
int height(TreeNode* node) {
    return node ? node->height : 0;
}

int getBalance(TreeNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

void updateHeight(TreeNode* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

TreeNode* insert(TreeNode* node, int key) {
    if (!node) return new TreeNode(key);

    if (key < node->val)
        node->left = insert(node->left, key);
    else if (key > node->val)
        node->right = insert(node->right, key);
    else return node; // no duplicates

    updateHeight(node);
    int bf = getBalance(node);

    // Handle rotations
    if (bf > 1 && key < node->left->val) return rightRotate(node);      // LL
    if (bf < -1 && key > node->right->val) return leftRotate(node);     // RR
    if (bf > 1 && key > node->left->val) return leftRightRotate(node);  // LR
    if (bf < -1 && key < node->right->val) return rightLeftRotate(node);// RL

    return node;
}
```

---

## ⏱️ Time Complexity:

- Insert/Delete/Search: **Θ(log n)**
- Best Case: **Ω(log n)**
- Worst Case: **Θ(log n)**

### 🧮 Space Complexity:

- O(h) = O(log n) (stack space for recursion)

---

### ✅ Pros:

- Always balanced → O(log n) guarantees
- Good for ordered data

### ❌ Cons:

- Complex rotation logic
- Slower insertions than plain BST

---

### 🚀 Applications:

- In-memory DB indexes
- Ordered map/set implementations
- Competitive programming (logarithmic BST ops)

---

## 🌲 Section: B-Trees & B+ Trees

**🎯 Category:** Tree Algorithms

**B-Trees** and **B+ Trees** are self-balancing search trees optimized for **minimizing disk I/O** and **range queries**. They're widely used in **databases** and **file systems** due to their ability to handle large blocks of data efficiently.

---

## 🧠 1. B-Tree

### 📌 Concept:

A **B-Tree** of order `m` is a generalization of a BST where:

- Each node can have **at most m children**
- Each internal node contains up to `m-1` **sorted keys**
- Ensures **logarithmic height** for fast access

### 🔧 Key Properties:

- Balanced, multi-level index tree
- All leaves appear on the same level
- Minimizes disk access by reading/writing in blocks

### 🔄 Operations:

- Search: Standard binary search on keys
- Insertion/Deletion: May require node **splitting or merging**

---

### 🔧 B-Tree Insertion (Overview):

1. Insert key in leaf
2. If overflow (more than `m-1` keys), **split** and promote median
3. Recursively adjust up to root

---

## 🌿 2. B+ Tree

### 📌 Concept:

A **B+ Tree** is a variant of B-Tree where:

- **All data keys are stored in leaves**
- **Internal nodes store only keys** used for routing
- Leaves are linked in a **linked list** for range scans

### 🔧 Key Properties:

- Internal nodes guide the search
- Leaves contain actual data and are linked → easy range queries
- All data is accessed from the leaves (uniform access path)

---

## 🔍 Differences: B-Tree vs B+ Tree

| Feature               | B-Tree                | B+ Tree                           |
| --------------------- | --------------------- | --------------------------------- |
| Data Storage          | Internal + leaf nodes | Only leaf nodes                   |
| Internal node content | Keys + data           | Only keys                         |
| Leaf linkage          | No                    | Doubly linked list                |
| Range queries         | Costlier              | Efficient with linked leaves      |
| Disk optimization     | Good                  | Excellent (better cache/disk use) |

---

## 🧩 B+ Tree Search Example

```plaintext
Internal:
       [17, 45]
      /    |     \
 [5,10] [20,30] [50,70]
     |      |      |
   ...    ...    ... ← leaves contain full data
```

Search path is purely guided by keys in internal nodes and **always ends at a leaf**.

---

## ⏱️ Time Complexity (Both Trees)

| Operation | Time Complexity |
| --------- | --------------- |
| Search    | Θ(logₘ n)       |
| Insert    | Θ(logₘ n)       |
| Delete    | Θ(logₘ n)       |

Where `m` = max number of children (depends on block size / disk page)

### 🧮 Space Complexity:

- O(n)

---

### ✅ Pros (Especially B+ Tree):

- Optimized for disk-based systems
- Fast range queries via linked leaves
- Height is very small (due to high fan-out)

### ❌ Cons:

- Insertion/Deletion are complex to implement
- Slower single-element search compared to BST for in-memory use

---

### 🚀 Applications:

- Database indexing (MySQL, PostgreSQL, Oracle)
- File systems (NTFS, HFS+, Ext4)
- Storage engines like InnoDB

---

## 📦 Summary Table

| Tree Type | Storage | Internal Nodes | Leaf Nodes           | Range Query | Used In        |
| --------- | ------- | -------------- | -------------------- | ----------- | -------------- |
| B-Tree    | All     | Keys + Values  | Keys + Values        | Medium      | In-memory/disk |
| B+ Tree   | Leaf    | Keys Only      | Full Values (Linked) | Excellent   | DB indexing    |

---

## 🌐 Section: Tree Diameter & Maximum Path Sum

**🎯 Category:** Tree Algorithms

Tree problems like **diameter** and **maximum path sum** can be solved using **DFS aggregation**, where we recursively collect and propagate information up the tree to compute global properties.

---

## 📏 1. Tree Diameter (Longest Path in Tree)

### 🧠 Concept:

The **diameter** of a tree is the **length of the longest path between any two nodes**. It may or may not pass through the root.

### 📌 Observation:

For any node `u`, the longest path through `u` =  
`height(left subtree) + height(right subtree)`

---

### 🔧 Code (Post-order DFS):

```cpp
int maxDiameter = 0;

int dfs(TreeNode* root) {
    if (!root) return 0;
    int lh = dfs(root->left);
    int rh = dfs(root->right);
    maxDiameter = max(maxDiameter, lh + rh); // update diameter
    return 1 + max(lh, rh); // height of current subtree
}

int diameterOfBinaryTree(TreeNode* root) {
    dfs(root);
    return maxDiameter;
}
```

---

### ⏱️ Time Complexity:

- Θ(n) – all nodes visited
- Ω(n) – no early return

### 🧮 Space Complexity:

- O(h) – recursion stack

### ✅ Pros:

- Clean recursive solution
- Aggregates height info efficiently

### ❌ Cons:

- Careful to return height, not diameter

### 🚀 Applications:

- Network cable length
- Max latency path in routers
- File system path analysis

---

## 💰 2. Maximum Path Sum in Binary Tree

### 🧠 Concept:

Find the **maximum sum of values along any path** in the tree.  
The path **can start and end at any node**, but must go downward (parent → child).

---

### 🔧 Recursive DFS Aggregation:

At each node, compute:

- Max gain from left: `max(0, dfs(left))`
- Max gain from right: `max(0, dfs(right))`
- Local sum: `val + left_gain + right_gain`

---

### 🔧 Code:

```cpp
int maxPath = INT_MIN;

int dfs(TreeNode* root) {
    if (!root) return 0;
    int leftGain = max(0, dfs(root->left));
    int rightGain = max(0, dfs(root->right));
    maxPath = max(maxPath, root->val + leftGain + rightGain);
    return root->val + max(leftGain, rightGain);
}

int maxPathSum(TreeNode* root) {
    dfs(root);
    return maxPath;
}
```

---

### ⏱️ Time Complexity:

- Θ(n) – full traversal
- Ω(n) – no shortcut

### 🧮 Space Complexity:

- O(h)

### ✅ Pros:

- Handles negative values
- Covers any-to-any path (not just root-to-leaf)

### ❌ Cons:

- Must avoid including both negative left/right gains

### 🚀 Applications:

- Profit paths in decision trees
- Weighted path analysis
- Max-cost traversal in DAG-like trees

---

## ⚖️ Comparison Summary

| Problem       | Path Type          | Code Logic             | Global State |
| ------------- | ------------------ | ---------------------- | ------------ |
| Tree Diameter | Node count         | Height aggregation     | maxDiameter  |
| Max Path Sum  | Value accumulation | Max gain + current val | maxPath      |

---

## 🌳 Section: Binary Search Trees (BST)

**🎯 Category:** Tree Algorithms

A **Binary Search Tree** is a binary tree where:

```
For any node:
All values in left subtree < node’s value < all values in right subtree
```

This **ordering invariant** allows efficient search, insertion, and range-based operations.

---

## 📐 1. Inorder Traversal Property

### 🧠 Concept:

The **inorder traversal** of a BST yields a **sorted sequence** of node values.

```cpp
void inorder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorder(root->left, result);
    result.push_back(root->val);
    inorder(root->right, result);
}
```

### 🔍 Usage:

- Verifies structure
- Enables binary search on output
- Basis for tree-to-array flattening

---

## 📊 2. Range Queries on BST

### 🧠 Concept:

Leverage BST properties to **prune branches** that fall outside the range `[L, R]`.

---

### 🔧 Count Nodes in Range [L, R]

```cpp
int rangeCount(TreeNode* root, int L, int R) {
    if (!root) return 0;
    if (root->val < L) return rangeCount(root->right, L, R);
    if (root->val > R) return rangeCount(root->left, L, R);
    return 1 + rangeCount(root->left, L, R) + rangeCount(root->right, L, R);
}
```

---

### 🔧 Sum Nodes in Range [L, R]

```cpp
int rangeSumBST(TreeNode* root, int L, int R) {
    if (!root) return 0;
    if (root->val < L) return rangeSumBST(root->right, L, R);
    if (root->val > R) return rangeSumBST(root->left, L, R);
    return root->val + rangeSumBST(root->left, L, R) + rangeSumBST(root->right, L, R);
}
```

---

## ✅ 3. Validating a BST

### 🧠 Concept:

Check recursively if each node lies in a valid value range `[min, max]`. This avoids incorrect trees with only local BST properties.

---

### 🔧 Code:

```cpp
bool isValid(TreeNode* root, long minVal, long maxVal) {
    if (!root) return true;
    if (root->val <= minVal || root->val >= maxVal) return false;
    return isValid(root->left, minVal, root->val) &&
           isValid(root->right, root->val, maxVal);
}

bool isValidBST(TreeNode* root) {
    return isValid(root, LONG_MIN, LONG_MAX);
}
```

---

## ⏱️ Time & Space Complexity

| Operation         | Time Complexity | Space Complexity |
| ----------------- | --------------- | ---------------- |
| Inorder Traversal | Θ(n)            | O(h)             |
| Range Count/Sum   | Θ(log n + k)    | O(h)             |
| Validation        | Θ(n)            | O(h)             |

- `n` = number of nodes
- `h` = height of tree
- `k` = number of nodes in range (output size)

---

### ✅ Pros:

- Fast search, insert, delete (O(log n) if balanced)
- Ordered traversal possible via inorder
- Can support range queries natively

### ❌ Cons:

- Degenerates to O(n) if unbalanced
- Needs AVL/Red-Black Tree for guaranteed performance

---

### 🚀 Applications:

- Symbol tables / Maps / Sets
- Range search problems
- Ordered statistics
- Data indexing

---

## 📐 Section: Segment Tree

**🎯 Category:** Tree Algorithms

A **Segment Tree** is a binary tree used for **efficient range queries and updates** on arrays. It provides **logarithmic time** for both operations and supports a variety of problems like sum, min, max, GCD, etc.

---

## 🔧 1. Segment Tree (Basic): Range Query + Point Update

### 🧠 Concept:

- Array is divided into segments (ranges) recursively.
- Each node stores info about a segment (e.g., sum of range).
- Combine child segments to answer queries efficiently.

---

### 🧩 Build:

```cpp
int seg[4 * N]; // N = size of input array

void build(vector<int>& a, int node, int l, int r) {
    if (l == r) {
        seg[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(a, 2 * node, l, mid);
    build(a, 2 * node + 1, mid + 1, r);
    seg[node] = seg[2 * node] + seg[2 * node + 1]; // change for other ops
}
```

---

### 🔍 Range Query (e.g., sum):

```cpp
int query(int node, int l, int r, int ql, int qr) {
    if (qr < l || ql > r) return 0;          // No overlap
    if (ql <= l && r <= qr) return seg[node]; // Total overlap
    int mid = (l + r) / 2;
    return query(2 * node, l, mid, ql, qr) +
           query(2 * node + 1, mid + 1, r, ql, qr);
}
```

---

### ✏️ Point Update:

```cpp
void update(int node, int l, int r, int idx, int val) {
    if (l == r) {
        seg[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (idx <= mid)
        update(2 * node, l, mid, idx, val);
    else
        update(2 * node + 1, mid + 1, r, idx, val);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
}
```

---

## 🛠️ 2. Segment Tree with Lazy Propagation

### 🧠 Concept:

Used when updates are frequent on **ranges**. Rather than updating immediately, changes are **"lazily"** stored and propagated only when needed.

---

### 🧩 Structure:

```cpp
int seg[4 * N], lazy[4 * N];
```

---

### ✏️ Lazy Update:

```cpp
void updateRange(int node, int l, int r, int ql, int qr, int val) {
    if (lazy[node] != 0) {
        seg[node] += (r - l + 1) * lazy[node];
        if (l != r) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    if (qr < l || ql > r) return; // No overlap

    if (ql <= l && r <= qr) {
        seg[node] += (r - l + 1) * val;
        if (l != r) {
            lazy[2 * node] += val;
            lazy[2 * node + 1] += val;
        }
        return;
    }

    int mid = (l + r) / 2;
    updateRange(2 * node, l, mid, ql, qr, val);
    updateRange(2 * node + 1, mid + 1, r, ql, qr, val);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
}
```

---

### 🔍 Lazy Query:

```cpp
int queryRange(int node, int l, int r, int ql, int qr) {
    if (lazy[node] != 0) {
        seg[node] += (r - l + 1) * lazy[node];
        if (l != r) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    if (qr < l || ql > r) return 0;
    if (ql <= l && r <= qr) return seg[node];

    int mid = (l + r) / 2;
    return queryRange(2 * node, l, mid, ql, qr) +
           queryRange(2 * node + 1, mid + 1, r, ql, qr);
}
```

---

## ⏱️ Time & Space Complexity

| Operation           | Time     | Space    |
| ------------------- | -------- | -------- |
| Build               | Θ(n)     | O(n)     |
| Point Query/Update  | Θ(log n) | O(log n) |
| Range Update (Lazy) | Θ(log n) | O(log n) |
| Range Query         | Θ(log n) | O(log n) |

---

### ✅ Pros:

- Very fast for range queries + updates
- Lazy propagation handles large updates efficiently
- Flexible to handle custom operations (min, max, GCD, XOR)

### ❌ Cons:

- Needs careful implementation
- Not as cache-friendly as flat arrays

---

### 🚀 Applications:

- Range sum/min/max queries
- Competitive programming
- Histogram or interval updates
- Matrix flattening queries (2D → 1D)

---

## 🧮 Section: Fenwick Tree (Binary Indexed Tree - BIT)

**🎯 Category:** Tree Algorithms

A **Fenwick Tree (or Binary Indexed Tree)** is a space-efficient data structure for **prefix sum and update operations** in logarithmic time.

---

## 📦 1. Structure & Indexing

### 🧠 Concept:

- Each index `i` stores sum of a range of elements determined by the **least significant bit (LSB)** of `i`.
- Operates on 1-based indexing.

### 📌 Binary Insight:

- LSB of `i` → `i & (-i)`
- Jump to next node: `i += (i & -i)`
- Move to parent: `i -= (i & -i)`

---

## 🔧 2. BIT Construction (Point Updates & Prefix Queries)

### 🧩 Initialize:

```cpp
int BIT[N + 1] = {0}; // 1-based indexing
```

---

### 🔍 Prefix Sum Query:

```cpp
int prefixSum(int i) {
    int sum = 0;
    while (i > 0) {
        sum += BIT[i];
        i -= (i & -i);
    }
    return sum;
}
```

---

### ✏️ Point Update:

```cpp
void update(int i, int delta) {
    while (i <= N) {
        BIT[i] += delta;
        i += (i & -i);
    }
}
```

---

## 🧾 3. Range Query [l, r] using Prefix Sums

### 🧠 Formula:

```cpp
rangeSum(l, r) = prefixSum(r) - prefixSum(l - 1);
```

---

## 🔄 4. Range Update with Point Query Variant

To support range updates and point query:

- Maintain a BIT such that `BIT[i]` = change applied to index `i`

```cpp
// Range update: add 'val' to range [l, r]
void rangeUpdate(int l, int r, int val) {
    update(l, val);
    update(r + 1, -val);
}

// Point query after range updates
int pointQuery(int i) {
    int sum = 0;
    while (i > 0) {
        sum += BIT[i];
        i -= (i & -i);
    }
    return sum;
}
```

---

## ⏱️ Time & Space Complexity

| Operation              | Time Complexity | Space |
| ---------------------- | --------------- | ----- |
| Build (naive)          | Θ(n log n)      | O(n)  |
| Point Update           | Θ(log n)        | O(1)  |
| Prefix Query           | Θ(log n)        | O(1)  |
| Range Query            | Θ(log n)        | O(1)  |
| Range Update (variant) | Θ(log n)        | O(1)  |

---

### ✅ Pros:

- Simple & fast for prefix/range operations
- Lower memory than Segment Tree (1 array only)
- Easy to code and debug

### ❌ Cons:

- Less flexible than Segment Tree (limited ops)
- Only works for invertible operations (sum, XOR)

---

### 🚀 Applications:

- Prefix sum queries (classic)
- Inversion count in arrays
- Counting frequency of elements
- Range frequency in offline queries
- Subarray problems (like count of smaller/greater elements)

---

## 📊 Example Usage: Count Inversions

```cpp
int countInversions(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> BIT(maxVal + 2, 0);
    int inv = 0;
    for (int i = arr.size() - 1; i >= 0; --i) {
        inv += prefixSum(arr[i] - 1);
        update(arr[i], 1);
    }
    return inv;
}
```

---

## 🧩 Section: Merge Sort Tree & Wavelet Tree

**🎯 Category:** Tree Algorithms

These trees allow fast range queries on **sorted information** like:

- Count of elements ≤ X in range `[L, R]`
- K-th smallest in a range
- Range frequency / quantile / selection problems

---

## 🧮 1. Merge Sort Tree

### 🧠 Concept:

A **Merge Sort Tree** is a Segment Tree where each node stores a **sorted vector of its segment**.

- Combines ideas from Merge Sort + Segment Tree
- Enables binary search over each segment

---

### 🛠️ Use-Cases:

- Count of elements ≤ X in range `[L, R]`
- Count of elements in custom ranges
- Lower/upper bound frequency in a range

---

### 🧩 Build:

```cpp
vector<int> tree[4 * N];

void build(vector<int>& a, int node, int l, int r) {
    if (l == r) {
        tree[node] = {a[l]};
        return;
    }
    int mid = (l + r) / 2;
    build(a, 2 * node, l, mid);
    build(a, 2 * node + 1, mid + 1, r);
    merge(tree[2 * node].begin(), tree[2 * node].end(),
          tree[2 * node + 1].begin(), tree[2 * node + 1].end(),
          back_inserter(tree[node]));
}
```

---

### 🔍 Query: Count of values ≤ `x` in range `[ql, qr]`

```cpp
int query(int node, int l, int r, int ql, int qr, int x) {
    if (r < ql || l > qr) return 0;
    if (ql <= l && r <= qr)
        return upper_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin();
    int mid = (l + r) / 2;
    return query(2 * node, l, mid, ql, qr, x) +
           query(2 * node + 1, mid + 1, r, ql, qr, x);
}
```

---

### ⏱️ Complexity:

| Operation | Time                                       |
| --------- | ------------------------------------------ |
| Build     | Θ(n log n)                                 |
| Query     | Θ(log² n) (binary search inside each node) |

---

### ✅ Pros:

- Supports value-based range queries
- Clean, recursive structure
- Handles frequency/counts efficiently

### ❌ Cons:

- No point updates (rebuild entire path on change)
- Slower than Segment Tree for simple ops

---

## 🌊 2. Wavelet Tree

### 🧠 Concept:

A **Wavelet Tree** is a powerful tree that encodes an array to answer:

- K-th smallest in `[L, R]`
- Count of numbers ≤ K in `[L, R]`
- Count/frequency of a value in range

It compresses the value range instead of segmenting positions.

---

### 🌳 Structure:

Each node divides values into **two halves** based on a midpoint `mid`, and recursively constructs left/right Wavelet subtrees:

- Left: values ≤ mid
- Right: values > mid

Each node also stores a **bit vector** of prefix sums of left side.

---

### 🔩 Operations:

- `kth(l, r, k)` → k-th smallest in range
- `LTE(l, r, k)` → count of numbers ≤ k in range
- `count(l, r, x)` → frequency of x in range

---

### 📚 Usage:

```cpp
// Wavelet Tree from sorted values in range [lo, hi]
struct WaveletTree {
    int lo, hi;
    WaveletTree *l = 0, *r = 0;
    vector<int> b;

    WaveletTree(vector<int>::iterator from, vector<int>::iterator to, int x, int y) : lo(x), hi(y) {
        if (lo == hi || from >= to) return;
        int mid = (lo + hi) / 2;
        auto f = [mid](int x) { return x <= mid; };
        b.reserve(to - from + 1);
        b.push_back(0);
        for (auto it = from; it != to; ++it)
            b.push_back(b.back() + f(*it));
        auto pivot = stable_partition(from, to, f);
        l = new WaveletTree(from, pivot, lo, mid);
        r = new WaveletTree(pivot, to, mid + 1, hi);
    }

    int kth(int l_idx, int r_idx, int k) {
        if (lo == hi) return lo;
        int inLeft = b[r_idx] - b[l_idx - 1];
        if (k <= inLeft)
            return l->kth(b[l_idx - 1] + 1, b[r_idx], k);
        return r->kth(l_idx - b[l_idx - 1], r_idx - b[r_idx], k - inLeft);
    }

    int LTE(int l_idx, int r_idx, int x) {
        if (x < lo) return 0;
        if (hi <= x) return r_idx - l_idx + 1;
        return l->LTE(b[l_idx - 1] + 1, b[r_idx], x) +
               r->LTE(l_idx - b[l_idx - 1], r_idx - b[r_idx], x);
    }

    int count(int l_idx, int r_idx, int x) {
        if (lo == hi) return r_idx - l_idx + 1;
        int mid = (lo + hi) / 2;
        if (x <= mid)
            return l->count(b[l_idx - 1] + 1, b[r_idx], x);
        return r->count(l_idx - b[l_idx - 1], r_idx - b[r_idx], x);
    }
};
```

---

## ⏱️ Complexity (Wavelet Tree)

| Operation          | Time       |
| ------------------ | ---------- |
| Build              | Θ(n log M) |
| K-th / LTE / Count | Θ(log M)   |

Where `M` = range of values in the array.

---

### ✅ Pros:

- Extremely powerful: k-th smallest, count ≤ X, range freq
- Efficient in space (O(n log M))
- Logarithmic query time

### ❌ Cons:

- Complex to implement/debug
- Not great for updates

---

### 🚀 Applications:

- Range frequency / order statistics
- Offline queries
- Compression / full-text indexing
- Computational geometry

---

## 🧱 Section: Persistent Segment Tree

**🎯 Category:** Tree Algorithms

A **Persistent Segment Tree** retains access to previous versions of the array after updates by **cloning only the affected path** during updates.

---

## 🧠 Core Concept

- When performing an update, a new version of the segment tree is created.
- Only **O(log n)** new nodes are created per update.
- Earlier versions remain unmodified and can still be queried.

This enables:

- Rollback support
- Time-travel range queries
- Efficient snapshot/versioning

---

## 🛠️ Structure

Each version has a **root pointer** to a version of the segment tree. A node structure looks like:

```cpp
struct Node {
    int val;
    Node *left, *right;
    Node(int v = 0, Node* l = nullptr, Node* r = nullptr) : val(v), left(l), right(r) {}
};
```

---

## 🧩 Build (Version 0)

```cpp
Node* build(int l, int r) {
    if (l == r) return new Node(0);
    int mid = (l + r) / 2;
    return new Node(0, build(l, mid), build(mid + 1, r));
}
```

---

## ✏️ Point Update (Persistent)

```cpp
Node* update(Node* prev, int l, int r, int idx, int val) {
    if (l == r) return new Node(val);
    int mid = (l + r) / 2;
    if (idx <= mid)
        return new Node(0, update(prev->left, l, mid, idx, val), prev->right);
    else
        return new Node(0, prev->left, update(prev->right, mid + 1, r, idx, val));
}
```

---

## 🔍 Query in Version `v`

```cpp
int query(Node* node, int l, int r, int ql, int qr) {
    if (r < ql || l > qr) return 0;
    if (ql <= l && r <= qr) return node->val;
    int mid = (l + r) / 2;
    return query(node->left, l, mid, ql, qr) +
           query(node->right, mid + 1, r, ql, qr);
}
```

To support sum queries, update `val` accordingly during updates:

```cpp
return new Node(left->val + right->val, left, right);
```

---

## ⏱️ Time & Space Complexity

| Operation    | Time     | Space per update   |
| ------------ | -------- | ------------------ |
| Build        | Θ(n)     | Θ(n)               |
| Point Update | Θ(log n) | O(log n) new nodes |
| Query        | Θ(log n) | -                  |

---

### ✅ Pros:

- All versions accessible in O(1) via root pointer
- Space-efficient versioning
- Great for rollback, immutable DS, and historical data

### ❌ Cons:

- Slightly slower than non-persistent segment trees
- Increased memory usage (log n per update)

---

### 🚀 Applications:

- Historical range queries
- Version control in arrays
- Undo features in editors/games
- K-th smallest in subarray (combine with Merge Sort Tree)
- Dynamic connectivity in graphs (offline)

---

## 📊 Summary

| Feature              | Persistent ST     | Normal ST         |
| -------------------- | ----------------- | ----------------- |
| Keeps previous state | ✅ Yes            | ❌ No             |
| Space per update     | O(log n)          | O(1)              |
| Point updates        | O(log n)          | O(log n)          |
| Use case             | Versioned queries | Real-time updates |

---

## 🔢 Section: Dynamic K-th Order Queries

**🎯 Category:** Advanced Trees & Order Statistics

Dynamic K-th order queries involve finding the **k-th smallest or largest element** in a dynamic dataset that supports:

- **Insertions**
- **Deletions**
- **Efficient querying**

---

## 🧠 Problem Statement

Given a dynamic array/set:

- Support insertion and deletion of elements
- Answer: “What is the k-th smallest element?” at any time

---

## 🔧 1. Augmented Balanced BST (Ordered Set / Treap)

### 🧠 Concept:

Each node of the BST maintains:

- Value
- Subtree size (for rank computation)

---

### ⚙️ Operations:

- Insertion: maintain size while inserting
- Deletion: update size after deletion
- K-th smallest: recurse using size of left subtree

---

### 🌲 Treap-based C++ Template:

```cpp
struct Node {
    int key, prior, size;
    Node *l, *r;
    Node(int k) : key(k), prior(rand()), size(1), l(nullptr), r(nullptr) {}
};

int sz(Node* t) { return t ? t->size : 0; }

void upd_sz(Node* t) {
    if (t) t->size = 1 + sz(t->l) + sz(t->r);
}

void split(Node* t, int key, Node*& l, Node*& r) {
    if (!t) l = r = nullptr;
    else if (key < t->key) split(t->l, key, l, t->l), r = t;
    else split(t->r, key, t->r, r), l = t;
    upd_sz(t);
}

Node* merge(Node* l, Node* r) {
    if (!l || !r) return l ? l : r;
    if (l->prior > r->prior) {
        l->r = merge(l->r, r); upd_sz(l); return l;
    } else {
        r->l = merge(l, r->l); upd_sz(r); return r;
    }
}

void insert(Node*& t, Node* it) {
    if (!t) t = it;
    else if (it->prior > t->prior) {
        split(t, it->key, it->l, it->r);
        t = it;
    } else {
        insert(it->key < t->key ? t->l : t->r, it);
    }
    upd_sz(t);
}

void erase(Node*& t, int key) {
    if (!t) return;
    if (t->key == key) {
        Node* tmp = t;
        t = merge(t->l, t->r);
        delete tmp;
    } else {
        erase(key < t->key ? t->l : t->r, key);
    }
    upd_sz(t);
}

int kth(Node* t, int k) {
    if (!t) return -1;
    int leftSize = sz(t->l);
    if (k <= leftSize) return kth(t->l, k);
    if (k == leftSize + 1) return t->key;
    return kth(t->r, k - leftSize - 1);
}
```

---

## 📦 2. BIT + Coordinate Compression (Static Values Only)

### 🧠 Idea:

- Use a Binary Indexed Tree (Fenwick Tree) over compressed indices
- Count frequencies and perform binary search for k-th

---

### ⚙️ Steps:

1. Coordinate compress all possible values
2. Update frequencies using BIT
3. Use binary search on BIT prefix sums to get k-th smallest

---

### 📦 Code:

```cpp
int BIT[N]; // for compressed index

void update(int i, int delta) {
    while (i < N) {
        BIT[i] += delta;
        i += i & -i;
    }
}

int query(int i) {
    int sum = 0;
    while (i > 0) {
        sum += BIT[i];
        i -= i & -i;
    }
    return sum;
}

int findKth(int k) {
    int l = 1, r = N - 1, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (query(mid) >= k) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans; // index in compressed space
}
```

---

## ⏱️ Time & Space Complexity

| Method                | Insert / Delete | K-th Query | Space |
| --------------------- | --------------- | ---------- | ----- |
| Treap / AVL / RB Tree | Θ(log n)        | Θ(log n)   | O(n)  |
| BIT + Compression     | Θ(log n)        | Θ(log² n)  | O(n)  |

---

### ✅ Pros:

- Supports dynamic querying
- Efficient for online queries

### ❌ Cons:

- Treap is randomized (less deterministic)
- BIT requires coordinate compression (static domain)

---

### 🚀 Applications:

- Online Median / Quantile queries
- Interactive queries with insert/delete
- K-th inversion problem
- Range K-th queries (with Merge Sort Tree / Wavelet Tree)

---

## 🧭 Section: Heavy-Light Decomposition (HLD)

**🎯 Category:** Tree Algorithms / Tree Queries

**Heavy-Light Decomposition** is used to answer **path queries** (like sum, max, min, LCA, etc.) on trees efficiently by converting the tree into arrays where **segment trees** or **BITs** can be applied.

---

## 🧠 Core Idea

- Decompose the tree into "heavy paths" and "light edges"
- Map tree nodes to an array (`dfs_in[u]`) using DFS
- Perform range queries or updates on these arrays using Segment Trees or BITs

---

## 📊 Definitions

- **Heavy Edge:** Edge to the child with the largest subtree
- **Light Edge:** All other edges
- Every node is connected to at most one heavy child
- Total number of light edges on a root-to-leaf path: ≤ log n

---

## 🧩 1. Preprocessing

```cpp
const int N = 1e5 + 5;
vector<int> tree[N];
int parent[N], depth[N], heavy[N], head[N], pos[N], size[N];
int cur_pos = 0;

int dfs(int u, int p) {
    parent[u] = p;
    depth[u] = depth[p] + 1;
    size[u] = 1;
    int max_size = 0;

    for (int v : tree[u]) {
        if (v == p) continue;
        int sz = dfs(v, u);
        size[u] += sz;
        if (sz > max_size) {
            max_size = sz;
            heavy[u] = v;
        }
    }
    return size[u];
}

void decompose(int u, int h) {
    head[u] = h;
    pos[u] = cur_pos++;
    if (heavy[u])
        decompose(heavy[u], h);
    for (int v : tree[u]) {
        if (v != parent[u] && v != heavy[u])
            decompose(v, v); // new heavy path starts
    }
}
```

---

## 🏗️ 2. Segment Tree on HLD Array

Use `pos[u]` as the index in the segment tree.

---

### Query on Path [u, v]

```cpp
int query(int u, int v) {
    int res = 0;
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]])
            swap(u, v);
        res += segTree.query(pos[head[u]], pos[u]); // range query
        u = parent[head[u]];
    }
    if (depth[u] > depth[v])
        swap(u, v);
    res += segTree.query(pos[u], pos[v]);
    return res;
}
```

---

### Update at Node u

```cpp
segTree.update(pos[u], value);
```

---

## ⏱️ Time & Space Complexity

| Operation           | Time      | Space |
| ------------------- | --------- | ----- |
| Preprocessing (dfs) | Θ(n)      | O(n)  |
| Decomposition       | Θ(n)      | O(n)  |
| Path Query/Update   | Θ(log² n) | O(n)  |

- Each query touches O(log n) segments
- Segment tree query per segment takes O(log n)

---

### ✅ Pros:

- Efficient for tree path/range queries
- Segment/BIT power on trees
- Powerful for rooted or unrooted tree queries

### ❌ Cons:

- Complex to implement
- Doesn't handle subtree queries well (Euler Tour preferred)

---

### 🚀 Applications:

- Path sum/max/min queries
- LCA computation
- Tree modification problems
- Tree DP flattening + query

---

## 🧮 Summary

| Feature        | HLD          | Euler Tour + ST           |
| -------------- | ------------ | ------------------------- |
| Path Query     | ✅ Efficient | ❌ Needs DFS split        |
| Subtree Query  | ❌ Harder    | ✅ Easy (range on in/out) |
| Updates        | ✅ Supported | ✅ Supported              |
| Implementation | 🧠 Complex   | 🧠 Moderate               |

---

## IV. Graph Algorithms

### 📍 Section: Graph Traversals

Graph traversal is a fundamental operation to explore the nodes and edges of a graph. Common approaches include **Breadth-First Search (BFS)** and **Depth-First Search (DFS)**. Variants like **0-1 BFS** are used in weighted graphs with constraints.

---

## 🦶 1. Breadth-First Search (BFS)

### 🧠 Concept:

BFS explores all neighbors of a node before moving to the next level. It uses a queue and is optimal for finding **shortest paths in unweighted graphs**.

### 🛠️ Algorithm:

```cpp
void bfs(int start, vector<vector<int>>& adj, int n) {
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << " ";
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}
```

### ⏱️ Time & Space Complexity:

- **Time:** Θ(V + E)
- **Space:** O(V)

### ✅ Pros:

- Finds shortest path in unweighted graphs
- Simple and robust

### ❌ Cons:

- Can be slow for large graphs
- Requires extra space for queue and visited array

### 🚀 Applications:

- Shortest path (unweighted)
- Level-order traversal
- Bipartite checking
- Connectivity components

---

## 🤷 2. Depth-First Search (DFS)

### 🧠 Concept:

DFS explores as deep as possible before backtracking. Can be implemented recursively or iteratively using a stack.

### 🛠️ Recursive DFS:

```cpp
void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    cout << u << " ";
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, adj, visited);
        }
    }
}
```

### 🛠️ Iterative DFS:

```cpp
void iterativeDFS(int start, vector<vector<int>>& adj, int n) {
    vector<bool> visited(n, false);
    stack<int> st;
    st.push(start);

    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (!visited[u]) {
            visited[u] = true;
            cout << u << " ";
            for (int v : adj[u]) {
                if (!visited[v]) {
                    st.push(v);
                }
            }
        }
    }
}
```

### ⏱️ Time & Space Complexity:

- **Time:** Θ(V + E)
- **Space:** O(V) (stack/recursion)

### ✅ Pros:

- Easy to implement
- Good for cycle detection, topological sort, SCC

### ❌ Cons:

- Stack overflow risk for deep recursion
- No guarantee on path length

### 🚀 Applications:

- Topological sort
- Cycle detection
- SCC / bridges / articulation points

---

## 0️⃣ 3. 0-1 BFS (Weighted Graphs with 0/1 edges)

### 🧠 Concept:

Used for graphs where edge weights are only 0 or 1. It uses a deque instead of a queue and prioritizes **0-weight edges**.

### 🛠️ Algorithm:

```cpp
void zeroOneBFS(int start, vector<vector<pair<int, int>>>& adj, vector<int>& dist) {
    int n = adj.size();
    dist.assign(n, INT_MAX);
    deque<int> dq;
    dq.push_front(start);
    dist[start] = 0;

    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 1)
                    dq.push_back(v);
                else
                    dq.push_front(v);
            }
        }
    }
}
```

### ⏱️ Time & Space Complexity:

- **Time:** Θ(V + E)
- **Space:** O(V)

### ✅ Pros:

- Faster than Dijkstra for 0/1 weights
- Easy to implement

### ❌ Cons:

- Only works with 0/1 weights

### 🚀 Applications:

- Grid shortest path with 0/1 cost
- Graphs with binary weight edges
- BFS-like optimization with edge cost

---

## 🛣️ Section: Shortest Path Algorithms

**🎯 Category:** Graph Algorithms

Shortest path algorithms find the minimum cost/distance from a source node to one or all other nodes. Depending on constraints (negative weights, all-pairs, heuristic search), different algorithms are optimal.

---

## 📌 1. Dijkstra’s Algorithm

### 🧠 Concept:

Greedy algorithm using a **priority queue** to always extend the minimum-cost path first. Works with **non-negative weights**.

### 🛠️ Code:

```cpp
void dijkstra(int start, vector<vector<pair<int, int>>>& adj, vector<int>& dist) {
    int n = adj.size();
    dist.assign(n, INT_MAX);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
}
```

### ⏱️ Complexity:

- **Time:** Θ((V + E) log V)
- **Space:** O(V)

### ✅ Pros:

- Efficient for sparse graphs
- Guarantees optimal path

### ❌ Cons:

- Fails with negative weights

### 🚀 Applications:

- Maps, GPS routing
- Network latency optimization

---

## ⭐ 2. A\* Search Algorithm

### 🧠 Concept:

Dijkstra + **Heuristic**. Uses `f(n) = g(n) + h(n)` where:

- `g(n)` is the cost from source
- `h(n)` is a heuristic estimate to goal

### 🛠️ Code:

```cpp
struct Node {
    int v, f;
    bool operator>(const Node& other) const { return f > other.f; }
};

void astar(int start, int goal, vector<vector<pair<int, int>>>& adj, vector<int>& h, vector<int>& dist) {
    priority_queue<Node, vector<Node>, greater<>> pq;
    dist[start] = 0;
    pq.push({start, h[start]});

    while (!pq.empty()) {
        auto [u, f] = pq.top(); pq.pop();
        if (u == goal) return;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({v, dist[v] + h[v]});
            }
        }
    }
}
```

### ⏱️ Complexity:

- **Time:** Best with admissible `h(n)`, close to Θ((V + E) log V)
- **Space:** O(V)

### ✅ Pros:

- Faster than Dijkstra when heuristic is good
- Ideal for pathfinding in grids/mazes

### ❌ Cons:

- Heuristic must be admissible and consistent
- Doesn’t work without good heuristic

### 🚀 Applications:

- AI pathfinding
- Game maps, puzzle solving

---

## ⚖️ 3. Bellman-Ford Algorithm

### 🧠 Concept:

DP-based approach that **relaxes all edges V-1 times**. Works with **negative weights** and detects negative cycles.

### 🛠️ Code:

```cpp
bool bellmanFord(int start, vector<tuple<int, int, int>>& edges, int V, vector<int>& dist) {
    dist.assign(V, INT_MAX);
    dist[start] = 0;
    for (int i = 1; i < V; ++i) {
        for (auto [u, v, w] : edges) {
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    for (auto [u, v, w] : edges) {
        if (dist[u] != INT_MAX && dist[u] + w < dist[v])
            return false; // Negative cycle
    }
    return true;
}
```

### ⏱️ Complexity:

- **Time:** Θ(V × E)
- **Space:** O(V)

### ✅ Pros:

- Handles negative weights
- Detects negative cycles

### ❌ Cons:

- Slower than Dijkstra
- Not suitable for dense graphs

### 🚀 Applications:

- Arbitrage detection
- Shortest paths with penalties

---

## 🌐 4. Floyd-Warshall Algorithm

### 🧠 Concept:

All-pairs shortest paths using **dynamic programming** over triplets (i, j, k). Works for **both positive and negative weights**, no negative cycles.

### 🛠️ Code:

```cpp
void floydWarshall(vector<vector<int>>& dist, int V) {
    for (int k = 0; k < V; ++k)
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}
```

### ⏱️ Complexity:

- **Time:** Θ(V³)
- **Space:** O(V²)

### ✅ Pros:

- Simple and powerful
- All-pairs shortest paths in one pass

### ❌ Cons:

- Not efficient for sparse graphs

### 🚀 Applications:

- Routing tables
- Shortest paths between all cities
- Transitive closure (if unweighted)

---

## 📊 Summary Table

| Algorithm      | Handles Neg Weights  | All Pairs | Time Complexity      | Best Use Case            |
| -------------- | -------------------- | --------- | -------------------- | ------------------------ |
| Dijkstra       | ❌ No                | ❌ No     | Θ((V+E) log V)       | Single-source (positive) |
| A\* Search     | ❌ (heuristic-based) | ❌ No     | Depends on heuristic | Grid pathfinding         |
| Bellman-Ford   | ✅ Yes               | ❌ No     | Θ(V × E)             | Neg edges, cycle detect  |
| Floyd-Warshall | ✅ Yes               | ✅ Yes    | Θ(V³)                | All-pairs dense graphs   |

---

## 🌲 Section: Minimum Spanning Tree (MST)

**🎯 Category:** Graph Algorithms

A **Minimum Spanning Tree (MST)** of a connected, undirected graph is a subset of the edges that connects all the vertices without cycles and with the minimum possible total edge weight.

---

## 📌 1. Kruskal’s Algorithm

### 🧠 Concept:

Sort all edges by weight and pick the smallest edge that doesn’t form a cycle. Union-Find is used to detect cycles efficiently.

### 🛠️ Code:

```cpp
struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const { return w < other.w; }
};

int find(int x, vector<int>& parent) {
    return parent[x] == x ? x : parent[x] = find(parent[x], parent);
}

bool unite(int x, int y, vector<int>& parent, vector<int>& rank) {
    int rx = find(x, parent), ry = find(y, parent);
    if (rx == ry) return false;
    if (rank[rx] < rank[ry]) swap(rx, ry);
    parent[ry] = rx;
    if (rank[rx] == rank[ry]) rank[rx]++;
    return true;
}

int kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    vector<int> parent(n), rank(n, 0);
    iota(parent.begin(), parent.end(), 0);
    int mstWeight = 0;
    for (Edge e : edges) {
        if (unite(e.u, e.v, parent, rank)) {
            mstWeight += e.w;
        }
    }
    return mstWeight;
}
```

### ⏱️ Time Complexity:

- **Θ(E log E)** — sorting edges + Union-Find
- **Space:** O(V)

### ✅ Pros:

- Works well with edge list
- Easy to code

### ❌ Cons:

- Not efficient with adjacency list

### 🚀 Applications:

- Network design
- Cost minimization in graphs

---

## 📌 2. Prim’s Algorithm (Min Heap + Adjacency List)

### 🧠 Concept:

Start from any node and grow the MST by picking the minimum-weight edge connecting the MST to an unvisited node.

### 🛠️ Code:

```cpp
int prim(int start, vector<vector<pair<int, int>>>& adj, int V) {
    vector<bool> inMST(V, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});
    int totalCost = 0;

    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (inMST[u]) continue;
        inMST[u] = true;
        totalCost += w;
        for (auto [v, weight] : adj[u]) {
            if (!inMST[v]) {
                pq.push({weight, v});
            }
        }
    }
    return totalCost;
}
```

### ⏱️ Time Complexity:

- **Θ((V + E) log V)** — with min-heap
- **Space:** O(V)

### ✅ Pros:

- Efficient with adjacency list
- Fast for dense graphs

### ❌ Cons:

- Slightly more complex to implement than Kruskal

### 🚀 Applications:

- Minimum wiring/cabling cost
- Approximation for NP-Hard problems

---

## 🧭 Section: Topological Sort

**🎯 Category:** Graph Algorithms

Topological sorting is applicable to **Directed Acyclic Graphs (DAGs)**. It provides a linear ordering of vertices such that for every directed edge `u → v`, vertex `u` comes before `v`.

---

## 📌 Conceptual Prerequisites:

- **Acyclicity:** Topo sort is only defined on DAGs
- **Indegree:** Used in Kahn’s Algorithm to count incoming edges
- **DFS Tree:** Post-order traversal of DAG gives reverse topo sort

---

## 📌 1. DFS-Based Topological Sort

### 🧠 Concept:

Use post-order traversal. Push nodes to a stack after visiting all descendants.

### 🛠️ Code:

```cpp
void dfsTopo(int u, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v])
            dfsTopo(v, adj, visited, st);
    }
    st.push(u);
}

vector<int> topoSortDFS(int V, vector<vector<int>>& adj) {
    vector<bool> visited(V, false);
    stack<int> st;
    for (int i = 0; i < V; i++) {
        if (!visited[i])
            dfsTopo(i, adj, visited, st);
    }
    vector<int> topo;
    while (!st.empty()) {
        topo.push_back(st.top()); st.pop();
    }
    return topo;
}
```

### ⏱️ Time Complexity:

- **Θ(V + E)**
- **Space:** O(V) stack + recursion

### ✅ Pros:

- Simple DFS-based
- Natural recursive structure

### ❌ Cons:

- Requires reverse postorder
- No indegree insight

### 🚀 Applications:

- Build systems, course scheduling
- Dependency resolution

---

## 📌 2. Kahn’s Algorithm (BFS-Based)

### 🧠 Concept:

Count indegrees, start with 0-indegree nodes, and remove them iteratively. If a cycle is found, the graph is not a DAG.

### 🛠️ Code:

```cpp
vector<int> topoSortKahn(int V, vector<vector<int>>& adj) {
    vector<int> indegree(V, 0);
    for (int u = 0; u < V; ++u) {
        for (int v : adj[u]) {
            indegree[v]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (int v : adj[u]) {
            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    return topo;
}
```

### ⏱️ Time Complexity:

- **Θ(V + E)**
- **Space:** O(V)

### ✅ Pros:

- Intuitive level-order like processing
- Detects cycles in DAG

### ❌ Cons:

- Queue overhead
- No recursive structure

### 🚀 Applications:

- Task scheduling
- Course prerequisite checking
- Dependency graphs

---

## 🧩 Section: Union-Find (Disjoint Set Union)

**🎯 Category:** Graph Algorithms

Union-Find is a data structure that keeps track of elements partitioned into disjoint (non-overlapping) sets. It supports **two operations** efficiently:

- `find(x)`: Determines the set representative of `x`
- `union(x, y)`: Merges the sets containing `x` and `y`

Optimizations like **path compression** and **union by rank/size** make operations nearly constant time.

---

## 📌 1. Path Compression + Union by Rank

### 🧠 Concept:

- **Path Compression** flattens the tree during `find` to make future operations faster.
- **Union by Rank** attaches the smaller tree under the root of the deeper tree to keep the tree shallow.

### 🛠️ Code:

```cpp
class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // path compression
        return parent[x];
    }

    bool unite(int x, int y) {
        int xr = find(x), yr = find(y);
        if (xr == yr) return false;
        if (rank[xr] < rank[yr])
            parent[xr] = yr;
        else if (rank[xr] > rank[yr])
            parent[yr] = xr;
        else {
            parent[yr] = xr;
            rank[xr]++;
        }
        return true;
    }
};
```

### ⏱️ Time Complexity:

- **Amortized Time:** ~Θ(α(n)) per operation (α = Inverse Ackermann Function)
- **Space:** O(n)

### ✅ Pros:

- Efficient near-constant time
- Easy to implement and use

### ❌ Cons:

- Limited to connectivity components
- Not inherently dynamic (no node deletion)

### 🚀 Applications:

- Kruskal’s Algorithm
- Cycle detection in undirected graphs
- Dynamic connectivity problems

---

## 📌 2. Cycle Detection in Undirected Graph

### 🧠 Concept:

If two vertices `u` and `v` belong to the same set and we try to union them again, it forms a **cycle**.

### 🛠️ Code:

```cpp
bool hasCycle(int V, vector<pair<int, int>>& edges) {
    DSU dsu(V);
    for (auto [u, v] : edges) {
        if (!dsu.unite(u, v)) {
            return true; // cycle detected
        }
    }
    return false;
}
```

### ⏱️ Time Complexity:

- **Θ(E × α(n))**, where α is inverse Ackermann
- **Space:** O(V)

### 🚀 Applications:

- Validating tree structure
- Redundant connection detection
- Connectivity queries

---

## 🧱 Section: Strongly Connected Components (SCC)

**🎯 Category:** Graph Algorithms

A **Strongly Connected Component (SCC)** in a directed graph is a maximal group of nodes such that every node is reachable from every other node in the group.

---

## 📌 1. Kosaraju’s Algorithm

### 🧠 Concept:

Kosaraju’s algorithm uses two passes of DFS:

1. Do a DFS and push nodes into a stack in post-order
2. Reverse the graph and do DFS in the order of the stack to extract components

### 🛠️ Code:

```cpp
void dfs1(int u, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfs1(v, adj, visited, st);
    }
    st.push(u);
}

void dfs2(int u, vector<vector<int>>& radj, vector<bool>& visited, vector<int>& component) {
    visited[u] = true;
    component.push_back(u);
    for (int v : radj[u]) {
        if (!visited[v]) dfs2(v, radj, visited, component);
    }
}

vector<vector<int>> kosaraju(int V, vector<vector<int>>& adj) {
    stack<int> st;
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) dfs1(i, adj, visited, st);
    }

    vector<vector<int>> radj(V);
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            radj[v].push_back(u);
        }
    }

    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> scc;

    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (!visited[u]) {
            vector<int> component;
            dfs2(u, radj, visited, component);
            scc.push_back(component);
        }
    }
    return scc;
}
```

### ⏱️ Time Complexity:

- **Θ(V + E)**
- **Space:** O(V + E)

### ✅ Pros:

- Easy to implement
- Simple idea with two passes

### ❌ Cons:

- Requires graph reversal

### 🚀 Applications:

- Compiler design (dependency resolution)
- Condensation graph
- Web crawling

---

## 📌 2. Tarjan’s Algorithm

### 🧠 Concept:

DFS-based algorithm using a stack, discovery time, and low-link values to find SCCs in a single pass.

### 🛠️ Code:

```cpp
int timeCounter = 0;
void tarjanDFS(int u, vector<vector<int>>& adj, vector<int>& disc, vector<int>& low,
               stack<int>& st, vector<bool>& inStack, vector<vector<int>>& scc) {
    disc[u] = low[u] = timeCounter++;
    st.push(u);
    inStack[u] = true;

    for (int v : adj[u]) {
        if (disc[v] == -1) {
            tarjanDFS(v, adj, disc, low, st, inStack, scc);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (low[u] == disc[u]) {
        vector<int> component;
        int v;
        do {
            v = st.top(); st.pop();
            inStack[v] = false;
            component.push_back(v);
        } while (u != v);
        scc.push_back(component);
    }
}

vector<vector<int>> tarjansSCC(int V, vector<vector<int>>& adj) {
    vector<int> disc(V, -1), low(V, -1);
    vector<bool> inStack(V, false);
    stack<int> st;
    vector<vector<int>> scc;
    timeCounter = 0;

    for (int i = 0; i < V; i++) {
        if (disc[i] == -1)
            tarjanDFS(i, adj, disc, low, st, inStack, scc);
    }
    return scc;
}
```

### ⏱️ Time Complexity:

- **Θ(V + E)**
- **Space:** O(V + E)

### ✅ Pros:

- One-pass
- No graph reversal

### ❌ Cons:

- Slightly harder to implement

### 🚀 Applications:

- Online SCC detection
- Game state decompositions
- Circuit component isolation

---

## 🔗 Section: Biconnected Components & Articulation Points

**🎯 Category:** Graph Algorithms

A **Biconnected Component** is a maximal set of edges such that any two edges lie on a common simple cycle. An **Articulation Point** (or cut vertex) is a vertex that, if removed, increases the number of connected components of the graph.

---

## 📌 Tarjan’s Algorithm for Articulation Points

### 🧠 Concept:

Use a DFS traversal while maintaining:

- **disc[u]** = discovery time of node `u`
- **low[u]** = lowest discovery time reachable from `u` (including back edges)

A node `u` is an articulation point if:

- `u` is the root of DFS and has ≥ 2 children
- `u` is not root and exists a child `v` such that `low[v] ≥ disc[u]`

### 🛠️ Code:

```cpp
void APUtil(int u, vector<vector<int>>& adj, vector<bool>& visited,
            vector<int>& disc, vector<int>& low, vector<int>& parent,
            vector<bool>& isAP, int& time) {
    visited[u] = true;
    disc[u] = low[u] = ++time;
    int children = 0;

    for (int v : adj[u]) {
        if (!visited[v]) {
            children++;
            parent[v] = u;
            APUtil(v, adj, visited, disc, low, parent, isAP, time);
            low[u] = min(low[u], low[v]);

            if (parent[u] == -1 && children > 1)
                isAP[u] = true;
            if (parent[u] != -1 && low[v] >= disc[u])
                isAP[u] = true;
        }
        else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

vector<int> findArticulationPoints(int V, vector<vector<int>>& adj) {
    vector<bool> visited(V, false), isAP(V, false);
    vector<int> disc(V, -1), low(V, -1), parent(V, -1);
    int time = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            APUtil(i, adj, visited, disc, low, parent, isAP, time);
    }

    vector<int> result;
    for (int i = 0; i < V; i++) {
        if (isAP[i]) result.push_back(i);
    }
    return result;
}
```

### ⏱️ Time Complexity:

- **Θ(V + E)** — DFS traversal
- **Space:** O(V)

### ✅ Pros:

- Single-pass DFS
- Detects weak points in networks

### ❌ Cons:

- Slightly complex to implement

### 🚀 Applications:

- Network reliability
- Bi-connected components extraction
- Fault-tolerant systems

---

## 🔎 Notes:

- Edge version of this algorithm can be extended to detect **bridges**
- Stack can be used to extract actual **biconnected components**

---

## 🧩 Section: Graph Properties (Hamiltonian, Eulerian, Bipartite)

**🎯 Category:** Graph Algorithms

This section explores global properties of graphs including Hamiltonian paths, Euler circuits, and bipartiteness.

---

## 📌 1. Hamiltonian Path

### 🧠 Concept:

A path that visits every vertex **exactly once**. A **Hamiltonian Circuit** ends at the starting vertex.

### ✅ Exists If:

- **Dirac’s Theorem** (n ≥ 3): if every vertex has degree ≥ n/2
- NP-Complete problem in general

### 🛠️ Backtracking Code (Naive):

```cpp
bool hamiltonianUtil(int u, vector<vector<int>>& graph, vector<bool>& visited, int count, int start) {
    if (count == graph.size()) {
        return find(graph[u].begin(), graph[u].end(), start) != graph[u].end();
    }
    for (int v : graph[u]) {
        if (!visited[v]) {
            visited[v] = true;
            if (hamiltonianUtil(v, graph, visited, count + 1, start)) return true;
            visited[v] = false;
        }
    }
    return false;
}

bool hasHamiltonianCircuit(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<bool> visited(V, false);
    visited[0] = true;
    return hamiltonianUtil(0, graph, visited, 1, 0);
}
```

### ⏱️ Time Complexity:

- **Θ(n!)** — backtracking

### 🚀 Applications:

- TSP (Traveling Salesman)
- Genome sequencing
- Puzzle solving

---

## 📌 2. Euler Circuit / Path

### 🧠 Concept:

- **Eulerian Circuit**: visits every edge exactly once and starts/ends at same vertex
- **Eulerian Path**: visits every edge once (not necessarily a cycle)

### ✅ Conditions (Undirected):

- **Circuit**: All vertices have even degree
- **Path**: Exactly 0 or 2 vertices have odd degree
- Graph must be connected

### 🛠️ Fleury’s Algorithm (Simplified):

```cpp
void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfs(v, adj, visited);
    }
}

bool isEulerian(vector<vector<int>>& adj) {
    int V = adj.size();
    vector<bool> visited(V, false);
    dfs(0, adj, visited);

    for (int i = 0; i < V; i++) {
        if (adj[i].size() % 2 != 0) return false;
    }
    return true;
}
```

### ⏱️ Time Complexity:

- **Θ(V + E)** — DFS

### 🚀 Applications:

- Route planning
- Circuit board design
- Drawing problems

---

## 📌 3. Bipartite Graph Check

### 🧠 Concept:

A graph is bipartite if we can split the nodes into two sets such that **no two nodes in the same set are adjacent**. Can be verified using **BFS or DFS coloring**.

### 🛠️ BFS Coloring:

```cpp
bool isBipartite(vector<vector<int>>& adj, int V) {
    vector<int> color(V, -1);
    for (int start = 0; start < V; start++) {
        if (color[start] != -1) continue;
        queue<int> q;
        q.push(start); color[start] = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false;
                }
            }
        }
    }
    return true;
}
```

### ⏱️ Time Complexity:

- **Θ(V + E)**

### 🚀 Applications:

- Matching problems
- Network flow
- Graph coloring problems

---

## 🧮 Section: Multistage Graphs (Layered DP)

**🎯 Category:** Graph Algorithms

A **Multistage Graph** is a directed graph where nodes are grouped into multiple stages, and all edges move from one stage to the next (i.e., acyclic and layered). The goal is to find the shortest path from the source node in the first stage to the sink node in the last stage using **dynamic programming**.

---

## 📌 Concept:

- Multistage graphs consist of `k` stages and nodes arranged such that all edges move from stage `i` to `i+1`.
- Since the graph is acyclic and ordered, we can compute the **shortest path using bottom-up DP**.

---

## 🛠️ Layered DP Algorithm:

1. Start from the last node (target) and assign distance = 0.
2. For each node from stage `k-1` to stage `1`, calculate the minimum cost to reach the destination using the formula:
   ```
   dp[u] = min(dp[v] + cost(u → v))
   ```

---

### 🛠️ C++ Code:

```cpp
int shortestPathMultistage(int V, vector<vector<pair<int, int>>>& adj, int source, int target) {
    vector<int> dp(V, INT_MAX);
    dp[target] = 0;

    for (int u = V - 1; u >= 0; --u) {
        for (auto [v, cost] : adj[u]) {
            if (dp[v] != INT_MAX)
                dp[u] = min(dp[u], cost + dp[v]);
        }
    }

    return dp[source];
}
```

- `adj[u]` contains `{v, cost}` pairs for all neighbors `v` of `u`
- `V` is the number of nodes, indexed `0` to `V-1`
- `source` is the starting node (e.g., 0), `target` is the final stage node (e.g., V-1)

---

## ⏱️ Time and Space Complexity

| Aspect           | Value    |
| ---------------- | -------- |
| Time Complexity  | Θ(V + E) |
| Space Complexity | O(V)     |

---

## ✅ Pros:

- Efficient for layered DAGs
- Clean bottom-up DP formulation

## ❌ Cons:

- Limited to multistage DAGs
- Requires ordering of stages

---

## 🚀 Applications:

- Pipeline scheduling
- Multistage decision problems
- Workflow graphs

---

## 🌿 Section: Branch and Bound

**🎯 Category:** Advanced Optimization Algorithms

Branch and Bound is a **systematic search strategy** to solve combinatorial optimization problems. It explores the **solution space as a tree**, and **prunes** paths that cannot yield a better solution than the best found so far.

---

## 📌 Core Ideas

- **Branch**: Generate subproblems by exploring possible decisions
- **Bound**: Estimate the best possible outcome from each subproblem
- **Prune**: Discard subproblems that can't beat current best (bound worse than best)

Used for solving NP-hard problems efficiently using intelligent pruning.

---

## 🧠 Key Applications

### 1. Traveling Salesman Problem (TSP)

- Find the shortest tour that visits every city exactly once and returns to the start.
- Use **lower bound heuristics** (e.g., reduced cost matrix) to prune branches.

```cpp
// Simplified TSP with branch-and-bound idea (not full implementation)
void tspBranchAndBound(...) {
    // Maintain cost, visited[], current path
    // Compute lower bound for partial paths
    // Use priority queue / recursion with pruning
}
```

### ✅ Pros:

- Much faster than brute-force for small N
- Can yield optimal solution

### ❌ Cons:

- Still exponential in worst case
- Requires good bound estimation

---

### 2. N-Queens

- Place N queens on an NxN chessboard so that no two queens attack each other.

- Use bounding to **prune placements** that result in conflicts early.

```cpp
void solveNQueens(int row, vector<string>& board, vector<vector<string>>& results) {
    if (row == board.size()) {
        results.push_back(board);
        return;
    }
    for (int col = 0; col < board.size(); ++col) {
        if (isSafe(board, row, col)) {
            board[row][col] = 'Q';
            solveNQueens(row + 1, board, results);
            board[row][col] = '.';
        }
    }
}
```

---

### 3. Job Scheduling (Minimize total tardiness)

- Minimize total delay in job completion using task order permutations
- Use bounding function (e.g., earliest finish time) to prune job orderings

---

## 🧠 Complexity Summary

| Aspect           | Value                          |
| ---------------- | ------------------------------ |
| Time Complexity  | Θ(k^n) (depending on pruning)  |
| Space Complexity | O(n) (depth of recursion tree) |

---

## ✅ Pros:

- Avoids unnecessary work through pruning
- Can yield optimal results
- More efficient than brute-force

## ❌ Cons:

- Still exponential in worst-case
- Requires clever bounding functions

---

## 🚀 Applications:

- TSP
- N-Queens
- Job Assignment
- Integer Linear Programming
- Knapsack (with bounds)

---

## 💧 Section: Flow Algorithms (Max Flow, Edmonds-Karp)

**🎯 Category:** Graph Algorithms

Flow algorithms deal with finding the **maximum amount of flow** that can be pushed from a **source** to a **sink** in a **flow network**. Each edge has a **capacity**, and flow must obey:

- Capacity constraint: flow on edge ≤ capacity
- Conservation of flows: inflow = outflow at each node (except source/sink)

---

## 📌 1. Ford-Fulkerson Method (Generic Max Flow)

### 🧠 Concept:

Repeatedly augment flow along **any available path** from source to sink using **DFS or BFS** until no more augmenting paths exist.

### 🛠️ Algorithm:

1. While there's a path from source to sink with available capacity:
   - Send flow along the path
   - Update residual capacities

- Can use **DFS (inefficient)** or **BFS (leads to Edmonds-Karp)**

### ⏱️ Time Complexity:

- Depends on path search:
  - DFS-based: O(max_flow × E)

---

## 📌 2. Edmonds-Karp Algorithm (BFS-based Ford-Fulkerson)

### 🧠 Concept:

- Implementation of Ford-Fulkerson using **BFS** to always find the **shortest augmenting path**
- Ensures polynomial time

---

### 🛠️ C++ Code:

```cpp
int bfs(int s, int t, vector<vector<int>>& capacity, vector<vector<int>>& adj, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v]) {
                parent[v] = u;
                int new_flow = min(flow, capacity[u][v]);
                if (v == t)
                    return new_flow;
                q.push({v, new_flow});
            }
        }
    }
    return 0;
}

int edmondsKarp(int n, int s, int t, vector<vector<int>>& capacity, vector<vector<int>>& adj) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while ((new_flow = bfs(s, t, capacity, adj, parent))) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}
```

---

### ⏱️ Time and Space Complexity:

| Metric           | Value                           |
| ---------------- | ------------------------------- |
| Time Complexity  | **Θ(V × E²)**                   |
| Space Complexity | **O(V²)** (for capacity matrix) |

---

## ✅ Pros:

- Polynomial time
- Easy to implement
- Guarantees max flow

## ❌ Cons:

- Inefficient for very dense graphs
- Doesn’t handle cost-based flow

---

## 🚀 Applications:

- Bipartite matching
- Image segmentation
- Airline scheduling
- Data routing
- Circulation and supply chains

---

## 🔎 Related Algorithms:

- Dinic’s Algorithm (improved with level graph + blocking flow)
- Push-Relabel (more efficient in dense graphs)
- Min-Cut = Max-Flow Theorem

---

## V. Advanced Techniques & Patterns

---

## 🌲 Section: Trie (Prefix Tree)

**🎯 Category:** Advanced Techniques & Patterns

A **Trie** (also known as a prefix tree) is a specialized tree used to efficiently store and retrieve keys in a dataset of strings. It is particularly useful for **prefix-based queries**, **autocomplete**, and **bitwise XOR optimizations**.

---

## 📌 1. Prefix Matching (Basic Trie)

### 🧠 Concept:

Each node represents a character, and edges represent transitions between characters. A path from root to leaf represents a string.

### 🛠️ Optimized C++ Implementation:

```cpp
struct TrieNode {
    TrieNode* children[26];
    bool isEnd;
    TrieNode() {
        fill(begin(children), end(children), nullptr);
        isEnd = false;
    }
};

class Trie {
    TrieNode* root;

public:
    Trie() { root = new TrieNode(); }

    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx])
                node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return node->isEnd;
    }

    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return true;
    }
};
```

### ⏱️ Complexity:

| Operation    | Time | Space           |
| ------------ | ---- | --------------- |
| Insert       | Θ(L) | O(ALPHABET × L) |
| Search       | Θ(L) | -               |
| Prefix Check | Θ(L) | -               |

- L = word length
- ALPHABET = 26 for lowercase letters

### ✅ Pros:

- Fast prefix searching
- Space-efficient for large word sets

### ❌ Cons:

- Higher memory usage compared to hashmap

### 🚀 Applications:

- Autocomplete
- Spell checking
- Dictionary matching

---

## 📌 2. Bitwise XOR Trie (for max XOR pair)

### 🧠 Concept:

Each node of the trie represents a bit (0 or 1). Traverse based on desired bit to maximize XOR result.

### 🛠️ C++ Code:

```cpp
struct TrieNode {
    TrieNode* child[2];
    TrieNode() {
        child[0] = child[1] = nullptr;
    }
};

class BitwiseTrie {
    TrieNode* root;
public:
    BitwiseTrie() { root = new TrieNode(); }

    void insert(int num) {
        TrieNode* node = root;
        for (int i = 31; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if (!node->child[bit])
                node->child[bit] = new TrieNode();
            node = node->child[bit];
        }
    }

    int maxXOR(int num) {
        TrieNode* node = root;
        int res = 0;
        for (int i = 31; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if (node->child[1 - bit]) {
                res |= (1 << i);
                node = node->child[1 - bit];
            } else {
                node = node->child[bit];
            }
        }
        return res;
    }
};
```

### ✅ Pros:

- Efficient for XOR queries
- Useful for subset bitwise operations

### ❌ Cons:

- 32 levels of tree for 32-bit integers

### 🚀 Applications:

- Maximum XOR pair
- Subarray XOR problems

---

## 📌 3. Autocomplete using Trie

### 🧠 Concept:

Traverse to the prefix node, then DFS to gather all completions from that point

### 🛠️ Autocomplete C++ Snippet:

```cpp
void dfs(TrieNode* node, string prefix, vector<string>& results) {
    if (node->isEnd) results.push_back(prefix);
    for (int i = 0; i < 26; ++i) {
        if (node->children[i])
            dfs(node->children[i], prefix + char(i + 'a'), results);
    }
}

vector<string> autocomplete(TrieNode* root, string prefix) {
    TrieNode* node = root;
    for (char c : prefix) {
        int idx = c - 'a';
        if (!node->children[idx]) return {};
        node = node->children[idx];
    }
    vector<string> results;
    dfs(node, prefix, results);
    return results;
}
```

### ⏱️ Complexity:

- **Time**: Θ(P + K), where P = prefix length, K = number of results
- **Space**: O(ALPHABET × L)

---

## 📊 Summary Table

| Operation     | Time Complexity | Space Complexity | Notes                       |
| ------------- | --------------- | ---------------- | --------------------------- |
| Insert/Search | Θ(L)            | O(ALPHABET × L)  | Standard trie operation     |
| Max XOR Query | Θ(32)           | O(32 × n)        | For 32-bit integers         |
| Autocomplete  | Θ(P + K)        | O(ALPHABET × L)  | P = prefix, K = suggestions |

---

## 📊 Section: Monotonic Stack / Queue

**🎯 Category:** Advanced Techniques & Patterns

Monotonic data structures maintain a **sorted order** of elements (increasing or decreasing) and are commonly used for range queries, nearest greater/smaller elements, and sliding window problems.

---

## 📌 1. Next Greater Element (NGE)

### 🧠 Concept:

- Use a **monotonic decreasing stack** to maintain candidate elements.
- Pop from stack while top ≤ current element.

### 🛠️ Code:

```cpp
vector<int> nextGreaterElements(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n, -1);
    stack<int> st;
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && st.top() <= nums[i]) st.pop();
        if (!st.empty()) res[i] = st.top();
        st.push(nums[i]);
    }
    return res;
}
```

### ⏱️ Complexity:

- Time: **Θ(n)**
- Space: **O(n)** (stack)

---

## 📌 2. Largest Rectangle in Histogram

### 🧠 Concept:

- For each bar, find the **first smaller to left and right**.
- Use monotonic increasing stack to get bounds.

### 🛠️ Code:

```cpp
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    stack<int> st;
    int maxA = 0;
    heights.push_back(0); // sentinel
    for (int i = 0; i < heights.size(); ++i) {
        while (!st.empty() && heights[i] < heights[st.top()]) {
            int h = heights[st.top()]; st.pop();
            int w = st.empty() ? i : i - st.top() - 1;
            maxA = max(maxA, h * w);
        }
        st.push(i);
    }
    return maxA;
}
```

### ⏱️ Complexity:

- Time: **Θ(n)**
- Space: **O(n)**

---

## 📌 3. Sliding Window Maximum (Monotonic Queue)

### 🧠 Concept:

- Maintain a **deque** of indices where values are **monotonically decreasing**.
- Remove smaller values from back and out-of-window from front.

### 🛠️ Code:

```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> res;
    for (int i = 0; i < nums.size(); ++i) {
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) res.push_back(nums[dq.front()]);
    }
    return res;
}
```

### ⏱️ Complexity:

- Time: **Θ(n)**
- Space: **O(k)**

---

## 📊 Summary Table

| Problem                | Time Complexity | Space Complexity | Technique                  |
| ---------------------- | --------------- | ---------------- | -------------------------- |
| Next Greater Element   | Θ(n)            | O(n)             | Monotonic Decreasing Stack |
| Largest Rectangle      | Θ(n)            | O(n)             | Stack with heights         |
| Sliding Window Maximum | Θ(n)            | O(k)             | Monotonic Deque            |

---

## 🔲 Section: Sliding Window Techniques

**🎯 Category:** Advanced Techniques & Patterns

The **Sliding Window** technique is used to efficiently solve problems that involve **contiguous subarrays or substrings** within a given constraint.

---

## 📌 1. Longest Substring Without Repeating Characters

### 🧠 Concept:

- Use a **hashmap** to track last index of each character.
- Maintain a moving window without repeating characters.

### 🛠️ Code:

```cpp
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> lastIndex;
    int left = 0, maxLen = 0;
    for (int right = 0; right < s.size(); ++right) {
        if (lastIndex.count(s[right])) {
            left = max(left, lastIndex[s[right]] + 1);
        }
        lastIndex[s[right]] = right;
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}
```

### ⏱️ Complexity:

- Time: **Θ(n)**
- Space: **O(26)** or **O(256)** depending on charset

---

## 📌 2. Maximum Sum Subarray of Size K

### 🧠 Concept:

- Maintain a sliding window of size **K**
- Compute sum on the fly

### 🛠️ Code:

```cpp
int maxSumSubarray(vector<int>& nums, int k) {
    int maxSum = 0, windowSum = 0;
    for (int i = 0; i < nums.size(); ++i) {
        windowSum += nums[i];
        if (i >= k) windowSum -= nums[i - k];
        if (i >= k - 1) maxSum = max(maxSum, windowSum);
    }
    return maxSum;
}
```

### ⏱️ Complexity:

- Time: **Θ(n)**
- Space: **O(1)**

---

## 📊 Summary Table

| Problem                    | Time Complexity | Space Complexity | Technique Used           |
| -------------------------- | --------------- | ---------------- | ------------------------ |
| Longest Unique Substring   | Θ(n)            | O(26~256)        | Sliding window + hashmap |
| Max Sum Subarray of Size K | Θ(n)            | O(1)             | Fixed-size window        |

---

## ➿ Section: Two Pointers

**🎯 Category:** Advanced Techniques & Patterns

The **Two Pointers** technique involves using two indices to scan data in linear time, usually from opposite ends or one leading and one trailing. It's efficient for **sorted arrays**, **merge-like operations**, and **pair-sum** type problems.

---

## 📌 1. Merging Two Sorted Arrays

### 🧠 Concept:

- Move two pointers `i` and `j` across both arrays.
- Compare and merge in sorted order.

### 🛠️ Code:

```cpp
vector<int> mergeSortedArrays(vector<int>& A, vector<int>& B) {
    int i = 0, j = 0;
    vector<int> result;
    while (i < A.size() && j < B.size()) {
        if (A[i] < B[j]) result.push_back(A[i++]);
        else result.push_back(B[j++]);
    }
    while (i < A.size()) result.push_back(A[i++]);
    while (j < B.size()) result.push_back(B[j++]);
    return result;
}
```

### ⏱️ Complexity:

- Time: **Θ(n + m)**
- Space: **O(n + m)**

---

## 📌 2. Two Sum in Sorted Array

### 🧠 Concept:

- Use one pointer from the beginning and one from the end.
- Move inward based on the sum.

### 🛠️ Code:

```cpp
pair<int, int> twoSumSorted(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == target) return {left, right};
        else if (sum < target) ++left;
        else --right;
    }
    return {-1, -1}; // Not found
}
```

### ⏱️ Complexity:

- Time: **Θ(n)**
- Space: **O(1)**

---

## 📌 3. Remove Duplicates in Sorted Array (In-place)

### 🧠 Concept:

- Maintain a slow-runner pointer `j` for position to write.
- Fast pointer `i` scans through the array.

### 🛠️ Code:

```cpp
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int j = 0;
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] != nums[j])
            nums[++j] = nums[i];
    }
    return j + 1;
}
```

### ⏱️ Complexity:

- Time: **Θ(n)**
- Space: **O(1)**

---

## 📌 4. Move Zeroes to End (Stable)

### 🧠 Concept:

- Use a pointer to track non-zero position.
- Traverse and shift non-zero elements forward.

### 🛠️ Code:

```cpp
void moveZeroes(vector<int>& nums) {
    int insertPos = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != 0) nums[insertPos++] = nums[i];
    }
    while (insertPos < nums.size()) nums[insertPos++] = 0;
}
```

### ⏱️ Complexity:

- Time: **Θ(n)**
- Space: **O(1)**

---

## 📊 Summary Table

| Problem                    | Time Complexity | Space Complexity | Description                     |
| -------------------------- | --------------- | ---------------- | ------------------------------- |
| Merge Two Sorted Arrays    | Θ(n + m)        | O(n + m)         | Classic merge operation         |
| Two Sum (Sorted)           | Θ(n)            | O(1)             | Find pair summing to target     |
| Remove Duplicates (Sorted) | Θ(n)            | O(1)             | In-place removal                |
| Move Zeroes                | Θ(n)            | O(1)             | Stable reordering of non-zeroes |

---

## 🧩 Section: Meet-in-the-Middle

**🎯 Category:** Advanced Techniques & Patterns

The **Meet-in-the-Middle (MITM)** technique is a powerful divide-and-conquer optimization used when brute-force approaches are too slow (typically Θ(2ⁿ) time). MITM reduces this by splitting the problem into halves and using preprocessing.

---

## 📌 Subset Sum using Meet-in-the-Middle

### 🧠 Concept:

- Divide the array into **two halves**
- Generate all subset sums of both halves
- Sort one half, and for each sum in the other, perform **binary search** to check for feasible complements

This reduces the complexity from **Θ(2ⁿ)** to **Θ(2ⁿ⁄² log 2ⁿ⁄²)**

---

### 🛠️ C++ Code:

```cpp
bool subsetSumMeetInMiddle(vector<int>& nums, int target) {
    int n = nums.size();
    int mid = n / 2;

    vector<int> left, right;

    // Generate all subset sums for the left half
    for (int i = 0; i < (1 << mid); ++i) {
        int sum = 0;
        for (int j = 0; j < mid; ++j)
            if (i & (1 << j)) sum += nums[j];
        left.push_back(sum);
    }

    // Generate all subset sums for the right half
    for (int i = 0; i < (1 << (n - mid)); ++i) {
        int sum = 0;
        for (int j = 0; j < (n - mid); ++j)
            if (i & (1 << j)) sum += nums[mid + j];
        right.push_back(sum);
    }

    sort(right.begin(), right.end());

    // Check for complement
    for (int x : left) {
        if (binary_search(right.begin(), right.end(), target - x))
            return true;
    }
    return false;
}
```

---

### ⏱️ Complexity:

| Metric           | Value                   |
| ---------------- | ----------------------- |
| Time Complexity  | **Θ(2ⁿ⁄² × log(2ⁿ⁄²))** |
| Space Complexity | **Θ(2ⁿ⁄²)**             |

---

## ✅ Pros:

- Drastically reduces time from Θ(2ⁿ)
- Efficient for **n ≤ 40**
- Used in tight subset/combinatoric problems

## ❌ Cons:

- Not scalable for large `n` (e.g. n > 50)
- Needs sorting and binary search

---

## 🚀 Applications:

- Subset sum
- Partitioning sets
- Combinatorial optimization
- Problems on Codeforces, AtCoder, Google Kickstart

---

## 🔁 Section: Rolling Hash

**🎯 Category:** String Algorithms / Hashing

The **Rolling Hash** technique allows computation of hash values of substrings in constant time using a precomputed hash table and power table. It is fundamental to **string matching**, **plagiarism detection**, and **duplicate substring** problems.

---

## 📌 Rabin-Karp String Matching

### 🧠 Concept:

- Hash a pattern and compare it with the hash of substrings of the text.
- Use **modular arithmetic** and polynomial hashing:
  - Hash(s) = `s[0]*p⁰ + s[1]*p¹ + ... + s[n-1]*pⁿ⁻¹ (mod m)`
- Use rolling hash to update substring hash in O(1)

---

### 🛠️ C++ Implementation:

```cpp
typedef long long ll;
const int p = 31;
const int mod = 1e9 + 9;

vector<ll> computePrefixHash(const string& s) {
    int n = s.size();
    vector<ll> hash(n + 1, 0), p_pow(n + 1, 1);
    for (int i = 1; i <= n; ++i)
        p_pow[i] = (p_pow[i - 1] * p) % mod;

    for (int i = 0; i < n; ++i)
        hash[i + 1] = (hash[i] + (s[i] - 'a' + 1) * p_pow[i]) % mod;

    return hash;
}

ll substringHash(const vector<ll>& hash, const vector<ll>& p_pow, int l, int r) {
    ll res = (hash[r + 1] - hash[l] + mod) % mod;
    res = (res * p_pow[p_pow.size() - l - 1]) % mod; // normalize
    return res;
}

vector<int> rabinKarp(const string& text, const string& pattern) {
    int n = text.size(), m = pattern.size();
    ll patHash = 0;
    vector<ll> p_pow(n + 1, 1);
    for (int i = 1; i <= n; ++i)
        p_pow[i] = (p_pow[i - 1] * p) % mod;

    for (int i = 0; i < m; ++i)
        patHash = (patHash + (pattern[i] - 'a' + 1) * p_pow[i]) % mod;

    vector<ll> hash = computePrefixHash(text);
    vector<int> result;
    for (int i = 0; i <= n - m; ++i) {
        ll currHash = (hash[i + m] - hash[i] + mod) % mod;
        if (currHash == (patHash * p_pow[i]) % mod)
            result.push_back(i);
    }
    return result;
}
```

---

## 🧠 Plagiarism Detection

### Concept:

- Compute hashes of k-length substrings (k-grams) of two documents
- Use set intersection to find how many substrings match
- Jaccard Similarity = `|A ∩ B| / |A ∪ B|`

### Snippet:

```cpp
unordered_set<ll> getKgramHashes(const string& doc, int k) {
    unordered_set<ll> hashes;
    vector<ll> hash = computePrefixHash(doc);
    vector<ll> p_pow = computePrefixHash(string(k, 'a')); // same length powers
    for (int i = 0; i <= doc.size() - k; ++i) {
        ll h = substringHash(hash, p_pow, i, i + k - 1);
        hashes.insert(h);
    }
    return hashes;
}
```

---

## ⏱️ Complexity:

| Operation         | Time Complexity  |
| ----------------- | ---------------- |
| Preprocessing     | Θ(n)             |
| Substring Hash    | Θ(1)             |
| Rabin-Karp Search | Θ(n + m) average |
| Plagiarism K-gram | Θ(n - k + 1)     |

---

## ✅ Pros:

- Efficient for substring comparison
- Works well for batch matching (many patterns)
- Hash collisions rare with good prime/mod

## ❌ Cons:

- Possible hash collisions (use double hashing)
- Need to choose base/mod carefully

---

## 🚀 Applications:

- Substring matching (Rabin-Karp)
- Detecting duplicates
- Plagiarism and similarity detection
- Rolling checksum systems (e.g. rsync)

---

## 🎲 Section: Reservoir Sampling

**🎯 Category:** Advanced Techniques & Patterns

**Reservoir Sampling** is used to randomly sample **k elements from a stream** (or very large dataset) where the total size **n is unknown or too large** to fit into memory.

---

## 📌 Problem: Random Element from a Stream

### 🧠 Concept:

- Maintain a **reservoir** of `k` elements.
- For each incoming element at index `i` (0-based):
  - If `i < k`: Add to reservoir directly
  - Else: Replace an element in the reservoir with **probability k / (i + 1)**

For **k = 1**, the probability becomes `1 / (i + 1)` to replace the current sample.

---

## 🛠️ Code (C++ - Single Random Element)

```cpp
class Solution {
private:
    int result;
    int count = 0;

public:
    void insert(int val) {
        count++;
        if (rand() % count == 0) {
            result = val;
        }
    }

    int getRandom() {
        return result;
    }
};
```

- `insert(val)` simulates the incoming stream
- `getRandom()` returns the current uniformly sampled element

---

## 🛠️ Code (C++ - Reservoir Sampling with k elements)

```cpp
vector<int> reservoirSample(vector<int>& stream, int k) {
    vector<int> reservoir(stream.begin(), stream.begin() + k);
    for (int i = k; i < stream.size(); ++i) {
        int j = rand() % (i + 1);
        if (j < k) {
            reservoir[j] = stream[i];
        }
    }
    return reservoir;
}
```

---

## ⏱️ Complexity

| Metric           | Value    |
| ---------------- | -------- |
| Time Complexity  | **Θ(n)** |
| Space Complexity | **O(k)** |

---

## ✅ Pros:

- Handles large or infinite streams
- Requires only **O(k)** space
- Guarantees uniform random sampling

## ❌ Cons:

- Only works with random access or online model
- Needs high-quality randomness source

---

## 🚀 Applications:

- Online machine learning sampling
- Random k-subset generation
- Genetic algorithms
- Load balancing and distributed systems
- Big Data systems (e.g., Apache Spark, Google Bigtable)

---

## 🔺 Section: Heap (Priority Queue)

**🎯 Category:** Advanced Techniques & Patterns

A **Heap** is a specialized binary tree-based structure that satisfies the **heap property**:

- **Min-Heap**: `parent ≤ children`
- **Max-Heap**: `parent ≥ children`

Used for **priority queues**, **top-K problems**, **heap sort**, and **scheduling**.

---

## 📌 1. Heapify (Building Heap)

### 🧠 Concept:

Convert an unsorted array into a valid heap in **O(n)** time using bottom-up approach.

### 🛠️ Code (Heapify with STL `make_heap`):

```cpp
vector<int> arr = {3, 1, 5, 7, 2};
make_heap(arr.begin(), arr.end()); // Max Heap by default
```

### 🛠️ Code (Manual Min-Heap Heapify):

```cpp
void minHeapify(vector<int>& heap, int i, int n) {
    int smallest = i, left = 2*i + 1, right = 2*i + 2;
    if (left < n && heap[left] < heap[smallest]) smallest = left;
    if (right < n && heap[right] < heap[smallest]) smallest = right;
    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        minHeapify(heap, smallest, n);
    }
}
```

---

## 📌 2. Top-K Elements from Stream or Array

### 🧠 Concept:

- Use a **Min Heap of size K** to maintain largest K elements.
- Remove root (smallest) if a bigger element comes in.

### 🛠️ Code:

```cpp
vector<int> topKElements(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k) minHeap.pop();
    }
    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }
    reverse(result.begin(), result.end());
    return result;
}
```

---

## 📌 3. Min Heap and Max Heap Operations

### Min Heap (STL):

```cpp
priority_queue<int, vector<int>, greater<int>> minHeap;
minHeap.push(10);
minHeap.push(5);
minHeap.top();     // returns 5
minHeap.pop();     // removes 5
```

### Max Heap (STL):

```cpp
priority_queue<int> maxHeap;
maxHeap.push(10);
maxHeap.push(15);
maxHeap.top();     // returns 15
maxHeap.pop();     // removes 15
```

---

## ⏱️ Complexity Table

| Operation      | Time Complexity |
| -------------- | --------------- |
| Build Heap     | **Θ(n)**        |
| Insert / Pop   | **Θ(log n)**    |
| Peek Top       | **Θ(1)**        |
| Top-K Elements | **Θ(n log k)**  |

---

## ✅ Pros:

- Fast access to max/min
- Great for dynamic top-K queries
- Useful in Dijkstra, A\*, Prim’s, scheduling

## ❌ Cons:

- No random access
- Can’t delete arbitrary elements efficiently

---

## 🚀 Applications:

- Top-K frequent elements
- Median in stream (two heaps)
- Dijkstra’s & Prim’s algorithm
- CPU Scheduling
- Merge k sorted arrays

---

## 📐 Section: Recurrence Relation Analysis - Master’s Theorem

**🎯 Category:** Complexity Analysis / Divide-and-Conquer

The **Master Theorem** provides a direct way to analyze time complexities of divide-and-conquer algorithms of the form:

```
T(n) = a · T(n/b) + f(n)
```

Where:

- `a ≥ 1` is the number of subproblems
- `b > 1` is the factor by which input size is reduced
- `f(n)` is the cost outside the recursive calls (e.g., merge step)

---

## 🎓 Master Theorem Cases:

Let `T(n) = aT(n/b) + f(n)`

### Case 1: **f(n) = O(n^log_b(a) - ε)**

- **Result:** `T(n) = Θ(n^log_b(a))`
- **Interpretation:** Work per level is dominated by the recursive calls.

### Case 2: **f(n) = Θ(n^log_b(a))**

- **Result:** `T(n) = Θ(n^log_b(a) · log n)`
- **Interpretation:** Work per level is balanced.

### Case 3: **f(n) = Ω(n^log_b(a) + ε)** and regularity condition holds

- **Condition:** `a · f(n/b) ≤ c · f(n)` for some `c < 1` and sufficiently large `n`
- **Result:** `T(n) = Θ(f(n))`
- **Interpretation:** Non-recursive work dominates.

---

## 📌 Example Applications:

### Example 1: Merge Sort

```
T(n) = 2T(n/2) + Θ(n)
```

- a = 2, b = 2 → log_b(a) = log₂2 = 1
- f(n) = Θ(n) → **Case 2**
- ✅ `T(n) = Θ(n log n)`

---

### Example 2: Binary Search

```
T(n) = T(n/2) + Θ(1)
```

- a = 1, b = 2 → log_b(a) = 0
- f(n) = Θ(1) → **Case 2**
- ✅ `T(n) = Θ(log n)`

---

### Example 3: Strassen’s Matrix Multiplication

```
T(n) = 7T(n/2) + Θ(n^2)`
```

- a = 7, b = 2 → log₂7 ≈ 2.81
- f(n) = Θ(n^2) → f(n) = O(n^log_b(a) - ε) → **Case 1**
- ✅ `T(n) = Θ(n^log₂7) ≈ Θ(n^2.81)`

---

## ⚠️ When NOT to Use Master Theorem:

- If `a` or `b` are not constants
- If the recurrence is not in the Master format
- For **non-polynomial f(n)** (e.g. f(n) = n log n when a = b = 1)
- For **subtractive** recurrences: `T(n) = T(n - 1) + f(n)`

---

## ✅ Pros:

- Quick closed-form for many recurrences
- Simplifies divide-and-conquer analysis

## ❌ Cons:

- Only works for specific form
- Needs extra methods (recursion tree, substitution) for non-conforming cases

---

## 🧠 Alternate Techniques:

- Recursion Tree Method
- Substitution / Induction Method
- Akra-Bazzi Theorem (generalized form)

---

## 🧪 Practice Problems:

- Merge Sort
- Karatsuba Multiplication
- Strassen’s Algorithm
- Ternary Search Recurrence

---

## 🧮 Section: Strassen’s Matrix Multiplication

**🎯 Category:** Divide and Conquer / Matrix Algorithms

Strassen’s algorithm is a **divide and conquer** approach to matrix multiplication that reduces the number of multiplications needed, improving time complexity from **O(n³)** to **O(n^2.81)**.

---

## 🧠 Concept:

Given two `n × n` matrices **A** and **B**, Strassen’s algorithm:

- Divides each into four `n/2 × n/2` submatrices
- Computes **7** products (instead of 8) using clever combinations:

Let:

- A = `[A11 A12; A21 A22]`
- B = `[B11 B12; B21 B22]`

Define:

```
M1 = (A11 + A22) * (B11 + B22)
M2 = (A21 + A22) * B11
M3 = A11 * (B12 - B22)
M4 = A22 * (B21 - B11)
M5 = (A11 + A12) * B22
M6 = (A21 - A11) * (B11 + B12)
M7 = (A12 - A22) * (B21 + B22)
```

Then:

```
C11 = M1 + M4 - M5 + M7
C12 = M3 + M5
C21 = M2 + M4
C22 = M1 - M2 + M3 + M6
```

---

## 📌 C++ Code:

```cpp
vector<vector<int>> add(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

vector<vector<int>> subtract(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

vector<vector<int>> strassen(vector<vector<int>> A, vector<vector<int>> B) {
    int n = A.size();
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int k = n / 2;
    vector<vector<int>> A11(k, vector<int>(k)), A12(k, vector<int>(k)),
                        A21(k, vector<int>(k)), A22(k, vector<int>(k)),
                        B11(k, vector<int>(k)), B12(k, vector<int>(k)),
                        B21(k, vector<int>(k)), B22(k, vector<int>(k));

    for (int i = 0; i < k; ++i)
        for (int j = 0; j < k; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }

    auto M1 = strassen(add(A11, A22), add(B11, B22));
    auto M2 = strassen(add(A21, A22), B11);
    auto M3 = strassen(A11, subtract(B12, B22));
    auto M4 = strassen(A22, subtract(B21, B11));
    auto M5 = strassen(add(A11, A12), B22);
    auto M6 = strassen(subtract(A21, A11), add(B11, B12));
    auto M7 = strassen(subtract(A12, A22), add(B21, B22));

    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < k; ++i)
        for (int j = 0; j < k; ++j) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + k] = M3[i][j] + M5[i][j];
            C[i + k][j] = M2[i][j] + M4[i][j];
            C[i + k][j + k] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }

    return C;
}
```

---

## ⏱️ Time and Space Complexity

| Metric           | Value                          |
| ---------------- | ------------------------------ |
| Time Complexity  | **Θ(n^log₂7)** ≈ **Θ(n^2.81)** |
| Space Complexity | **Θ(n²)**                      |

---

## ✅ Pros:

- Faster than O(n³) brute-force matrix multiplication
- Recursive and parallelizable

## ❌ Cons:

- Not cache-friendly for small matrices
- Constant factors higher than naive
- Precision errors with floating point

---

## 🚀 Applications:

- Fast matrix multiplication for large matrices
- Computer graphics
- Numerical computing and linear algebra
- Theoretical CS (sub-cubic algorithms)

---

## 🧠 Section: Row-Major vs Column-Major Order

**🎯 Category:** Memory Layout / Low-Level Data Structure

2D arrays in memory are stored in **linear (1D)** form. The way they are mapped determines cache locality and access patterns.

---

## 📌 Row-Major Order (used in C/C++)

### 🧠 Concept:

- Elements are stored **row by row**
- For 2D array `arr[i][j]`, the linearized index is:
  ```
  index = i × numCols + j
  ```

### Example:

For a 2×3 matrix:

```
arr = [ [1, 2, 3],
        [4, 5, 6] ]
```

Stored as:

```
[1, 2, 3, 4, 5, 6]
```

Access `arr[1][2] = 6` → index = `1 × 3 + 2 = 5`

---

## 📌 Column-Major Order (used in Fortran, MATLAB)

### 🧠 Concept:

- Elements are stored **column by column**
- For 2D array `arr[i][j]`, the linearized index is:
  ```
  index = j × numRows + i
  ```

### Example:

Same 2×3 matrix:

```
arr = [ [1, 2, 3],
        [4, 5, 6] ]
```

Stored as:

```
[1, 4, 2, 5, 3, 6]
```

Access `arr[1][2] = 6` → index = `2 × 2 + 1 = 5`

---

## 📊 Comparison Table

| Feature          | Row-Major Order     | Column-Major Order     |
| ---------------- | ------------------- | ---------------------- |
| Language Usage   | C, C++, Java        | Fortran, MATLAB        |
| Cache Efficiency | Better for row-wise | Better for column-wise |
| Index Formula    | `i × cols + j`      | `j × rows + i`         |

---

## ✅ Pros of Understanding:

- Improves **cache performance**
- Crucial in **image processing, matrix ops**
- Helps in implementing **flattened 2D arrays**

## ❌ Cons:

- Mistakes in mapping → hard-to-debug bugs

---

## 🚀 Applications:

- Matrix multiplication and storage
- OpenCV, graphics programming
- Parallelism and memory-efficient computation
- Flattening multidimensional arrays

---

## String Matching & Pattern Algorithms

---

## 🔤 Section: KMP (Knuth-Morris-Pratt) Algorithm

The **KMP Algorithm** efficiently finds all occurrences of a **pattern `P`** in a **text `T`** in linear time **O(n + m)** by avoiding unnecessary re-checking of characters using a **prefix table (LPS array)**.

---

## 🧠 Concept:

- KMP preprocesses the pattern to compute the **Longest Prefix which is also Suffix (LPS)** array.
- When a mismatch occurs during matching, KMP uses the LPS table to **skip** ahead rather than starting from scratch.

---

### 🧩 Prefix Table (LPS Array):

- `lps[i]` tells the length of the longest prefix which is also a suffix for `P[0..i]`
- Helps in deciding the next position to resume after a mismatch.

---

## 🛠️ Step 1: Compute LPS Array

```cpp
vector<int> computeLPS(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0;  // length of previous longest prefix suffix
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        } else {
            if (len != 0)
                len = lps[len - 1]; // fallback
            else
                lps[i++] = 0;
        }
    }
    return lps;
}
```

---

## 🛠️ Step 2: Search using KMP

```cpp
vector<int> KMPSearch(const string& text, const string& pattern) {
    int n = text.size(), m = pattern.size();
    vector<int> lps = computeLPS(pattern);
    vector<int> matches;

    int i = 0, j = 0; // i -> text, j -> pattern

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++, j++;
        }
        if (j == m) {
            matches.push_back(i - j); // match found
            j = lps[j - 1]; // continue search
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return matches;
}
```

---

## ⏱️ Time & Space Complexity

| Operation         | Time Complexity | Space Complexity |
| ----------------- | --------------- | ---------------- |
| Preprocessing LPS | Θ(m)            | Θ(m)             |
| Pattern Matching  | Θ(n)            | Θ(1)             |
| Overall           | **Θ(n + m)**    | **Θ(m)**         |

---

## ✅ Pros:

- Deterministic linear time matching
- No backtracking or repeated scanning
- Works well with repetitive patterns

## ❌ Cons:

- Slightly more complex than naive methods
- Requires extra preprocessing (LPS array)

---

## 🚀 Applications:

- Fast pattern search in strings/documents
- Plagiarism detection
- Substring search in editors/IDE
- Bioinformatics (DNA/protein sequence matching)
- Search within compressed formats

---

## 🧠 Example Dry Run:

Text: `ABABDABACDABABCABAB`  
Pattern: `ABABCABAB`

1. Compute LPS: `[0, 0, 1, 2, 0, 1, 2, 3, 4]`
2. Match starts at index **10**

---

## 📎 Visualization:

```
Text:    A B A B D A B A C D A B A B C A B A B
Pattern:         A B A B C A B A B
                 | | | | | | | | |
Match found at index 10
```

---

## 🔄 Section: Rabin-Karp Algorithm

**🎯 Category:** String Matching & Pattern Algorithms

The **Rabin-Karp Algorithm** is a hashing-based string matching technique. It computes a **rolling hash** of the pattern and the text window, enabling efficient search for multiple pattern matches in linear time (on average).

---

## 🧠 Concept:

- Treat the pattern and text substrings as numbers in a **base-p system modulo a large prime**.
- Compute the hash of the pattern and the hash of each substring of the same length in the text.
- Compare hashes; if they match, confirm with character comparison to handle collisions.

---

## 📌 Hash Function:

For a string `s` of length `m`:

```
hash(s) = s[0]*p⁰ + s[1]*p¹ + ... + s[m-1]*p^(m-1) mod M
```

- `p` is a base (commonly 31 or 53)
- `M` is a large prime (e.g., 1e9+9)

---

## 🛠️ C++ Code:

```cpp
typedef long long ll;
const int p = 31;
const int mod = 1e9 + 9;

ll computeHash(const string& s) {
    ll hash = 0, p_pow = 1;
    for (char c : s) {
        hash = (hash + (c - 'a' + 1) * p_pow) % mod;
        p_pow = (p_pow * p) % mod;
    }
    return hash;
}

vector<ll> computePrefixHash(const string& s) {
    int n = s.size();
    vector<ll> hash(n + 1, 0), p_pow(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        p_pow[i] = (p_pow[i - 1] * p) % mod;
        hash[i] = (hash[i - 1] + (s[i - 1] - 'a' + 1) * p_pow[i - 1]) % mod;
    }
    return hash;
}

vector<int> rabinKarp(const string& text, const string& pattern) {
    int n = text.size(), m = pattern.size();
    ll patHash = computeHash(pattern);
    vector<ll> hash = computePrefixHash(text);
    vector<ll> p_pow = computePrefixHash(string(n, 'a')); // just for powers
    vector<int> result;

    for (int i = 0; i <= n - m; ++i) {
        ll currHash = (hash[i + m] - hash[i] + mod) % mod;
        ll expected = (patHash * p_pow[i]) % mod;
        if (currHash == expected) {
            // optional: verify actual characters due to hash collisions
            if (text.substr(i, m) == pattern)
                result.push_back(i);
        }
    }
    return result;
}
```

---

## ⏱️ Time and Space Complexity:

| Operation               | Time Complexity |
| ----------------------- | --------------- |
| Preprocess Hash         | Θ(n)            |
| Pattern Hash            | Θ(m)            |
| Compare per window      | Θ(1)            |
| Overall (average)       | **Θ(n + m)**    |
| Worst case (collisions) | **Θ(nm)**       |
| Space                   | Θ(n)            |

---

## ✅ Pros:

- Efficient for searching multiple patterns
- Works well for long texts with few matches
- Excellent in plagiarism and fingerprint detection

## ❌ Cons:

- Possible **hash collisions** → false positives
- Requires large prime and careful mod handling
- Not always worst-case optimal

---

## 🚀 Applications:

- Substring matching in search engines
- Plagiarism detection systems
- Detecting duplicate files or data
- Approximate string matching (using multiple hashes)

---

## 🔍 Example:

Text: `"ababcabdababc"`  
Pattern: `"abc"`

- Hash(pattern) → `H1`
- Compute hash for each window of length 3
- Compare with `H1` and verify

---

## 💡 Tip:

To avoid hash collisions:

- Use **double hashing** (two different primes)
- Use **unsigned long long** + custom base

---

## 🧬 Section: Z-Algorithm

**🎯 Category:** String Matching & Pattern Algorithms

The **Z-Algorithm** computes an array `Z[]` where `Z[i]` is the **length of the longest substring starting at i** that matches the prefix of the string. It is commonly used in pattern matching and periodic substring problems.

---

## 🧠 Concept:

- Let `S = pattern + "$" + text` (use `$` as a delimiter not in pattern or text)
- Compute `Z[]` for `S`
- If any `Z[i] == length(pattern)`, a match is found at `i - pattern.length() - 1` in the text.

---

## 🔍 Z-Array Example:

```
S = a b a b a b $
Z = 0 0 4 0 2 0 0
```

Each `Z[i]` gives how much of the prefix matches at position `i`.

---

## 🛠️ Z-Function Code (C++):

```cpp
vector<int> computeZ(string s) {
    int n = s.length();
    vector<int> Z(n, 0);
    int l = 0, r = 0;

    for (int i = 1; i < n; ++i) {
        if (i <= r)
            Z[i] = min(r - i + 1, Z[i - l]);

        while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]])
            Z[i]++;

        if (i + Z[i] - 1 > r) {
            l = i;
            r = i + Z[i] - 1;
        }
    }
    return Z;
}
```

---

## 🧩 Pattern Matching with Z:

```cpp
vector<int> zSearch(const string& text, const string& pattern) {
    string combined = pattern + "$" + text;
    vector<int> Z = computeZ(combined);
    vector<int> matches;
    int m = pattern.length();

    for (int i = m + 1; i < Z.size(); ++i) {
        if (Z[i] == m) {
            matches.push_back(i - m - 1); // pattern starts at this index in text
        }
    }
    return matches;
}
```

---

## ⏱️ Time and Space Complexity

| Operation            | Time Complexity |
| -------------------- | --------------- |
| Z Array Construction | **Θ(n)**        |
| Pattern Matching     | **Θ(n + m)**    |
| Space Complexity     | **Θ(n + m)**    |

---

## ✅ Pros:

- Linear time preprocessing
- Works well for exact pattern search
- Useful for detecting **periodicity**, **prefix-suffix matches**

## ❌ Cons:

- Needs full string build-up (`pattern + $ + text`)
- Harder to generalize for approximate search

---

## 🚀 Applications:

- Pattern Matching (like KMP)
- **Longest substring which is prefix & suffix**
- **Periodicity Detection** in strings
- **Palindrome construction** (reverse + original + delimiter)

---

## 📚 Example Use Case:

Find smallest period of string `S`:

- Compute Z-array
- If `Z[i] + i == n`, then the substring of length `i` is repeating

---

## 🧠 Tip:

For palindrome problems, try:  
`Z(reverse(S) + "#" + S)` → gives you how much prefix of reverse matches suffix of original.

---

## 🌐 Section: Aho-Corasick Algorithm

**🎯 Category:** String Matching & Pattern Algorithms

The **Aho-Corasick algorithm** is a generalized string matching algorithm that efficiently finds occurrences of **multiple patterns** in a single pass over the text using a **Trie with failure links** (like a DFA built via BFS).

---

## 🧠 Concept:

- Insert all patterns into a Trie
- Compute **failure links** (similar to KMP LPS array but for Trie)
- Traverse the text using BFS over Trie nodes and failure links
- When reaching a node with matched word(s), report matches

---

## 📌 Key Components:

1. **Trie Node** with:

   - Children (char → node)
   - `fail` link (fallback pointer)
   - Output: list of matched pattern indices

2. **Failure Links**:
   - For node `v` with parent `u` and char `c`:  
     `v.fail = u.fail.children[c]`
   - Built using BFS traversal of the Trie

---

## 🛠️ C++ Code (Aho-Corasick Trie + Matching):

```cpp
struct Node {
    unordered_map<char, Node*> children;
    Node* fail = nullptr;
    vector<int> output; // pattern indices
};

class AhoCorasick {
    Node* root;
    vector<string> patterns;

public:
    AhoCorasick() {
        root = new Node();
    }

    void insert(const string& word, int index) {
        Node* node = root;
        for (char ch : word) {
            if (!node->children.count(ch))
                node->children[ch] = new Node();
            node = node->children[ch];
        }
        node->output.push_back(index);
    }

    void build() {
        queue<Node*> q;
        root->fail = root;
        for (auto& [ch, child] : root->children) {
            child->fail = root;
            q.push(child);
        }

        while (!q.empty()) {
            Node* current = q.front(); q.pop();
            for (auto& [ch, child] : current->children) {
                Node* f = current->fail;
                while (f != root && !f->children.count(ch))
                    f = f->fail;
                if (f->children.count(ch))
                    f = f->children[ch];
                child->fail = f;
                child->output.insert(child->output.end(), f->output.begin(), f->output.end());
                q.push(child);
            }
        }
    }

    unordered_map<int, vector<int>> search(const string& text) {
        unordered_map<int, vector<int>> occurrences;
        Node* node = root;

        for (int i = 0; i < text.size(); ++i) {
            char ch = text[i];
            while (node != root && !node->children.count(ch))
                node = node->fail;
            if (node->children.count(ch))
                node = node->children[ch];
            for (int patternIndex : node->output) {
                occurrences[patternIndex].push_back(i); // end of match
            }
        }
        return occurrences;
    }

    void addPattern(const string& pattern) {
        int idx = patterns.size();
        patterns.push_back(pattern);
        insert(pattern, idx);
    }

    const vector<string>& getPatterns() const {
        return patterns;
    }
};
```

---

## ⏱️ Time & Space Complexity

| Operation        | Time Complexity                 |
| ---------------- | ------------------------------- |
| Trie Build       | Θ(sum of all pattern lengths)   |
| Failure Link BFS | Θ(total trie nodes)             |
| Search Text      | Θ(n + #matches)                 |
| Space            | Θ(total characters in patterns) |

---

## ✅ Pros:

- Efficient for large dictionary-based search
- Handles **multiple patterns** simultaneously
- Avoids redundant comparisons via failure links

## ❌ Cons:

- Complex to implement
- Higher memory usage than single-pattern methods

---

## 🚀 Applications:

- **Spam filtering**
- **Virus detection**
- **Intrusion detection systems**
- **Auto-complete & text highlighting**
- **Plagiarism detection**

---

## 🔍 Example Use Case:

Search all keywords from a list:

```cpp
AhoCorasick ac;
ac.addPattern("he");
ac.addPattern("she");
ac.addPattern("his");
ac.addPattern("hers");

ac.build();
auto result = ac.search("ahishers");

for (auto& [patIdx, positions] : result) {
    cout << "Pattern '" << ac.getPatterns()[patIdx] << "' found at: ";
    for (int pos : positions)
        cout << pos << " ";
    cout << endl;
}
```

---

## 🧠 Trivia:

- Invented by Alfred V. Aho and Margaret J. Corasick in 1975
- Performs better than KMP or Rabin-Karp for many patterns

---

## 🌲 Section: Suffix Arrays / Suffix Trees

**🎯 Category:** String Matching & Pattern Algorithms

Suffix arrays and suffix trees are **powerful data structures** that enable fast substring queries, longest repeated substring detection, and efficient pattern matching in strings.

---

## 🧠 1. Suffix Array

### 🧩 Concept:

A **suffix array** is an array of integers giving the **starting positions of sorted suffixes** of a string.

For string `S = "banana"`:

- Suffixes: `"banana", "anana", "nana", "ana", "na", "a"`
- Sorted: `"a", "ana", "anana", "banana", "na", "nana"`
- Suffix Array: `[5, 3, 1, 0, 4, 2]` (starting indices)

---

### 🛠️ Suffix Array Construction (C++ – O(n log² n)):

```cpp
vector<int> buildSuffixArray(const string& s) {
    int n = s.size(), k = 0;
    vector<int> sa(n), rank(n), tmp(n);

    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rank[i] = s[i];
    }

    auto cmp = [&](int i, int j) {
        if (rank[i] != rank[j]) return rank[i] < rank[j];
        int ri = (i + k < n) ? rank[i + k] : -1;
        int rj = (j + k < n) ? rank[j + k] : -1;
        return ri < rj;
    };

    for (k = 1; k < n; k <<= 1) {
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        rank = tmp;
    }
    return sa;
}
```

---

### 🔍 LCP Array (Longest Common Prefix):

Builds an array `lcp[i] = LCP(sa[i], sa[i-1])`, useful for:

- Longest repeated substring
- Efficient range queries

```cpp
vector<int> buildLCP(const string& s, const vector<int>& sa) {
    int n = s.size();
    vector<int> rank(n), lcp(n - 1);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;

    int h = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] > 0) {
            int j = sa[rank[i] - 1];
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
            lcp[rank[i] - 1] = h;
            if (h > 0) h--;
        }
    }
    return lcp;
}
```

---

### ⏱️ Complexity

| Operation          | Time Complexity |
| ------------------ | --------------- |
| Build Suffix Array | Θ(n log² n)     |
| Build LCP Array    | Θ(n)            |
| Space              | Θ(n)            |

---

## ✅ Pros:

- Simple to implement
- Works well for pattern matching, duplicate detection

## ❌ Cons:

- Slower to construct than some alternatives
- Difficult to adapt for real-time updates

---

## 🚀 Applications:

- Fast pattern search (binary search over suffixes)
- Longest repeated substring
- Compression (e.g., BWT)
- Plagiarism detection
- Bioinformatics

---

## 🌳 2. Suffix Tree (Conceptual Overview)

### 🧠 Concept:

A **compressed trie of all suffixes** of a string `S`. Allows:

- Substring queries in O(m)
- LCS / LRS detection
- O(n) construction using **Ukkonen's algorithm**

### 🧩 Properties:

- Edges represent substrings
- Internal nodes have at least two children
- Each leaf represents a suffix

---

### 🔍 Example:

For `S = "banana$"`:

```
             ┌── ana$
         ┌───┤
         │   └── na$
    ┌────┤
    │    └──── a$
───┤
    │     ┌── na$
    └─────┤
          └──── a$
```

---

### 📚 Notes:

- Ukkonen’s Algorithm builds suffix tree in **O(n)** time.
- Difficult to code and optimize due to suffix links and edge-label compression.
- Used in **bioinformatics**, **data compression**, and **string kernels**.

---

## ⏱️ Suffix Tree Complexity

| Operation         | Time Complexity |
| ----------------- | --------------- |
| Build Suffix Tree | Θ(n) (Ukkonen)  |
| Substring Query   | Θ(m)            |
| Space             | Θ(n)            |

---

## ✅ Pros:

- Extremely fast substring queries
- Supports multiple advanced string operations

## ❌ Cons:

- Harder to implement than suffix arrays
- High constant factor in space

---

## 🚀 Applications:

- Substring existence in O(m)
- Finding repeated substrings
- Longest Common Substring
- DNA sequence analysis

---

## VIII. Time & Space Complexity Analysis

**🎯 Category:** Computational Complexity

---

### 🔼 Big O (O): Upper Bound Runtime

- Describes **worst-case growth rate**.
- `T(n) ∈ O(f(n))` ⇒ Runtime grows no faster than `f(n)` asymptotically.
- Example: Binary Search = O(log n), Merge Sort = O(n log n)

---

### 🔽 Big Ω (Omega): Lower Bound Runtime

- Describes **best-case growth rate**.
- `T(n) ∈ Ω(f(n))` ⇒ Runtime is at least `f(n)` for some input.
- Example: Linear Search = Ω(1), Merge Sort = Ω(n log n)

---

### 🟰 Big Θ (Theta): Tight Bound

- Describes **exact asymptotic behavior**.
- `T(n) ∈ Θ(f(n))` ⇔ T(n) is both O(f(n)) and Ω(f(n)).
- Example: Merge Sort = Θ(n log n)

---

### ⚖️ Amortized Analysis

- Averages costly operations over many cheap ones.

#### 📌 Examples:

- **Stack Resizing:** O(1) amortized push despite occasional O(n) resize.
- **Union-Find (w/ path compression):** O(α(n)) per op.

---

### 📉 Worst / Avg / Best Case

| Algorithm       | Best       | Avg        | Worst      |
| --------------- | ---------- | ---------- | ---------- |
| Linear Search   | O(1)       | O(n)       | O(n)       |
| Binary Search   | O(1)       | O(log n)   | O(log n)   |
| Quick Sort      | O(n log n) | O(n log n) | O(n²)      |
| Merge Sort      | O(n log n) | O(n log n) | O(n log n) |
| AVL Tree Search | O(log n)   | O(log n)   | O(log n)   |

---

### 💾 Space Complexity

| Component            | Description              | Example                  |
| -------------------- | ------------------------ | ------------------------ |
| **Recursion stack**  | Implicit function calls  | DFS = O(h), Hanoi = O(n) |
| **Auxiliary arrays** | Extra arrays used        | Merge Sort = O(n)        |
| **Dynamic memory**   | Vectors, hash maps, etc. | Dijkstra = O(V + E)      |

---

## 🧠 Key Takeaways

- **Big O** → Worst-case guarantee
- **Big Ω** → Best-case performance
- **Big Θ** → Tight asymptotic bound
- **Amortized** → Long-run average cost
- **Worst/Avg/Best** → Realistic case analysis
- **Space** → Memory efficiency matters too

---
