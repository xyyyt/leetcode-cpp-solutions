#include <iostream>

class Solution
{
public :
    int getSum(int a, int b)
    {
        constexpr int NUMBER_OF_BIT = sizeof(int) * 8;
        int sum = 0;
        uint8_t carryBit = 0;

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

            carryBit = (xor1And1) ? 1 : 0;
            sum |= (bit3 << n);
        }

        return sum;
    }
};

int main()
{
    std::cout << Solution().getSum(1, 2) << '\n';
    std::cout << Solution().getSum(2, 2) << '\n';
    std::cout << Solution().getSum(2, 3) << '\n';
    std::cout << Solution().getSum(7, 3) << '\n';
    std::cout << Solution().getSum(24, 3) << '\n';
    std::cout << Solution().getSum(17, 34) << '\n';
    std::cout << Solution().getSum(125, 250) << '\n';
    std::cout << Solution().getSum(367, 33) << '\n';
    std::cout << Solution().getSum(-1, -2) << '\n';
    std::cout << Solution().getSum(2, -2) << '\n';
    std::cout << Solution().getSum(2, -3) << '\n';
    std::cout << Solution().getSum(7, -3) << '\n';
    std::cout << Solution().getSum(-24, 3) << '\n';
    std::cout << Solution().getSum(-17, 34) << '\n';
    std::cout << Solution().getSum(125, -250) << '\n';
    std::cout << Solution().getSum(367, -33) << '\n';

    return 0;
}
