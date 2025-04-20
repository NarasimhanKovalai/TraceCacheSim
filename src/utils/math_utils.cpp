#include "utils/math_utils.hpp"
#include <cmath>

namespace cache_simulator {

bool MathUtils::isPowerOfTwo(uint32_t n) {
    return (n != 0) && ((n & (n - 1)) == 0);
}

uint32_t MathUtils::log2(uint32_t n) {
    return static_cast<uint32_t>(std::log2(n));
}

} // namespace cache_simulator 