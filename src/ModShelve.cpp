#include <cstdint>
#include "ModShelve.h"


ModShelve::ModShelve()
{
    this->mb_mem_block = nullptr;
}

ModShelve::~ModShelve()
{
}

template <typename T>
uint32_t ModShelve::allocate(std::optional<uint32_t> location)
{

}