#pragma once
#include "utils.hpp"

namespace cp::bit {
#define setbits(x) __builtin_popcountll(x)
#define parity(x) (__builtin_parityll(x))
#define clz(x) __builtin_clzll(x)
#define ctz(x) __builtin_ctzll(x)
#define ffs(x) __builtin_ffsll(x)
int count_bits(int x) { return __builtin_popcount(x); }
int trailing_zeros(int x) { return __builtin_ctz(x); }
void iterate_submasks(int mask, std::function<void(int)> callback) {
    for (int sub = mask; sub; sub = (sub - 1) & mask) {
        callback(sub);
    }
}
}  // namespace cp::bit