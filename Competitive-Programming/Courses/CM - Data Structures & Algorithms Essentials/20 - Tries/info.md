# Tries

- Important Data structure for pattern Matching Problems

```

Sample Problem - Given a list of strings and Q queries , each query containing a word, you have to tell whether the word is contained in the list or not.

Sample Input
    words [] = {"apple", "ape", "mango", "news", "no"}

    queries [] = {"apple", "banana", "new", "mango"}

Sample Output

    Yes, No, No, Yes

w = word length
- Insert: n * O(w)
- Search: o(w)

```

## Prefix Tree / Trie

- Generic Tree like data structure. Every node can have multiple children.
- Efficient Info Retrieval Data Structure
- Searches in Optimal TIme `O(key length)` but uses **Extra Storage**

Imp Operations

- Insert a new word
- Search for a given word
- Deletion (but rarely used)

## Time & Space

```
N words

N = no. of words
L = Length of word


O(NL) to build word

O(L)

```
