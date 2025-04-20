#ifndef ADDRESS_UTILS_HPP
#define ADDRESS_UTILS_HPP

#include <cstdint>

namespace cache_simulator {

class AddressUtils {
public:
    static uint32_t getSetIndex(uint32_t address, uint32_t offsetBits, uint32_t indexMask);
    static uint32_t getTag(uint32_t address, uint32_t offsetBits, uint32_t indexBits);
};

} // namespace cache_simulator 

#endif // ADDRESS_UTILS_HPP 