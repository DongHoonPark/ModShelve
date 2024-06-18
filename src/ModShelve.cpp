#include <cstdint>
#include <optional>
#include "ModShelve.h"


ModShelve::ModShelve()
{
    this->mb_mem_block    = nullptr;
    this->last_alloc_addr = 0;
}

ModShelve::~ModShelve()
{
}

template <typename T>
std::optional<T *> ModShelve::allocate()
{
    return allocate(last_alloc_addr + 1);
}

template <typename T>
std::optional<T *> ModShelve::allocate(uint32_t reg_addr)
{
    auto var_size = sizeof(T);
    if(var_size % 2)
    {
        return 
    }
}