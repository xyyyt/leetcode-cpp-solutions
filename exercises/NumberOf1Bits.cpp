#include <cassert>

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
    assert(Solution().hammingWeight(0) == 0);
    assert(Solution().hammingWeight(1) == 1);
    assert(Solution().hammingWeight(2) == 1);
    assert(Solution().hammingWeight(3) == 2);
    assert(Solution().hammingWeight(5) == 2);
    assert(Solution().hammingWeight(7) == 3);
    assert(Solution().hammingWeight(9) == 2);
    assert(Solution().hammingWeight(11) == 3);
    assert(Solution().hammingWeight(15) == 4);
    assert(Solution().hammingWeight(31) == 5);
    assert(Solution().hammingWeight(128) == 1);
    assert(Solution().hammingWeight(255) == 8);
    assert(Solution().hammingWeight(1023) == 10);
    assert(Solution().hammingWeight(2147483645) == 30);

    return 0;
}
