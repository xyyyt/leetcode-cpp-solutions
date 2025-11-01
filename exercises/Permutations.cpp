#include <vector>
#include <cmath>
#include <cassert>

class Solution
{
public :
    std::vector<std::vector<int>> permute(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return {};
        }

        std::vector<std::vector<int>> permutations;

        permutations.reserve(std::tgamma(nums.size() + 1));
        permute(nums, 0, permutations);

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
};

inline void check(
    const std::vector<std::vector<int>>& permutations,
    std::vector<std::vector<int>> expected)
{
    assert(permutations == expected);
}

int main()
{
    check(Solution().permute({1, 2, 3}),
          {{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 2, 1}, {3, 1, 2}});
    check(Solution().permute({0, 1}),
          {{0, 1}, {1, 0}});
    check(Solution().permute({1}),
          {{1}});

    return 0;
}
