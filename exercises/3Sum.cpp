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
    std::vector<std::vector<int>> threeSum(std::vector<int> nums)
    {
        if (nums.size() < 3)
        {
            return {};
        }

        std::unordered_multimap<int, int> indexByNums;

        indexByNums.reserve(nums.size());

        for (int n = 0; n < nums.size(); ++n)
        {
            indexByNums.emplace(nums[n], n);
        }

        std::unordered_set<std::vector<int>> triplets;

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

                            triplets.emplace(
                                InitList_t{nums[n], nums[n2], it->first});
                        }
                    }
                }
            }
        }

        return std::vector<std::vector<int>>(
            std::move_iterator(triplets.begin()),
            std::move_iterator(triplets.end()));
     }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<std::vector<int>>& triplets) noexcept
{
    if (triplets.empty())
    {
        os << "EMPTY";

        return os;
    }

    os << '[';

    for (const auto& triplet : triplets)
    {
        if (triplet.empty())
        {
            continue;
        }

        auto begin = triplet.cbegin();
        auto end = triplet.cend();

        os << '[' << *begin;
        ++begin;

        while (begin != end)
        {
            os << ", " << *begin;
            ++begin;
        }

        os << ']';
    }

    os << ']';

    return os;
}

int main()
{
    std::cout << Solution().threeSum({-1, 0, 1, 2, -1, 4}) << '\n';
    std::cout << Solution().threeSum({0, 1, 1}) << '\n';
    std::cout << Solution().threeSum({0, 0, 0}) << '\n';

    return 0;
}
