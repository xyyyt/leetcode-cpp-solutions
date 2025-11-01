#include <vector>
#include <optional>
#include <algorithm>
#include <iostream>

struct BestTimeToBuyAndSellStock
{
    int profit = 0;
    std::optional<std::pair<int, int>> timeToBuyAndSell;

    [[nodiscard]]
    friend bool operator>(
        const BestTimeToBuyAndSellStock& lhs,
        const BestTimeToBuyAndSellStock& rhs) noexcept
    {
        return lhs.profit > rhs.profit;
    }

    friend std::ostream& operator<<(
        std::ostream& os,
        const BestTimeToBuyAndSellStock& bttbass) noexcept
    {
        // os << "Best profit : "
        //    << bttbass.profit
        //    << " | Time to buy and sell : ";

        if (bttbass.timeToBuyAndSell)
        {
            const auto& value = bttbass.timeToBuyAndSell.value();

            os << value.first
               << ", "
               << value.second;
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
    BestTimeToBuyAndSellStock maxProfit(std::vector<int> prices)
    {
        BestTimeToBuyAndSellStock bttbass;

        for (int n = 0; n < prices.size() - 1; ++n)
        {
            for (int n2 = n + 1; n2 < prices.size(); ++n2)
            {
                BestTimeToBuyAndSellStock bttbass2{
                    prices[n2] - prices[n], std::make_pair(n, n2)};

                if (bttbass2.profit > bttbass.profit)
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
    std::cout << Solution().maxProfit({7, 1, 5, 3, 6, 4}) << '\n';
    std::cout << Solution().maxProfit({7, 6, 4, 3, 1}) << '\n';

    return 0;
}
