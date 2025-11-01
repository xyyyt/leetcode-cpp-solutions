#include <vector>
#include <cassert>

class Solution
{
public :
    int maxProfit(std::vector<int> prices)
    {
        // bttass = best time to buy and sell stock
        int bttbass = 0;

        for (int n = 0; n < prices.size() - 1; ++n)
        {
            for (int n2 = n + 1; n2 < prices.size(); ++n2)
            {
                int bttbass2 = prices[n2] - prices[n];

                if (bttbass2 > bttbass)
                {
                    bttbass = bttbass2;
                }
            }
        }

        return bttbass;
    }
};

int main()
{
    assert(Solution().maxProfit({7, 1, 5, 3, 6, 4}) == 5);
    assert(Solution().maxProfit({7, 6, 4, 3, 1}) == 0);

    return 0;
}
