#ifndef MODSHELVE_H
#define MODSHELVE_H

#include <list>
#include <utility>
#include <algorithm>
#include <cstdint>
#include <optional>

class ModShelve
{
    public:
    ModShelve();
    ModShelve(uint16_t* mb_mem_block);
    ModShelve(uint16_t* mb_mem_block, uint32_t reg_size);
    ~ModShelve();

    template <typename T>
    std::optional<T*> allocate();

    template <typename T>
    std::optional<T*> allocate(uint32_t reg_addr);

    uint16_t* mb_mem_block;

    private:
    uint32_t next_addr;
    uint32_t reg_size;

    std::list<std::pair<uint32_t, uint32_t>> allocatedRanges;
    bool allocateRange(uint32_t start, uint32_t end);
    bool isRangeAvailable(uint32_t start, uint32_t end) const;
};

// Move template definitions here
template <typename T>
std::optional<T*> ModShelve::allocate() {
    return allocate<T>(next_addr);
}

template <typename T>
std::optional<T*> ModShelve::allocate(uint32_t reg_addr) {
    constexpr auto var_size = sizeof(T);
    constexpr auto reg_size_needed = (var_size + 1) / 2;  // Assuming each register is 16 bits (2 bytes)

    if constexpr (var_size >= 4) {
        if (reg_addr % 2 == 1) {
            reg_addr += 1;
        }
    }

    // Check if the requested memory fits within the allocated block
    if (reg_addr + reg_size_needed > this->reg_size || reg_addr % 2 != 0)
        return std::nullopt; // Return empty optional if out of bounds or misaligned

    T* allocated_addr = reinterpret_cast<T*>(&this->mb_mem_block[reg_addr]);
    this->next_addr = reg_addr + reg_size_needed; // Update the next free address

    return allocated_addr; // Return the address within the Modbus memory block
}

#endif // MODSHELVE_H
