# Graph

- Network of vertices or nodes
- Connected via edge
- There can be weights in edges
- Weighted Graph & UnWeighted Graph
- Directed Graph & Undirected Graph

## Storing a Graph

- Adjacency List
- Adjacency Matrix
- Edge List
- 2D Matrix (Implicit Graph)

```

    0 ------ 3
    |   \
    |    \
    |     2
    |   /
    |  /
     1


```

### Adjacency List

Make a list of neighbours of each node

Can be:

- list<list>
- Arary<list>
- Vector<list>
- vector<vector>

Advantages:

- Given a node find neighbours so it can be solved easily
- Its Space Efficient

```
    0: [1, 2, 3]      // List
    1: [0, 2]
    2: [0, 1]
    3: [0]

```

### Adjacency Matrix

- Checks if there is a connection between two nodes
- You can represent both directed & undirected graph AND weighted & unweighted graph

Disadvantage:

- Too much of memory needed
- To check neighbour it will always be O(V)

```
     0 1 2 3

0    0 1 1 1
1    1 0 1 0
2    1 1 0 0
3    1 0 0 0

Space: O(V^2)
```

### Edge List

- When we have to do sorting based upon weights like minimum spanning tree & not find neighbours

- List of triplets in which we are storing weight, source and destination. Eg: (6, A, B)

```
    Edges = {(0 , 1), (0 , 3), (0 , 2), (2 , 1)}
```

### Implicit Graph / 2D Matrix

- You are in a 2D matrix and find shortest route to reach a point
- Assume each node is connected with 4 neighbours
- Sometimes it can be 8 way connectivity in which we will travel in diagonals too
- Example use: flood fill

## Applications of Graph

- Shortest Path
- Social Networks
- Shortest cyclic route where we cover all locations and come back to original one
- Resolving Dependencies like in a server module a is dependent on b then on c and so on. Right order in which this should be resolved. Such graphs are called as **directed acyclic graphs (DAG)**
- Routing Algorithms
- Machine Learning
- Computer Vision
- Web Crawlers
- Physics & Chem
- Graph Database

## Graph Traversals

### Breadth First Search (BFS)

```
      2 ------- 3
     /         / \
    /         /   5
   1         / /   \
     \       4      6
      \     /
         0
```

```
Lets start from 1

Take a queue

Push 1 and its neighbours and mark them as visited

Maintain a bool array of visited or not0

=> 1  2  0  3  4  5  6
```

- O(V + E) Time

### DFS

```

    DFS(6)
    DFS(5)
    DFS(4)
    DFS(3)
    DFS(2)
    DFS(1)

When coming back,

    DFS(0)
    DFS(4)
    DFS(3)
    DFS(2)
    DFS(1)

One possible output: 1 2 3 4 5 6 0

Depends on what order we are making our adjacency List
```

- O(V + E) Time

## Topological Sorting

- Sorting Algo for Directed Acyclic Graph (DAG)
- It is a linear ordering of vertices such that every directed edge u v, vertex u comes before v in the ordering.
- Not possible is grpah is not a DAG.

### Applications:

- scheduling jobs from the given dependencies among jobs.
- instruction scheduling
- ordering of formula cell evaluation when recomputing formula values in spreadsheets
- logic synthesis
- determining the order of compilation tasks to perform in make files, data serialization, and resolving symbol dependencies in linkers

### Kahn's Algorithm

```

                0
1             /
|   \        /
|     ->2  <-
-> 4     \
    \     -> 3
     \      /
      ->5 <-
```

indegree = no. of edges that are incoming to that node

- Make a indegree of every node
- Start from 0 and put it in a queue
- Reduce indegree by 1 from its nieghbouring node
- Similarly go for the nodes with indegree 0
- and add them to queue

**Output:**
1 0 4 2 3 5

**Complexity:** O(V+E)

## Dijkshtra's Algorithm for shortes Paths

- weighted graphs
- Single source shortest paths (SSSP)
- We take a source node form where distance to all other nodes will be computed including destination
