#include <vector>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    std::vector<int> sortedSquares(std::vector<int> nums)
    {
        std::vector<int> squares;

        squares.reserve(nums.size());

        for (auto num : nums)
        {
            squares.emplace_back(num * num);
        }

        std::sort(squares.begin(), squares.end());

        return squares;
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

    return 0;
}
