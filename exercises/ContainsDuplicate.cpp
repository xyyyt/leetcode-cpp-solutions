#include <vector>
#include <unordered_set>
#include <cassert>

class Solution
{
public :
    bool containsDuplicate(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return false;
        }

        std::unordered_set<int> seenNums;

        seenNums.reserve(nums.size());

        for (auto num : nums)
        {
            if (!seenNums.emplace(num).second)
            {
                return true;
            }
        }

        return false;
    }
};

int main()
{
    assert(Solution().containsDuplicate({1, 2, 3, 1}));
    assert(!Solution().containsDuplicate({1, 2, 3, 4}));
    assert(Solution().containsDuplicate({1, 1, 1, 3, 3, 4, 3, 2, 4, 2}));
    assert(!Solution().containsDuplicate({}));
    assert(!Solution().containsDuplicate({42}));
    assert(Solution().containsDuplicate({7, 7}));
    assert(Solution().containsDuplicate({1, 2, 3, 1}));
    assert(Solution().containsDuplicate({1, 2, 3, 4, 5, 6, 7, 1}));
    assert(!Solution().containsDuplicate({1, 2, 3, 4, 5, 6, 7, 8}));
    assert(Solution().containsDuplicate({-1, -2, -3, -1}));
    assert(!Solution().containsDuplicate({-5, -3, 0, 2, 4}));
    assert(Solution().containsDuplicate({9, 9, 9, 9, 9}));

    return 0;
}
