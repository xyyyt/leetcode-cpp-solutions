#include <vector>
#include <algorithm>
#include <limits>
#include <cassert>

class Solution
{
public :
    int rob(std::vector<int> nums)
    {
        return (!nums.empty()) ? rob(nums, 0) : -1;
    }

private :
    [[nodiscard]]
    int rob(
        const std::vector<int>& nums, int pos) const
    {
        if (pos >= nums.size())
        {
            return 0;
        }

        int maxMoneyAmount = std::numeric_limits<int>::min();

        for (int n = pos; n < nums.size(); ++n)
        {
            int maxMoneyAmount2 = nums[n];

            for (int n2 = n + 2; n2 < nums.size(); ++n2)
            {
                if (n == 0 && n2 == nums.size() - 1)
                {
                    continue;
                }

                int currentMoneyAmount = nums[n] + nums[n2];

                currentMoneyAmount += rob(nums, n2 + 2);
                maxMoneyAmount2 = std::max(maxMoneyAmount2, currentMoneyAmount);
            }

            maxMoneyAmount = std::max(maxMoneyAmount, maxMoneyAmount2);
        }

        return maxMoneyAmount;
    }
};

int main()
{
    assert(Solution().rob({2, 3, 2}) == 3);
    assert(Solution().rob({1, 2, 3, 1}) == 4);
    assert(Solution().rob({1, 2, 3}) == 3);
    assert(Solution().rob({5}) == 5);
    assert(Solution().rob({2, 3}) == 3);
    assert(Solution().rob({10, 1, 10}) == 10);
    assert(Solution().rob({5, 5, 5, 5}) == 10);
    assert(Solution().rob({6, 7, 1, 30, 8, 2, 4}) == 41);
    assert(Solution().rob({10, 50, 10, 50}) == 100);
    assert(Solution().rob({2, 1, 1, 2}) == 3);
    assert(Solution().rob({1, 1, 1, 1, 1, 1}) == 3);
    assert(Solution().rob({50, 1, 1, 1}) == 51);

    return 0;
}
