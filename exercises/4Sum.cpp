#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    std::vector<std::vector<int>> fourSum(
        std::vector<int> nums, int target)
    {
        if (nums.size() < 4)
        {
            return {{}};
        }

        std::unordered_multimap<int, int> indexByNums;

        indexByNums.reserve(nums.size());

        for (int n = 0; n < nums.size(); ++n)
        {
            indexByNums.emplace(nums[n], n);
        }

        std::vector<std::vector<int>> quadruplets;

        for (int n = 0; n < nums.size() - 3; ++n)
        {
            for (int n2 = n + 1; n2 < nums.size() - 2; ++n2)
            {
                for (int n3 = n2 + 1; n3 < nums.size() - 1; ++n3)
                {
                    int complement = target - (nums[n] + nums[n2] + nums[n3]);

                    if (auto range = indexByNums.equal_range(complement);
                        range.first != range.second)
                    {
                        for (auto it = range.first; it != range.second; ++it)
                        {
                            if (it->second != n && it->second != n2)
                            {
                                using InitList_t = std::initializer_list<int>;

                                quadruplets.emplace_back(InitList_t{
                                    nums[n], nums[n2], nums[n3], it->first});
                            }
                        }
                    }
                }
            }
        }

        removeDuplicates(quadruplets);

        return quadruplets;
     }

private :
    inline void removeDuplicates(
        std::vector<std::vector<int>>& quadruplets) const
    {
        for (auto& quadruplet : quadruplets)
        {
            std::sort(quadruplet.begin(), quadruplet.end());
        }

        std::sort(quadruplets.begin(), quadruplets.end());

        auto last = std::unique(quadruplets.begin(), quadruplets.end());

        quadruplets.erase(last, quadruplets.end());
    }
};

inline void check(
    const std::vector<std::vector<int>>& quadruplets,
    std::vector<std::vector<int>> expected)
{
    assert(quadruplets == expected);
}

int main()
{
    check(Solution().fourSum({1, 0, -1, 0, -2, 2}, 0),
          {{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}});
    check(Solution().fourSum({2, 2, 2, 2, 2}, 8),
          {{2, 2, 2, 2}});
    check(Solution().fourSum({}, 0),
          {{}});
    check(Solution().fourSum({1, 2, 3}, 6),
          {{}});
    check(Solution().fourSum({0, 0, 0, 0, 0}, 0),
          {{0, 0, 0, 0}});
    check(Solution().fourSum({2, 2, 2, 2, 2}, 8),
          {{2, 2, 2, 2}});
    check(Solution().fourSum({1, 0, -1, 0, -2, 2, 2}, 2),
          {{-2, 0, 2, 2}, {-1, 0, 1, 2}});

    return 0;
}
