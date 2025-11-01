#include <vector>
#include <unordered_map>
#include <iostream>

class Solution
{
public :
    std::vector<int> twoSum(std::vector<int> nums, int target)
    {
        if (nums.size() < 2)
        {
            return {};
        }

        std::unordered_map<int, int> indexByNums;

        indexByNums.reserve(nums.size());

        for (int n = 0; n < nums.size(); ++n)
        {
            int complement = target - nums[n];

            if (auto it = indexByNums.find(complement);
                it != indexByNums.cend())
            {
                return {it->second, n};
            }

            indexByNums[nums[n]] = n;
        }

        return {};
    }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<int>& indices) noexcept
{
    if (indices.empty())
    {
        os << "EMPTY";

        return os;
    }

    auto begin = indices.cbegin();
    auto end = indices.cend();

    os << *begin;
    ++begin;

    while (begin != end)
    {
        os << ", " << *begin;
        ++begin;
    }

    return os;
}

int main()
{
    std::cout << Solution().twoSum({2, 7, 11, 15}, 9) << '\n';
    std::cout << Solution().twoSum({3, 2, 4}, 6) << '\n';
    std::cout << Solution().twoSum({3, 3}, 6) << '\n';

    return 0;
}
