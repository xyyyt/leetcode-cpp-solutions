#include <cstddef>
#include <cstdint>
#include <cassert>

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
    assert(Solution().reverseBits(0)
           == 0);
    assert(Solution().reverseBits(1)
           == 2147483648);
    assert(Solution().reverseBits(2)
           == 1073741824);
    assert(Solution().reverseBits(3)
           == 3221225472);
    assert(Solution().reverseBits(43261596)
           == 964176192);
    assert(Solution().reverseBits(4294967293)
           == 3221225471);
    assert(Solution().reverseBits(0b11111111111111111111111111111111)
           == 0b11111111111111111111111111111111);
    assert(Solution().reverseBits(0b10000000000000000000000000000000)
           == 1);
    assert(Solution().reverseBits(0b00000010100101000001111010011100)
           == 0b00111001011110000010100101000000);
    assert(Solution().reverseBits(123456789)
           == 2830359264);

    return 0;
}
