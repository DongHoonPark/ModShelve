#include <cstdint>
#include <optional>
#include "ModShelve.h"


ModShelve::ModShelve()
{
    this->mb_mem_block = nullptr;
    this->next_addr = 0;
}

ModShelve::ModShelve(uint16_t* mb_mem_block): mb_mem_block(mb_mem_block){
    this->next_addr = 0;
};

ModShelve::ModShelve(uint16_t* mb_mem_block, uint32_t reg_size): mb_mem_block(mb_mem_block), reg_size(reg_size)
{
    this->next_addr = 0;
};

ModShelve::~ModShelve()
{
}

bool ModShelve::allocateRange(uint32_t start, uint32_t end)
{        
    if (!isRangeAvailable(start, end)) {
        return false;  // Reject allocation if there's an overlapping range
    }

    // Check for possible merging with existing ranges before adding the new range
    for (auto it = allocatedRanges.begin(); it != allocatedRanges.end(); ++it) {
        if (it->second + 1 == start) {
            // If the current range's end is directly before the new range's start
            start = it->first;  // Extend the new range's start to the current range's start
            allocatedRanges.erase(it);  // Remove the current range
            break;  // Break to avoid duplicate checking
        } else if (end + 1 == it->first) {
            // If the new range's end is directly before the current range's start
            end = it->second;  // Extend the new range's end to the current range's end
            allocatedRanges.erase(it);  // Remove the current range
            break;  // Break to avoid duplicate checking
        }
    }

    // Add the merged or new range to the list
    allocatedRanges.emplace_back(start, end);
    // Sort the ranges to facilitate processing of continuous segments
    allocatedRanges.sort([](const auto& a, const auto& b) { return a.first < b.first; });

    return true;
}

bool ModShelve::isRangeAvailable(uint32_t start, uint32_t end) const {
    for (const auto& range : allocatedRanges) {
        if (!(end < range.first || start > range.second)) {
            return false;  // Return false if there is an overlap
        }
    }
    return true;  // Return true if there is no overlap
}