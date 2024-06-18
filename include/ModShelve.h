#include <cstdint>
#include <optional>

class ModShelve
{
    public:
    ModShelve();
    ModShelve(uint16_t* mb_mem_block): mb_mem_block(mb_mem_block){};
    ~ModShelve();

    template <typename T>
    std::optional<T*> allocate();

    template <typename T>
    std::optional<T*> allocate(uint32_t reg_addr);

    uint16_t* mb_mem_block;

    private:
    uint32_t last_alloc_addr;
};