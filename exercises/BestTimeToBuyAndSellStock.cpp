#include <vector>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    int maxProfit(std::vector<int> prices)
    {
        if (prices.empty())
        {
            return 0;
        }

        // bttbass = best time to buy and sell stock
        int bttbass = 0;

        for (int n = 0; n < prices.size() - 1; ++n)
        {
            for (int n2 = n + 1; n2 < prices.size(); ++n2)
            {
                bttbass = std::max(
                    bttbass, prices[n2] - prices[n]);
            }
        }

        return bttbass;
    }
};

int main()
{
    assert(Solution().maxProfit({}) == 0);
    assert(Solution().maxProfit({5}) == 0);
    assert(Solution().maxProfit({1, 5}) == 4);
    assert(Solution().maxProfit({5, 1}) == 0);
    assert(Solution().maxProfit({7, 1, 5, 3, 6, 4}) == 5);
    assert(Solution().maxProfit({7, 6, 4, 3, 1}) == 0);
    assert(Solution().maxProfit({2, 1, 2, 1, 3}) == 2);
    assert(Solution().maxProfit({2, 2, 2, 3}) == 1);
    assert(Solution().maxProfit({9, 1, 3, 2, 8, 4, 10}) == 9);
    assert(Solution().maxProfit({5, 4, 3, 2, 10}) == 8);
    assert(Solution().maxProfit({3, 3, 3, 3}) == 0);
    assert(Solution().maxProfit({1, 2, 1, 2, 1, 2}) == 1);
    assert(Solution().maxProfit({5, 5, 5, 5, 5, 5}) == 0);
    assert(Solution().maxProfit({1, 1000000}) == 999999);
    assert(Solution().maxProfit({1, 100, 2, 99, 3, 98, 1000}) == 999);

    return 0;
}
