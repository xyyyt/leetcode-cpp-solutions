#include <vector>
#include <limits>
#include <iostream>

class Solution
{
public :
    int maxSubArray(std::vector<int> nums)
    {
        constexpr int MIN_VALUE = std::numeric_limits<int>::min();

        if (nums.empty())
        {
            return MIN_VALUE;
        }

        bool numsContainsOnlyNegValue = true;
        int bestSum = MIN_VALUE;
        int currentSum = MIN_VALUE;

        for (int n = 0; n < nums.size(); ++n)
        {
            if (nums[n] < 0 && numsContainsOnlyNegValue)
            {
                if (nums[n] > bestSum)
                {
                    bestSum = nums[n];
                    currentSum = bestSum;
                }
                else
                {
                    currentSum += nums[n];
                }
            }
            else
            {
                if (numsContainsOnlyNegValue)
                {
                    numsContainsOnlyNegValue = false;
                }

                currentSum += nums[n];

                if (currentSum > bestSum)
                {
                    bestSum = currentSum;
                }

                if (nums[n] > bestSum)
                {
                    bestSum = nums[n];
                    currentSum = bestSum;
                }
            }
        }

        return bestSum;
    }
};

int main()
{
    std::cout << Solution().maxSubArray({-2, 1, -3, 4, -1, 2, 1, -5, 4}) << '\n';
    std::cout << Solution().maxSubArray({1}) << '\n';
    std::cout << Solution().maxSubArray({5, 4, -1, 7, 8}) << '\n';
    std::cout << Solution().maxSubArray({-5, -3, -14, -1, -8}) << '\n';
    std::cout << Solution().maxSubArray({-69, -9, 0, -4, -2}) << '\n';
    std::cout << Solution().maxSubArray({1, 2, 3, 4, 5}) << '\n';

    return 0;
}
