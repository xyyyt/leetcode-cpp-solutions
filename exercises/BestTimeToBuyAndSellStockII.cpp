#include <vector>
#include <cassert>

class Solution
{
public :
    int maxProfit(std::vector<int> prices)
    {
        return maxProfit(prices, 0);
    }

private :
    [[nodiscard]]
    int maxProfit(
        const std::vector<int>& prices, int n)
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
                    int bttbass = prices[n2] - prices[n];
                    int subBTTBASS = maxProfit(prices, n2);

                    if (bttbass + subBTTBASS > currentBTTBASS)
                    {
                        currentBTTBASS = bttbass + subBTTBASS;
                    }
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
    assert(Solution().maxProfit({7, 1, 5, 3, 6, 4}) == 7);
    assert(Solution().maxProfit({1, 2, 3, 4, 5}) == 4);
    assert(Solution().maxProfit({7, 6, 4, 3, 1}) == 0);

    return 0;
}
