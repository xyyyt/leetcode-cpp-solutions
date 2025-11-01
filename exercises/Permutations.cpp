#include <vector>
#include <iostream>

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
    std::cout << Solution().permute({1, 2, 3}) << '\n';
    std::cout << Solution().permute({0, 1}) << '\n';
    std::cout << Solution().permute({1}) << '\n';

    return 0;
}
