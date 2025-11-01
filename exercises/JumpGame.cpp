#include <vector>
#include <cassert>

class Solution
{
public :
    bool jump(std::vector<int> nums)
    {
        return (!nums.empty()) ? jump(nums, 0) : false;
    }

private :
    [[nodiscard]]
    bool jump(const std::vector<int>& nums, int pos) const
    {
        if (pos >= nums.size())
        {
            return false;
        }
        else if (pos == nums.size() - 1)
        {
            return true;
        }

        for (int n = 1; n <= nums[pos]; ++n)
        {
            if (jump(nums, pos + n))
            {
                return true;
            }
        }

        return false;
    }
};

int main()
{
    assert(Solution().jump({0}));
    assert(Solution().jump({1}));
    assert(Solution().jump({2, 3, 1, 1, 4}));
    assert(!Solution().jump({3, 2, 1, 0, 4}));
    assert(!Solution().jump({0, 2, 3}));
    assert(Solution().jump({2, 0, 0}));
    assert(!Solution().jump({1, 0, 1, 0}));
    assert(Solution().jump({4, 2, 0, 0, 2, 0}));
    assert(Solution().jump({2, 5, 0, 0}));
    assert(Solution().jump({1, 1, 1, 1, 1}));
    assert(Solution().jump({2, 0, 2, 0, 1}));
    assert(!Solution().jump({2, 0, 1, 0, 0}));

    return 0;
}
