#include <cmath>
#include <cassert>

class Solution
{
public :
    int addDigits(int num)
    {
        int res = std::abs(num);

        while (res >= 10)
        {
            int sum = 0;

            do
            {
                sum += res % 10;
                res /= 10;
            }
            while (res > 0);

            res = sum;
        }

        return (num < 0) ? -res : res;
    }
};

int main()
{
    assert(Solution().addDigits(38) == 2);
    assert(Solution().addDigits(0) == 0);
    assert(Solution().addDigits(127) == 1);
    assert(Solution().addDigits(6) == 6);
    assert(Solution().addDigits(-27) == -9);
    assert(Solution().addDigits(-4) == -4);

    return 0;
}
