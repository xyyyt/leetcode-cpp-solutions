#include <cassert>

class Solution
{
public :
    int climbStairs(int n)
    {
        return (n >= 1) ? climbStairs(n, 0) : 0;
    }

private :
    [[nodiscard]]
    int climbStairs(int n, int step) const noexcept
    {
        if (step > n)
        {
            return 0;
        }
        else if (step == n)
        {
            return 1;
        }

        int reachTopCounter = 0;

        reachTopCounter += climbStairs(n, step + 1);
        reachTopCounter += climbStairs(n, step + 2);

        return reachTopCounter;
    }
};

int main()
{
    assert(Solution().climbStairs(0) == 0);
    assert(Solution().climbStairs(1) == 1);
    assert(Solution().climbStairs(2) == 2);
    assert(Solution().climbStairs(3) == 3);
    assert(Solution().climbStairs(4) == 5);
    assert(Solution().climbStairs(5) == 8);
    assert(Solution().climbStairs(10) == 89);
    assert(Solution().climbStairs(20) == 10946);

    return 0;
}
