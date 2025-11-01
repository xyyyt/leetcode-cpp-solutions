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

        std::unordered_set<int> usedNums;

        usedNums.reserve(nums.size());

        for (auto num : nums)
        {
            if (!usedNums.emplace(num).second)
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

    return 0;
}
