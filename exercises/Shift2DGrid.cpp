#include <vector>
#include <utility>
#include <limits>
#include <iostream>

class Solution
{
public :
    std::vector<std::vector<int>> shiftGrid(
        std::vector<std::vector<int>> grid, int k)
    {
        if (grid.empty() || k < 1)
        {
            return grid;
        }

        for (int n = 0; n < k; ++n)
        {
            int numToReinsert = std::numeric_limits<int>::min();

            for (int i = 0; i < grid.size(); ++i)
            {
                for (int j = 0; j < grid[i].size(); ++j)
                {
                    numToReinsert = std::exchange(grid[i][j], numToReinsert);
                }
            }

            grid[0][0] = numToReinsert;
        }

        return grid;
    }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<std::vector<int>>& grid) noexcept
{
    for (const auto& range : grid)
    {
        if (range.empty())
        {
            continue;
        }

        auto begin = range.cbegin() + 1;
        auto end = range.cend();

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
    std::cout << Solution().shiftGrid(
        {{1, 2, 3},
         {4, 5, 6},
         {7, 8, 9}},
        1)
              << '\n';
    std::cout << Solution().shiftGrid(
        {{3, 8, 1, 9},
         {19, 7, 2, 5},
         {4, 6, 11, 10},
         {12, 0, 21, 13}},
        4)
              << '\n';
    std::cout << Solution().shiftGrid(
        {{1, 2, 3},
         {4, 5, 6},
         {7, 8, 9}},
        9)
              << '\n';

    return 0;
}
