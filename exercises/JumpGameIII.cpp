#include <vector>
#include <unordered_set>
#include <limits>
#include <iostream>

class Solution
{
public :
    bool jump(std::vector<int> nums, int start)
    {
        if (nums.empty())
        {
            return false;
        }

        std::unordered_set<int> indexAlreadyUsed;

        indexAlreadyUsed.reserve(nums.size());

        return jump(nums, indexAlreadyUsed, start);
    }

private :
    [[nodiscard]]
    bool jump(
        const std::vector<int>& nums,
        std::unordered_set<int>& indexAlreadyUsed,
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

        if (!indexAlreadyUsed.emplace(pos).second)
        {
            return false;
        }

        return jump(nums, indexAlreadyUsed, pos + nums[pos])
            || jump(nums, indexAlreadyUsed, pos - nums[pos]);
    }
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << Solution().jump({4, 2, 3, 0, 3, 1, 2}, 5) << '\n';
    std::cout << Solution().jump({4, 2, 3, 0, 3, 1, 2}, 0) << '\n';
    std::cout << Solution().jump({3, 0, 2, 1, 2}, 2) << '\n';

    return 0;
}
