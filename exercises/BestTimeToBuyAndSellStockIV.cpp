#include <vector>
#include <iostream>

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
    friend BestTimeToBuyAndSellStock operator+(
        const BestTimeToBuyAndSellStock& lhs,
        const BestTimeToBuyAndSellStock& rhs)
    {
        BestTimeToBuyAndSellStock bttbass{lhs.profit + rhs.profit};
        auto fillVectorFrom = [](
            std::vector<std::pair<int, int>>& timesToBuyAndSell,
            const std::vector<std::pair<int, int>>& timesToBuyAndSellOther)
        {
            for (auto [timeToBuy, timeToSell] : timesToBuyAndSellOther)
            {
                timesToBuyAndSell.emplace_back(timeToBuy, timeToSell);
            }
        };

        fillVectorFrom(bttbass.timesToBuyAndSell, lhs.timesToBuyAndSell);
        fillVectorFrom(bttbass.timesToBuyAndSell, rhs.timesToBuyAndSell);

        return bttbass;
    }

    friend std::ostream& operator<<(
        std::ostream& os,
        const BestTimeToBuyAndSellStock& bttbass) noexcept
    {
        // os << "Best profit : "
        //    << bttbass.profit
        //    << " | Times to buy and sell : ";

        if (auto begin = bttbass.timesToBuyAndSell.cbegin(),
            end = bttbass.timesToBuyAndSell.cend();
            begin != end)
        {
            os << '[' << begin->first << ", " << begin->second << ']';
            ++begin;

            while (begin != end)
            {
                os << '[' << begin->first << ", " << begin->second << ']';
                ++begin;
            }
        }
        else
        {
            os << "EMPTY";
        }

        return os;
    }
};

class Solution
{
public :
    BestTimeToBuyAndSellStock maxProfit(std::vector<int> prices, int k)
    {
        return maxProfit(prices, k, 0);
    }

private :
    [[nodiscard]]
    BestTimeToBuyAndSellStock maxProfit(
        const std::vector<int>& prices, int k, int n)
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
                        maxProfit(prices, k, n2);

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
    std::cout << Solution().maxProfit({2, 4, 1}, 2) << '\n';
    std::cout << Solution().maxProfit({3, 2, 6, 5, 0, 3}, 2) << '\n';

    return 0;
}
