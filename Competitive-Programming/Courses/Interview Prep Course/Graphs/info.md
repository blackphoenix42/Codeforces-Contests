```
0 -> 1
 \   |
  -> 2
     |
     3

```

# Ways to represent graph

### Adj Matrix

|     | 0   | 1   | 2   | 3   |
| --- | --- | --- | --- | --- |
| 0   |     | T   | T   |     |
| 1   |     |     | T   |     |
| 2   |     | T   |     | T   |
| 3   |     | T   |     |     |

### Edge List: Edges & Vertices

```
V = {0,1,2,3}
E = [(0,1) (0,2) (1,2) (2,1) (2,3) (3,2)]
```

### Adj List

```
0 -> 1,2
1 -> 2
2 -> 1,3
3 -> 2
```

Can make a hashmap node as a key and its neighbours as list

```
{
    0 : [1,2],
    1 : [2],
    2 : [1,3],
    3 : [2]
}
```

### Implicit Graph
