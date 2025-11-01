#include <vector>
#include <utility>
#include <limits>
#include <cassert>

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
            int valueToReinsert = std::numeric_limits<int>::min();

            for (int i = 0; i < grid.size(); ++i)
            {
                for (int j = 0; j < grid[i].size(); ++j)
                {
                    valueToReinsert = std::exchange(grid[i][j], valueToReinsert);
                }
            }

            grid[0][0] = valueToReinsert;
        }

        return grid;
    }
};

inline void check(
    const std::vector<std::vector<int>>& grid,
    std::vector<std::vector<int>> expected)
{
    assert(grid == expected);
}

int main()
{
    check(Solution().shiftGrid(
        {{1, 2, 3},
         {4, 5, 6},
         {7, 8, 9}},
        1),
          {{9, 1, 2},
           {3, 4, 5},
           {6, 7, 8}});
    check(Solution().shiftGrid(
        {{3, 8, 1, 9},
         {19, 7, 2, 5},
         {4, 6, 11, 10},
         {12, 0, 21, 13}},
        4),
          {{12, 0, 21, 13},
           {3, 8, 1, 9},
           {19, 7, 2, 5},
           {4, 6, 11, 10}});
    check(Solution().shiftGrid(
        {{1, 2, 3},
         {4, 5, 6},
         {7, 8, 9}},
        9),
          {{1, 2, 3},
           {4, 5, 6},
           {7, 8, 9}});

    return 0;
}
