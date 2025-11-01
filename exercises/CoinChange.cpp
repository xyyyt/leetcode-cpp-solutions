#include <vector>
#include <cassert>

class Solution
{
public :
    int coinChange(const std::vector<int>& coins, int amount)
    {
        if (amount == 0)
        {
            return 0;
        }
        else if (coins.empty())
        {
            return -1;
        }

        int minStep = -1;

        for (int n = 0; n < coins.size(); ++n)
        {
            if (int res = coinChange(coins, amount, coins[n], 1, n);
                res != -1 && (minStep == -1 || minStep > res))
            {
                minStep = res;
            }
        }

        return minStep;
    }

private :
    [[nodiscard]]
    int coinChange(
        const std::vector<int>& coins,
        int amount,
        int current,
        int step,
        int n) const
    {
        int minStep = -1;

        while (true)
        {
            current += coins[n];
            step += 1;

            if (current >= amount)
            {
                break;
            }

            for (int n2 = 0; n2 < coins.size(); ++n2)
            {
                if (n2 == n)
                {
                    continue;
                }

                if (int res = coinChange(
                    coins, amount, current, step, n2);
                    res != -1 && (minStep == -1 || minStep > res))
                    {
                        minStep = res;
                    }
            }
        }

        if (current == amount && (minStep == -1 || minStep > step))
        {
            minStep = step;
        }

        return minStep;
    }
};

int main()
{
    assert(Solution().coinChange({1, 2, 5}, 11) == 3);
    assert(Solution().coinChange({2}, {3}) == -1);
    assert(Solution().coinChange({1}, {0}) == 0);
    assert(Solution().coinChange({1, 2, 5}, 0) == 0);
    assert(Solution().coinChange({7}, 14) == 2);
    assert(Solution().coinChange({7}, 13) == -1);
    assert(Solution().coinChange({1, 3, 4}, 6) == 2);
    assert(Solution().coinChange({2, 5, 10, 1}, 27) == 4);
    assert(Solution().coinChange({1, 3, 4}, 6) == 2);
    assert(Solution().coinChange({1}, 9999) == 9999);

    return 0;
}
