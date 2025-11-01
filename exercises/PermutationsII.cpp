#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iostream>

namespace std
{
    template <>
    struct hash<std::vector<int>>
    {
        [[nodiscard]]
        size_t operator()(const std::vector<int>& nums) const noexcept
        {
            size_t h = 0;

            for (auto num : nums)
            {
                h ^= std::hash<int>()(num);
            }

            return h;
        }
    };
}

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
        std::unordered_set<std::vector<int>> duplicates;

        permutations.erase(
            std::remove_if(
                permutations.begin(),
                permutations.end(),
                [&duplicates](const std::vector<int>& value)
                {
                    return !duplicates.emplace(value).second;
                }),
            permutations.end());
    }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<std::vector<int>>& permutations) noexcept
{
    if (permutations.empty())
    {
        os << "EMPTY";

        return os;
    }

    for (const auto& permutation : permutations)
    {
        if (permutation.empty())
        {
            continue;
        }

        auto begin = permutation.cbegin();
        auto end = permutation.cend();

        os << "[" << *begin;
        ++begin;

        while (begin != end)
        {
            os << ", " << *begin;
            ++begin;
        }

        os << "]";
    }

    return os;
}

int main()
{
    std::cout << Solution().permuteUnique({1, 1, 2}) << '\n';
    std::cout << Solution().permuteUnique({1, 2, 3}) << '\n';

    return 0;
}
