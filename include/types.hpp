#pragma once

using int_t = long long;
using real_t = double;

constexpr real_t operator"" _r(long double x) {
    return static_cast<real_t>(x);
}

constexpr int_t operator"" _i(unsigned long long x) {
    return static_cast<int_t>(x);
}