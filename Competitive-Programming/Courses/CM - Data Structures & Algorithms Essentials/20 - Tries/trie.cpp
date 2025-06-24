#include <bits/stdc++.h>
#include "trie.h"
using namespace std;

int main()
{
    string words[] = {"hello", "he", "apple", "aple", "news"};
    Trie t;
    for (auto word : words)
    {
        t.insert(word);
    }
    cout << t.search("hes");

    return 0;
}