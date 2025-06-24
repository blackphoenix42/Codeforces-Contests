## Binary AND `&`

```
0 & 0 = 0
1 & 0 = 0
0 & 1 = 0
1 & 1 = 1
```

## Binary OR `|`

```
0 | 0 = 0
1 | 0 = 1
0 | 1 = 1
1 | 1 = 1
```

## Binary XOR `^`

- Exclusive OR
- If boths bits same it will be `0` else `1`

```
0 ^ 0 = 0
1 ^ 1 = 0
1 ^ 0 = 1
0 ^ 1 = 1
```

## Binary NOT `~`

- It even changes the Most Significant Bit i.e. + or - sign

```
Bits:
~0 = 1
~1 = 0
```

```cpp
int a = 0;
cout << ~a; // -1
```

**Explaination:**

In the above `0` is an integer not a single bit. Thats why its not `1`

`0` can be represented as `0000000000...0` (32 bits)

`~0 ` => `111111...1`

_The left most bit is the MSB which represents the sign. So, 1 means a -ve number and 0 means +ve number_

.In this case its **-ve**

Take the rest 31 bits, i.e., `111111...1`

These bits are stored in memory as **2's compliment**

**2's Compliment => Invert all the bits and add 1 in it**

So,`111111...1` => `000000...0`

Add 1, `000000...0 + 1 => 1`

As we know MSB was -ve so answer is **`-1`**

## Binary Left Shift `<<`

```
5 = 0 0 0 0 1 0 1

5 << 2 => 0 0 1 0 1 0 0

```

- **Formula: `a << b => a * 2^b`**

## Binary Right Shift `>>`

```
10 = 0 0 1 0 1 0

10 >> 1 => 0 0 0 1 0 1

10 >> 4 => 10 / 2^4 => 10 / 16 => 0
```

- **Formula: `a >> b => a / 2^b`**

## Notes

- Odd - Even tips

```
All odd numbers has last bit (right most) as 1
All even numbers has last bit (right most) as 0
1 = 0000001
2 = 0000010
3 = 0000011
```


## Property

- A number will have at most `logN` number of bits (i.e. the leftmost set bit). In worst case `logN +1`