#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    std::vector<std::vector<int>> threeSum(
        std::vector<int> nums)
    {
        if (nums.size() < 3)
        {
            return {{}};
        }

        std::unordered_multimap<int, int> indexByNums;

        indexByNums.reserve(nums.size());

        for (int n = 0; n < nums.size(); ++n)
        {
            indexByNums.emplace(nums[n], n);
        }

        std::vector<std::vector<int>> triplets;

        for (int n = 0; n < nums.size() - 2; ++n)
        {
            for (int n2 = n + 1; n2 < nums.size() - 1; ++n2)
            {
                constexpr int TARGET = 0;
                int complement = TARGET - (nums[n] + nums[n2]);

                if (auto range = indexByNums.equal_range(complement);
                    range.first != range.second)
                {
                    for (auto it = range.first; it != range.second; ++it)
                    {
                        if (it->second != n && it->second != n2)
                        {
                            using InitList_t = std::initializer_list<int>;

                            triplets.emplace_back(
                                InitList_t{nums[n], nums[n2], it->first});
                        }
                    }
                }
            }
        }

        removeDuplicates(triplets);

        return triplets;
     }

private :
    inline void removeDuplicates(
        std::vector<std::vector<int>>& triplets) const
    {
        for (auto& triplet : triplets)
        {
            std::sort(triplet.begin(), triplet.end());
        }

        std::sort(triplets.begin(), triplets.end());

        auto last = std::unique(triplets.begin(), triplets.end());

        triplets.erase(last, triplets.end());
    }
};

inline void check(
    const std::vector<std::vector<int>>& triplets,
    std::vector<std::vector<int>> expected)
{
    assert(triplets == expected);
}

int main()
{
    check(Solution().threeSum({-1, 0, 1, 2, -1, -4}),
        {{-1, -1, 2}, {-1, 0, 1}});
    check(Solution().threeSum({0, 1, 1}),
        {});
    check(Solution().threeSum({0, 0, 0}),
        {{0, 0, 0}});
    check(Solution().threeSum({1, 2}),
        {{}});
    check(Solution().threeSum({0, 0, 0, 0}),
        {{0, 0, 0}});
    check(Solution().threeSum({1, -1, -1, 0}),
        {{-1, 0, 1}});
    check(Solution().threeSum({-2, 0, 1, 1, 2}),
        {{-2, 0, 2}, {-2, 1, 1}});

    return 0;
}
