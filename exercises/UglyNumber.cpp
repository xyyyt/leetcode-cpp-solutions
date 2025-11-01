#include <cassert>

class Solution
{
public :
    bool isUgly(int n)
    {
        while (n > 1)
        {
            if (n % 2 == 0)
            {
                n /= 2;
            }
            else if (n % 3 == 0)
            {
                n /= 3;
            }
            else if (n % 5 == 0)
            {
                n /= 5;
            }
            else
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    assert(Solution().isUgly(6));
    assert(Solution().isUgly(1));
    assert(!Solution().isUgly(14));
    assert(Solution().isUgly(8));
    assert(Solution().isUgly(27));
    assert(Solution().isUgly(25));
    assert(Solution().isUgly(30));
    assert(!Solution().isUgly(19));
    assert(Solution().isUgly(300));
    assert(!Solution().isUgly(121));

    return 0;
}
