# ModShelve
## Introduction

ModShelve is a specialized memory management library designed to facilitate efficient memory allocation within a given memory block, particularly targeting embedded systems with constrained memory resources. The inspiration behind ModShelve emerged from the need to manage memory allocations in a structured way that ensures both alignment requirements and allocation bounds are respected, especially in systems where memory resources are critical and limited.

## Build Guide

To integrate ModShelve into your project, follow these steps using CMake:

- Prerequisite: Ensure you have CMake installed (version 3.11 or higher).
- Add ModShelve as a Subdirectory
    ```cmake
    add_subdirectory(path/to/ModShelve)
    ```
- Link ModShelve Library: Link the ModShelve library to your target application using:
    ```cmake
    target_link_libraries(YourApplication ModShelve)
    ```

## Examples
Below are examples demonstrating how to use the ModShelve library to allocate memory for both primitive types and custom structures:

### Primitive Type Allocation
```cpp
#include "ModShelve.h"

int main() {
    uint16_t memoryBlock[1024]; // Simulated memory block
    ModShelve shelve(memoryBlock, sizeof(memoryBlock) / sizeof(memoryBlock[0]));
    auto intPtr = shelve.allocate<int>(52); // Allocate integer to 52 register block
    if (intPtr) {
        *intPtr.value() = 42;
    }
    return 0;
}
```

### Custom Struct Allocation
```cpp
#include "ModShelve.h"

struct MyStruct {
    int data;
    float value;
};

int main() {
    uint16_t memoryBlock[1024]; // Simulated memory block
    ModShelve shelve(memoryBlock, sizeof(memoryBlock) / sizeof(memoryBlock[0]));

    auto structPtr = shelve.allocate<MyStruct>();
    if (structPtr) {
        structPtr.value()->data = 123;
        structPtr.value()->value = 456.78f;
    }
    return 0;
}
```
