#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

class Solution
{
public :
    std::vector<std::vector<int>> permuteUnique(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return {};
        }

        std::vector<std::vector<int>> permutations;

        permutations.reserve(std::tgamma(nums.size() + 1));
        permute(nums, 0, permutations);
        removeDuplicates(permutations);

        return permutations;
    }

private :
    void permute(std::vector<int>& nums,
                 int index,
                 std::vector<std::vector<int>>& permutations) const
    {
        if (index >= nums.size())
        {
            permutations.emplace_back(nums);

            return;
        }

        for (int n = index; n < nums.size(); ++n)
        {
            std::swap(nums[n], nums[index]);
            permute(nums, index + 1, permutations);
            std::swap(nums[n], nums[index]);
        }
    }

    inline void removeDuplicates(
        std::vector<std::vector<int>>& permutations) const
    {
        std::sort(permutations.begin(), permutations.end());

        auto last = std::unique(permutations.begin(), permutations.end());

        permutations.erase(last, permutations.end());
    }
};

inline void check(
    const std::vector<std::vector<int>>& permutations,
    std::vector<std::vector<int>> expected)
{
    assert(permutations == expected);
}

int main()
{
    check(Solution().permuteUnique({1, 1, 2}),
           {{1, 1, 2}, {1, 2, 1}, {2, 1, 1}});
    check(Solution().permuteUnique({1, 2, 3}),
          {{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}});

    return 0;
}
