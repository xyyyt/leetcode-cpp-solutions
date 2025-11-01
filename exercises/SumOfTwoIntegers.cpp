#include <cstdint>
#include <cstddef>
#include <cassert>

class Solution
{
public :
    int getSum(int a, int b)
    {
        constexpr size_t NUMBER_OF_BIT = sizeof(int) * 8;
        uint8_t carryBit = 0;
        int sum = 0;

        for (int n = 0; n < NUMBER_OF_BIT; ++n)
        {
            uint8_t bit = (a >> n) & 1;
            uint8_t bit2 = (b >> n) & 1;
            uint8_t bit3 = bit ^ bit2;
            bool xor1And1 = bit && bit2;

            if (carryBit)
            {
                if (!xor1And1)
                {
                    xor1And1 = bit3 && carryBit;
                }

                bit3 ^= carryBit;
            }

            carryBit = static_cast<uint8_t>(xor1And1);
            sum |= (bit3 << n);
        }

        return sum;
    }
};

int main()
{
    assert(Solution().getSum(1, 2) == 3);
    assert(Solution().getSum(2, 2) == 4);
    assert(Solution().getSum(2, 3) == 5);
    assert(Solution().getSum(7, 3) == 10);
    assert(Solution().getSum(24, 3) == 27);
    assert(Solution().getSum(17, 34) == 51);
    assert(Solution().getSum(125, 250) == 375);
    assert(Solution().getSum(367, 33) == 400);
    assert(Solution().getSum(-1, -2) == -3);
    assert(Solution().getSum(2, -2) == 0);
    assert(Solution().getSum(2, -3) == -1);
    assert(Solution().getSum(7, -3) == 4);
    assert(Solution().getSum(-24, 3) == -21);
    assert(Solution().getSum(-17, 34) == 17);
    assert(Solution().getSum(125, -250) == -125);
    assert(Solution().getSum(367, -33) == 334);

    return 0;
}
