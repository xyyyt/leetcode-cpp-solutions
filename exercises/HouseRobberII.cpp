#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>

class Solution
{
public :
    int rob(std::vector<int> nums)
    {
        return (!nums.empty()) ? rob(nums, 0) : -1;
    }

private :
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
    std::cout << Solution().rob({2, 3, 2}) << '\n';
    std::cout << Solution().rob({1, 2, 3, 1}) << '\n';
    std::cout << Solution().rob({1, 2, 3}) << '\n';

    return 0;
}
