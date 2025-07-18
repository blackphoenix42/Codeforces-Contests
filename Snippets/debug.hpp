#pragma once
#include "utils.hpp"

// Debugging
#ifdef LOCAL
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "] = ", debug_out(__VA_ARGS__)
#define dbg_idx(v) cerr << "[" #v "] = ", _print_with_index(v), cerr << '\n'
#else
#define dbg(...)
#define dbg_idx(v)
#endif

// Debug print helpers for primitive and STL types
// Primitive types
void _print(int x) { cerr << x; }
void _print(bool x) { cerr << (x ? "true" : "false"); }
void _print(ll x) { cerr << x; }
void _print(char x) { cerr << x; }
void _print(string x) { cerr << x; }
void _print(const double &x) { cerr << x; }
void _print(ld x) { cerr << x; }
void _print(ull x) { cerr << x; }

// STL Containers
template <typename T, typename V>
void _print(const pair<T, V> &p) {
    cerr << "{";
    _print(p.fi);
    cerr << ", ";
    _print(p.se);
    cerr << "}";
}
template <typename T>
void _print(const vector<T> &v) {
    cerr << "[ ";
    for (const auto &i : v) {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <typename T>
void _print_with_index(const vector<T> &v) {
    cerr << "[\n";
    for (size_t i = 0; i < v.size(); ++i) {
        cerr << "  [" << i << "]: ";
        _print(v[i]);
        cerr << '\n';
    }
    cerr << "]";
}
template <typename T>
void _print(const vector<vector<T>> &v) {
    cerr << "[\n";
    for (const auto &row : v) {
        cerr << "  ";
        _print(row);
        cerr << "\n";
    }
    cerr << "]";
}
template <typename T>
void _print(const set<T> &s) {
    cerr << "{ ";
    for (const auto &i : s) {
        _print(i);
        cerr << " ";
    }
    cerr << "}";
}
template <typename T>
void _print(const unordered_set<T> &s) {
    cerr << "{ ";
    for (const auto &i : s) {
        _print(i);
        cerr << " ";
    }
    cerr << "}";
}
template <typename T>
void _print(const multiset<T> &s) {
    cerr << "{ ";
    for (const auto &i : s) {
        _print(i);
        cerr << " ";
    }
    cerr << "}";
}
template <typename K, typename V>
void _print(const map<K, V> &m) {
    cerr << "{ ";
    for (const auto &p : m) {
        cerr << "[";
        _print(p.first);
        cerr << ": ";
        _print(p.second);
        cerr << "] ";
    }
    cerr << "}";
}
template <typename K, typename V>
void _print(const unordered_map<K, V> &m) {
    cerr << "{ ";
    for (const auto &p : m) {
        cerr << "[";
        _print(p.first);
        cerr << ": ";
        _print(p.second);
        cerr << "] ";
    }
    cerr << "}";
}
template <typename T>
void _print(const deque<T> &d) {
    cerr << "[ ";
    for (const auto &i : d) {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <typename T>
void _print(queue<T> q) {
    cerr << "[ ";
    while (!q.empty()) {
        _print(q.front());
        cerr << " ";
        q.pop();
    }
    cerr << "]";
}
template <typename T>
void _print(priority_queue<T> pq) {
    vector<T> temp;
    while (!pq.empty()) {
        temp.push_back(pq.top());
        pq.pop();
    }
    _print(temp);
}
template <typename T>
void _print(stack<T> s) {
    vector<T> temp;
    while (!s.empty()) {
        temp.push_back(s.top());
        s.pop();
    }
    reverse(temp.begin(), temp.end());
    _print(temp);
}
// Other types
template <typename T1, typename T2, typename T3>
void _print(const tuple<T1, T2, T3> &t) {
    cerr << "(";
    _print(get<0>(t));
    cerr << ", ";
    _print(get<1>(t));
    cerr << ", ";
    _print(get<2>(t));
    cerr << ")";
}
template <size_t N>
void _print(const bitset<N> &b) {
    cerr << b.to_string();
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    _print(H);
    if (sizeof...(T)) cerr << ", ";
    debug_out(T...);
}
