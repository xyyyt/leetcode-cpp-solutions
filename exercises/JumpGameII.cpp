#include <vector>
#include <limits>
#include <cassert>

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
    assert(Solution().jump({0}) == 0);
    assert(Solution().jump({1}) == 0);
    assert(Solution().jump({2, 3, 1, 1, 4}) == 2);
    assert(Solution().jump({1, 2, 3}) == 2);
    assert(Solution().jump({2, 1}) == 1);
    assert(Solution().jump({2, 0, 2, 0, 1}) == 2);
    assert(Solution().jump({3, 0, 0, 0}) == 1);
    assert(Solution().jump({1, 1, 1, 1, 1}) == 4);
    assert(Solution().jump({2, 3, 0, 1, 4}) == 2);

    return 0;
}
