#include <vector>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    int maxProfit(std::vector<int> prices, int fee)
    {
        return (!prices.empty() && fee >= 0) ?
            maxProfit(prices, fee, 0) : 0;
    }

private :
    [[nodiscard]]
    int maxProfit(
        const std::vector<int>& prices, int fee, int n) const
    {
        // bttbass = best time to buy and sell stock
        int bttbass = 0;

        while (n < prices.size())
        {
            int currentBTTBASS = 0;

            for (int n2 = n + 1; n2 < prices.size(); ++n2)
            {
                if (prices[n2] - prices[n] > 0)
                {
                    int bttbass = (prices[n2] - prices[n]) - fee;
                    int subBTTBASS = maxProfit(prices, fee, n2);

                    currentBTTBASS = std::max(
                        currentBTTBASS, bttbass + subBTTBASS);
                }
            }

            if (currentBTTBASS > bttbass)
            {
                bttbass = currentBTTBASS;
            }

            ++n;
        }

        return bttbass;
    }
};

int main()
{
    assert(Solution().maxProfit({1, 3, 2, 8, 4, 9}, 2) == 8);
    assert(Solution().maxProfit({1, 3, 7, 5, 10, 3}, 3) == 6);
    assert(Solution().maxProfit({1, 2, 3, 4, 5}, 1) == 3);
    assert(Solution().maxProfit({9, 7, 4, 3, 1}, 2) == 0);
    assert(Solution().maxProfit({1, 2, 1, 2, 1, 2}, 2) == 0);
    assert(Solution().maxProfit({1, 2, 1, 2, 1, 2}, 1) == 0);
    assert(Solution().maxProfit({1, 10}, 20) == 0);
    assert(Solution().maxProfit({5}, 1) == 0);

    return 0;
}
