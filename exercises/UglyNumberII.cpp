#include <iostream>

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
    std::cout << Solution().nthUglyNumber(10) << '\n';
    std::cout << Solution().nthUglyNumber(1) << '\n';

    return 0;
}
