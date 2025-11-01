#include <vector>
#include <cassert>

struct BestTimeToBuyAndSellStock
{
    int profit = 0;
    std::vector<std::pair<int, int>> timesToBuyAndSell;

    [[nodiscard]]
    friend bool operator>(
        const BestTimeToBuyAndSellStock& lhs,
        const BestTimeToBuyAndSellStock& rhs) noexcept
    {
        return lhs.profit > rhs.profit;
    }

    [[nodiscard]]
    friend inline BestTimeToBuyAndSellStock operator+(
        const BestTimeToBuyAndSellStock& lhs,
        const BestTimeToBuyAndSellStock& rhs)
    {
        BestTimeToBuyAndSellStock bttbass{lhs.profit + rhs.profit};
        auto fillVectorFrom = [](
            std::vector<std::pair<int, int>>& timesToBuyAndSell,
            const std::vector<std::pair<int, int>>& timesToBuyAndSellOther) -> void
        {
            timesToBuyAndSell.insert(
                timesToBuyAndSell.end(),
                timesToBuyAndSellOther.cbegin(),
                timesToBuyAndSellOther.cend());
        };

        bttbass.timesToBuyAndSell.reserve(
            lhs.timesToBuyAndSell.size() + rhs.timesToBuyAndSell.size());
        fillVectorFrom(bttbass.timesToBuyAndSell, lhs.timesToBuyAndSell);
        fillVectorFrom(bttbass.timesToBuyAndSell, rhs.timesToBuyAndSell);

        return bttbass;
    }
};

class Solution
{
public :
    int maxProfit(std::vector<int> prices)
    {
        return (!prices.empty()) ? maxProfit(prices, 0).profit : 0;
    }

private :
    [[nodiscard]]
    BestTimeToBuyAndSellStock maxProfit(
        const std::vector<int>& prices, int n) const
    {
        BestTimeToBuyAndSellStock bttbass;

        while (n < prices.size())
        {
            BestTimeToBuyAndSellStock currentBTTBASS;

            for (int n2 = n + 1; n2 < prices.size(); ++n2)
            {
                if (prices[n2] - prices[n] > 0)
                {
                    BestTimeToBuyAndSellStock bttbass{
                        prices[n2] - prices[n], {{n, n2}}};
                    BestTimeToBuyAndSellStock subBTTBASS =
                        maxProfit(prices, n2);

                    if (bttbass.profit + subBTTBASS.profit > currentBTTBASS.profit
                        && bttbass.timesToBuyAndSell.size()
                        + subBTTBASS.timesToBuyAndSell.size() < 3)
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
    assert(Solution().maxProfit({3, 3, 5, 0, 0, 3, 1, 4}) == 6);
    assert(Solution().maxProfit({1, 2, 3, 4, 5}) == 4);
    assert(Solution().maxProfit({7, 6, 4, 3, 1}) == 0);
    assert(Solution().maxProfit({2, 1, 2, 0, 1}) == 2);
    assert(Solution().maxProfit({2, 4, 1}) == 2);
    assert(Solution().maxProfit({1, 2, 3, 4, 0, 1}) == 4);
    assert(Solution().maxProfit({5, 1, 5, 1, 5}) == 8);
    assert(Solution().maxProfit({1, 10, 1, 2}) == 10);
    assert(Solution().maxProfit({1, 2, 1, 2, 1, 2}) == 2);

    return 0;
}
