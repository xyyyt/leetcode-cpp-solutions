#include <vector>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    std::vector<std::vector<int>> subsets(
        std::vector<int> nums)
    {
        if (nums.empty())
        {
            return {{}};
        }

        using InitList_t = std::initializer_list<int>;

        std::vector<std::vector<int>> subsets;

        subsets.emplace_back(InitList_t{});

        for (int n = 0; n < nums.size(); ++n)
        {
            std::vector<int> subset;

            subset.reserve(nums.size() - n);
            subset.emplace_back(nums[n]);
            subsets.emplace_back(subset);

            for (int n2 = n + 1; n2 < nums.size(); ++n2)
            {
                subsets.emplace_back(InitList_t{nums[n], nums[n2]});
                subsets.emplace_back(InitList_t{nums[n2]});
                subset.emplace_back(nums[n2]);
                subsets.emplace_back(subset);
            }
        }

        subsets.emplace_back(nums);
        removeDuplicates(subsets);

        return subsets;
    }

private :
    inline void removeDuplicates(
        std::vector<std::vector<int>>& subsets) const
    {
        for (auto& subset : subsets)
        {
            std::sort(subset.begin(), subset.end());
        }

        std::sort(subsets.begin(), subsets.end());

        auto last = std::unique(subsets.begin(), subsets.end());

        subsets.erase(last, subsets.end());
    }
};

inline void check(
    const std::vector<std::vector<int>>& subsets,
    std::vector<std::vector<int>> expected)
{
    assert(subsets == expected);
}

int main()
{
    check(Solution().subsets({1, 2, 3}),
          {{}, {1}, {1, 2}, {1, 2, 3}, {1, 3}, {2}, {2, 3}, {3}});
    check(Solution().subsets({0}),
          {{}, {0}});
    check(Solution().subsets({0, 1}),
          {{}, {0}, {0, 1}, {1}});
    check(Solution().subsets({-1, 2}),
          {{}, {-1}, {-1, 2}, {2}});
    check(Solution().subsets({}),
          {{}});
    check(Solution().subsets({10, 100}),
          {{}, {10}, {10, 100}, {100}});

    return 0;
}
