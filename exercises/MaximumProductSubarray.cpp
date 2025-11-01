#include <vector>
#include <limits>
#include <cassert>

class Solution
{
public :
    int maxProduct(std::vector<int> nums)
    {
        constexpr int MIN_VALUE = std::numeric_limits<int>::min();

        if (nums.size() < 2)
        {
            return MIN_VALUE;
        }

        int bestProduct = MIN_VALUE;

        for (int n = 0; n < nums.size() - 1; ++n)
        {
            int currentProduct = nums[n] * nums[n + 1];

            bestProduct = std::max(bestProduct, currentProduct);

            for (int n2 = n + 2; n2 < nums.size(); ++n2)
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

    return 0;
}
