#include <cassert>

class Solution
{
public :
    int nthUglyNumber(int n)
    {
        int uglyNumberCounter = 0;
        int i = 0;

        while (uglyNumberCounter < n)
        {
            ++i;

            bool isUglyNumber = true;

            for (int j = 1; j < i; ++j)
            {
                if (i % j == 0 && j != 1 && j != 2 && j != 3 && j != 5)
                {
                    isUglyNumber = false;

                    break;
                }
            }

            if (isUglyNumber)
            {
                ++uglyNumberCounter;
            }
        }

        return i;
    }
};

int main()
{
    assert(Solution().nthUglyNumber(10) == 11);
    assert(Solution().nthUglyNumber(1) == 1);

    return 0;
}
