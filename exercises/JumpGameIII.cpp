#include <vector>
#include <unordered_set>
#include <limits>
#include <cassert>

class Solution
{
public :
    bool jump(std::vector<int> nums, int start)
    {
        if (nums.empty())
        {
            return false;
        }

        std::unordered_set<int> seenIndices;

        seenIndices.reserve(nums.size());

        return jump(nums, seenIndices, start);
    }

private :
    [[nodiscard]]
    bool jump(
        const std::vector<int>& nums,
        std::unordered_set<int>& seenIndices,
        int pos) const
    {
        if (pos < 0 || pos >= nums.size())
        {
            return false;
        }
        else if (nums[pos] == 0)
        {
            return true;
        }

        if (!seenIndices.emplace(pos).second)
        {
            return false;
        }

        return jump(nums, seenIndices, pos + nums[pos])
            || jump(nums, seenIndices, pos - nums[pos]);
    }
};

int main()
{
    assert(Solution().jump({0}, 0));
    assert(!Solution().jump({1, 2, 3}, 0));
    assert(Solution().jump({4, 2, 3, 0, 3, 1, 2}, 5));
    assert(Solution().jump({4, 2, 3, 0, 3, 1, 2}, 0));
    assert(!Solution().jump({3, 0, 2, 1, 2}, 2));
    assert(!Solution().jump({1, 1, 1, 1}, 0));
    assert(!Solution().jump({2, 0, 2, 0}, 2));
    assert(Solution().jump({0, 1, 2, 3}, 3));
    assert(Solution().jump({2, 3, 1, 2, 0}, 1));
    assert(Solution().jump({2, 3, 1, 2, 0}, 4));

    return 0;
}
