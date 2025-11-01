#include <vector>
#include <unordered_map>
#include <cassert>

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

inline void check(
    const std::vector<int>& indices,
    std::vector<int> expected)
{
    assert(indices == expected);
}

int main()
{
    check(Solution().twoSum({2, 7, 11, 15}, 9), {0, 1});
    check(Solution().twoSum({3, 2, 4}, 6), {1, 2});
    check(Solution().twoSum({3, 3}, 6), {0, 1});
    check(Solution().twoSum({1, 5, 3, 7}, 8), {1, 2});
    check(Solution().twoSum({1, 2, 3, 4, 5}, 9), {3, 4});
    check(Solution().twoSum({0, 4, 3, 0}, 0), {0, 3});
    check(Solution().twoSum({-3, 4, 3, 90}, 0), {0, 2});

    return 0;
}
