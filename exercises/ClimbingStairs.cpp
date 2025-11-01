#include <iostream>

class Solution
{
public :
    int climbStairs(int n)
    {
        return climbStairs(n, 0);
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
    std::cout << Solution().climbStairs(2) << '\n';
    std::cout << Solution().climbStairs(3) << '\n';

    return 0;
}
