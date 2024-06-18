#include <cstdint>
#include <optional>

class ModShelve
{
    public:
    ModShelve();
    ModShelve(uint16_t* mb_mem_block): mb_mem_block(mb_mem_block){};
    ~ModShelve();

    template <typename T>
    uint32_t allocate(std::optional<uint32_t> location);

    uint16_t* mb_mem_block;

};