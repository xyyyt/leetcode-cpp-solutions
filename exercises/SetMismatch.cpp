#include <vector>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    std::vector<int> findErrorNums(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return {};
        }

        std::sort(nums.begin(), nums.end());

        int n = 0;

        while (n < nums.size() - 1)
        {
            if (nums[n + 1] != nums[n] + 1)
            {
                break;
            }

            ++n;
        }

        return {nums[n], nums[n] + 1};
    }
};

inline void check(
    const std::vector<int>& errorNums,
    std::vector<int> expected)
{
    assert(errorNums == expected);
}

int main()
{
    check(Solution().findErrorNums({1, 2, 2, 4}), {2, 3});
    check(Solution().findErrorNums({1, 1}), {1, 2});

    return 0;
}
