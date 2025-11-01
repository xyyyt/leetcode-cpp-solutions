#include <cassert>

class Solution
{
public :
    bool isUgly(int n)
    {
        for (int i = 1; i < n; ++i)
        {
            if (n % i == 0 && i != 1 && i != 2 && i != 3 && i != 5)
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

    return 0;
}
