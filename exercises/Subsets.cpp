#include <vector>
#include <unordered_set>
#include <iostream>
#include <math.h>

namespace std
{
    template <>
    struct hash<std::vector<int>>
    {
        [[nodiscard]]
        size_t operator()(const std::vector<int>& v) const noexcept
        {
            size_t h = 0;

            for (auto value : v)
            {
                h ^= std::hash<int>()(value);
            }

            return h;
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

std::ostream& operator<<(
    std::ostream& os, const std::vector<std::vector<int>>& subsets) noexcept
{
    if (subsets.empty())
    {
        os << "EMPTY";

        return os;
    }

    for (const auto& subset : subsets)
    {
        if (subset.empty())
        {
            continue;
        }

        auto begin = subset.cbegin();
        auto end = subset.cend();

        os << '[' << *begin;
        ++begin;

        while (begin != end)
        {
            os << ", " << *begin;
            ++begin;
        }

        os << ']';
    }

    return os;
}

int main()
{
    std::cout << Solution().subsets({1, 2, 3}) << '\n';
    std::cout << Solution().subsets({0}) << '\n';

    return 0;
}
