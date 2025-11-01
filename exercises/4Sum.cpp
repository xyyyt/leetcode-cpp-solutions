#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>

namespace std
{
    template <>
    struct hash<std::vector<int>>
    {
        [[nodiscard]]
        size_t operator()(const std::vector<int>& v) const noexcept
        {
            size_t h = 0;

            for (auto n : v)
            {
                h ^= std::hash<int>()(n);
            }

            return h;
        }
    };

    template <>
    struct equal_to<std::vector<int>>
    {
        [[nodiscard]]
        bool operator()(
            const std::vector<int>& lhs, const std::vector<int>& rhs) const
        {
            if (lhs.size() != rhs.size())
            {
                return false;
            }

            std::vector<int> lhsCopy = lhs;
            std::vector<int> rhsCopy = rhs;

            std::sort(lhsCopy.begin(), lhsCopy.end());
            std::sort(rhsCopy.begin(), rhsCopy.end());

            return lhsCopy == rhsCopy;
        }
    };
}

class Solution
{
public :
    std::vector<std::vector<int>> fourSum(std::vector<int> nums, int target)
    {
        if (nums.size() < 4)
        {
            return {};
        }

        std::unordered_multimap<int, int> indexByNums;

        indexByNums.reserve(nums.size());

        for (int n = 0; n < nums.size(); ++n)
        {
            indexByNums.emplace(nums[n], n);
        }

        std::unordered_set<std::vector<int>> quadruplets;

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

                                quadruplets.emplace(InitList_t{
                                    nums[n], nums[n2], nums[n3], it->first});
                            }
                        }
                    }
                }
            }
        }

        return std::vector<std::vector<int>>(
            std::move_iterator(quadruplets.begin()),
            std::move_iterator(quadruplets.end()));
     }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<std::vector<int>>& quadruplets) noexcept
{
    if (quadruplets.empty())
    {
        os << "EMPTY";

        return os;
    }

    for (const auto& quadruplet : quadruplets)
    {
        if (quadruplet.empty())
        {
            continue;
        }

        auto begin = quadruplet.cbegin();
        auto end = quadruplet.cend();

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
    std::cout << Solution().fourSum({1, 0, -1, 0, -2, 2}, 0) << '\n';
    std::cout << Solution().fourSum({2, 2, 2, 2, 2}, 8) << '\n';

    return 0;
}
