#include <vector>
#include <limits>
#include <iostream>

class Solution
{
public :
    int jump(std::vector<int> nums)
    {
        return jump(nums, 0, 0);
    }

private :
    [[nodiscard]]
    int jump(
        const std::vector<int>& nums,
        int jumpCounter,
        int pos) const
    {
        if (pos >= nums.size())
        {
            return -1;
        }
        else if (pos == nums.size() - 1)
        {
            return jumpCounter;
        }

        int jumpCounterMin = std::numeric_limits<int>::max();

        for (int n = 1; n <= nums[pos]; ++n)
        {
            if (int res = jump(nums, jumpCounter + 1, pos + n); res != -1)
            {
                jumpCounterMin = std::min(jumpCounterMin, res);
            }
        }

        return jumpCounterMin;
    }
};

int main()
{
    std::cout << Solution().jump({2, 3, 1, 1, 4}) << '\n';
    std::cout << Solution().jump({2, 3, 0, 1, 4}) << '\n';

    return 0;
}
