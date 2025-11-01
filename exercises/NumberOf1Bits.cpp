#include <iostream>

class Solution
{
public :
    int hammingWeight(int n)
    {
        int totalOfOneSetBit = 0;

        while (n != 0)
        {
            if (n % 2 == 1)
            {
                totalOfOneSetBit++;
            }

            n /= 2;
        }

        return totalOfOneSetBit;
    }
};

int main()
{
    std::cout << Solution().hammingWeight(11) << '\n';
    std::cout << Solution().hammingWeight(128) << '\n';
    std::cout << Solution().hammingWeight(2147483645) << '\n';

    return 0;
}
