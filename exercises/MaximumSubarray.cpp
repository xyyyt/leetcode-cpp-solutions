#include <vector>
#include <limits>
#include <cassert>

class Solution
{
public :
    int maxSubArray(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return std::numeric_limits<int>::min();
        }

        int bestSum = nums[0];
        int currentSum = nums[0];

        for (int n = 1; n < nums.size(); ++n)
        {
            currentSum = std::max(currentSum + nums[n], nums[n]);
            bestSum = std::max(bestSum, currentSum);
        }

        return bestSum;
    }
};

int main()
{
    assert(Solution().maxSubArray({-2, 1, -3, 4, -1, 2, 1, -5, 4})
           == 6);
    assert(Solution().maxSubArray({1})
           == 1);
    assert(Solution().maxSubArray({5, 4, -1, 7, 8})
           == 23);
    assert(Solution().maxSubArray({-5, -3, -14, -1, -8})
           == -1);
    assert(Solution().maxSubArray({-69, -9, 0, -4, -2})
           == 0);
    assert(Solution().maxSubArray({1, 2, 3, 4, 5})
           == 15);

    return 0;
}
