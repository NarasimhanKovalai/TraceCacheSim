#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

#include <cstdint>

namespace cache_simulator {

class MathUtils {
public:
    static bool isPowerOfTwo(uint32_t n);
    static uint32_t log2(uint32_t n);
};

} // namespace cache_simulator 

#endif // MATH_UTILS_HPP 