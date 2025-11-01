#include <vector>
#include <limits>
#include <cassert>

class Solution
{
public :
    int maxProduct(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return 0;
        }

        int bestProduct = std::numeric_limits<int>::min();

        for (int n = 0; n < nums.size(); ++n)
        {
            int currentProduct = nums[n];

            bestProduct = std::max(bestProduct, currentProduct);

            for (int n2 = n + 1; n2 < nums.size(); ++n2)
            {
                currentProduct *= nums[n2];
                bestProduct = std::max(bestProduct, currentProduct);
            }
        }

        return bestProduct;
    }
};

int main()
{
    assert(Solution().maxProduct({2, 3, -2, 4}) == 6);
    assert(Solution().maxProduct({-2, 0, -1}) == 0);
    assert(Solution().maxProduct({-7, 2, -3}) == 42);
    assert(Solution().maxProduct({-1, -2, 0}) == 2);
    assert(Solution().maxProduct({1, 2, 3, 4}) == 24);
    assert(Solution().maxProduct({-1, -3, -10, 0, 60}) == 60);
    assert(Solution().maxProduct({-2, -3, 4, -1}) == 24);
    assert(Solution().maxProduct({-2, 0, -1}) == 0);
    assert(Solution().maxProduct({0, -2, 0, -3, 0, 4}) == 4);
    assert(Solution().maxProduct({-5}) == -5);
    assert(Solution().maxProduct({-2, -3, -4}) == 12);
    assert(Solution().maxProduct({-2, -3, 7}) == 42);
    assert(Solution().maxProduct({2, -5, -2, -4, 3}) == 24);

    return 0;
}
