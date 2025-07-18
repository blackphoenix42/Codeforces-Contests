#pragma once
#include "utils.hpp"
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;

struct CustomHash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
struct PairHash {
    size_t operator()(const pair<int, int> &p) const {
        return CustomHash{}(((uint64_t)p.first << 32) | p.second);
    }
};
struct TupleHash {
    size_t operator()(const tuple<int, int, int> &t) const {
        auto [a, b, c] = t;
        size_t h1 = CustomHash{}(a);
        size_t h2 = CustomHash{}(b);
        size_t h3 = CustomHash{}(c);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

// gp_hash_table<ll, int, CustomHash> mp;

template <typename K, typename V>
using safe_umap = unordered_map<K, V, CustomHash>;

template <typename K>
using safe_uset = unordered_set<K, CustomHash>;
