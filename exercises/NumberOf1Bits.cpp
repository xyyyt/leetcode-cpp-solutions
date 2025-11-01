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
    assert(Solution().hammingWeight(11) == 3);
    assert(Solution().hammingWeight(128) == 1);
    assert(Solution().hammingWeight(2147483645) == 30);

    return 0;
}
