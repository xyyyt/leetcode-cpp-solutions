#include <vector>
#include <algorithm>
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
        const std::vector<int>& prices, int n) const
    {
        // bttbass = best time to buy and sell stock
        int bttbass = 0;

        while (n < prices.size())
        {
            int currentBTTBASS = 0;
            int n2 = n + 1;

            while (n2 < prices.size())
            {
                if (prices[n2] - prices[n] > 0)
                {
                    int bttbass = prices[n2] - prices[n];

                    n2 += 2;

                    int subBTTBASS = maxProfit(prices, n2);

                    currentBTTBASS = std::max(
                        currentBTTBASS, bttbass + subBTTBASS);
                }
                else
                {
                    ++n2;
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
    assert(Solution().maxProfit({1, 2, 3, 0, 2}) == 3);
    assert(Solution().maxProfit({1}) == 0);

    return 0;
}
