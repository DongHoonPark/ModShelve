#define CATCH_CONFIG_MAIN

#include "catch2/catch_all.hpp"
#include <iostream>
#include <cmath>

#include "ModShelve.h"

TEST_CASE("Allocate consecutive uint16_t and check for allocation failure on already allocated addresses", "[ModShelve]") {
    uint16_t regs[100];
    auto shelve = ModShelve(regs, 100);

    // Allocate 10 consecutive uint16_t
    bool allAllocated = true;
    for (uint32_t i = 0; i < 10; ++i) {
        auto result = shelve.allocate<uint16_t>(i);
        if (!result.has_value()) {
            allAllocated = false;
            break;
        }
    }
    REQUIRE(allAllocated == true);

    // Try to allocate again at an already allocated address (address 5)
    auto repeatResult = shelve.allocate<uint16_t>(5);
    REQUIRE_FALSE(repeatResult.has_value());
}

TEST_CASE("Allocate uint16_t consecutively and then a float32_t with proper address skipping", "[ModShelve]") {
    uint16_t regs[100];
    auto shelve = ModShelve(regs, 100);

    // Allocate 3 consecutive uint16_t
    shelve.allocate<uint16_t>(0);
    shelve.allocate<uint16_t>(1);
    shelve.allocate<uint16_t>(2);

    // Now allocate a float32_t
    auto floatResult = shelve.allocate<float>(3);
    REQUIRE_FALSE(floatResult.has_value()); // Should fail because 3 is not a multiple of 4

    auto floatResultAligned = shelve.allocate<float>(4);
    REQUIRE(floatResultAligned.has_value()); // Should succeed and allocate at the next multiple of 4
}
