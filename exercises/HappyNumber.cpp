#include <cmath>
#include <cassert>

class Solution
{
public :
    bool isHappy(int n)
    {
        n = std::abs(n);

        while (n >= 10)
        {
            int sum = 0;

            do
            {
                sum += (n % 10) * (n % 10);
                n /= 10;
            }
            while (n > 0);

            n = sum;
        }

        return n == 1;
    }
};

int main()
{
    assert(Solution().isHappy(19));
    assert(!Solution().isHappy(2));
    assert(Solution().isHappy(1));
    assert(!Solution().isHappy(-4));
    assert(Solution().isHappy(-10));
    assert(!Solution().isHappy(-16));

    return 0;
}
