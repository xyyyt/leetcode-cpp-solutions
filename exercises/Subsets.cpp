#include <vector>
#include <unordered_set>
#include <cmath>
#include <cassert>

namespace std
{
    template <>
    struct hash<std::vector<int>>
    {
        [[nodiscard]]
        size_t operator()(const std::vector<int>& v) const noexcept
        {
            size_t seed = v.size();

            for (auto n : v)
            {
                size_t h = std::hash<int>{}(n);

                // boost::hash_combine formula
                seed ^= h + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }

            return seed;
        }
    };
}

class Solution
{
public :
    std::vector<std::vector<int>> subsets(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return {};
        }

        using InitList_t = std::initializer_list<int>;

        std::unordered_set<std::vector<int>> uniqueSubsets;

        uniqueSubsets.emplace(InitList_t{});

        for (int n = 0; n < nums.size(); ++n)
        {
            std::vector<int> subset;

            subset.reserve(nums.size() - n);
            subset.emplace_back(nums[n]);
            uniqueSubsets.emplace(subset);

            for (int n2 = n + 1; n2 < nums.size(); ++n2)
            {
                uniqueSubsets.emplace(InitList_t{nums[n2]});
                uniqueSubsets.emplace(InitList_t{nums[n], nums[n2]});
                subset.emplace_back(nums[n2]);
                uniqueSubsets.emplace(subset);
            }
        }

        uniqueSubsets.emplace(nums);

        return std::vector<std::vector<int>>(
            std::move_iterator(uniqueSubsets.begin()),
            std::move_iterator(uniqueSubsets.end()));
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
          {{1, 2, 3}, {2, 3}, {1, 3}, {3}, {1, 2}, {2}, {1}, {}});
    check(Solution().subsets({0}),
          {{0}, {}});

    return 0;
}
