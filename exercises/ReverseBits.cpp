#include <cstdint>
#include <iostream>

class Solution
{
public :
    uint32_t reverseBits(uint32_t n)
    {
        constexpr size_t NUMBER_OF_BIT = sizeof(uint32_t) * 8;
        uint32_t n2 = 0;

        for (int i = 0; i < NUMBER_OF_BIT; ++i)
        {
            uint8_t bit = (n >> i) & 1;

            n2 |= bit << ((NUMBER_OF_BIT - 1) - i);
        }

        return n2;
    }
};

int main()
{
    std::cout << Solution().reverseBits(43261596) << '\n';
    std::cout << Solution().reverseBits(4294967293) << '\n';

    return 0;
}
