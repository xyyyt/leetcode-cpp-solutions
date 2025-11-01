#include <vector>
#include <cmath>
#include <cassert>

class Solution
{
public :
    std::vector<int> sortedSquares(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return {};
        }

        std::vector<int> sorted;
        int left = 0;
        int right = nums.size() - 1;

        sorted.resize(nums.size());

        for (int n = nums.size() - 1; left <= right; --n)
        {
            if (std::abs(nums[left]) > nums[right])
            {
                sorted[n] = nums[left] * nums[left];
                ++left;
            }
            else
            {
                sorted[n] = nums[right] * nums[right];
                --right;
            }
        }

        return sorted;
    }
};

inline void check(
    const std::vector<int>& squares,
    std::vector<int> expected)
{
    assert(squares == expected);
}

int main()
{
    check(Solution().sortedSquares({-4, -1, 0, 3, 10}),
          {0, 1, 9, 16, 100});
    check(Solution().sortedSquares({-7, -3, 2, 3, 11}),
          {4, 9, 9, 49, 121});
    check(Solution().sortedSquares({-12, -9, -7, -3, 1}),
          {1, 9, 49, 81, 144});
    check(Solution().sortedSquares({-3, -1, 0, 3}),
          {0, 1, 9, 9});
    check(Solution().sortedSquares({-5, -2, 0}),
          {0, 4, 25});
    check(Solution().sortedSquares({-10, 10}),
          {100, 100});
    check(Solution().sortedSquares({-4}),
          {16});

    return 0;
}
