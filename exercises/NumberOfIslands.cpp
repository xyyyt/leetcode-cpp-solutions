#include <vector>
#include <unordered_set>
#include <type_traits>
#include <iostream>

namespace std
{
    template <>
    struct hash<std::pair<int, int>>
    {
        [[nodiscard]]
        size_t operator()(const std::pair<int, int>& pair) const noexcept
        {
            return std::hash<int>()(pair.first)
                ^ std::hash<int>()(pair.second);
        }
    };
}

class Solution
{
public :
    int numIslands(std::vector<std::vector<char>> grid)
    {
        if (grid.empty())
        {
            return 0;
        }

        VCSet_t landVCSet;
        int islandCounter = 0;

        for (int m = 0; m < grid.size(); ++m)
        {
            for (int n = 0; n < grid[m].size(); ++n)
            {
                if (grid[m][n] == to(GridItem::LAND)
                    && landVCSet.find({m, n}) == landVCSet.cend())
                {
                    findIsland(
                        grid, landVCSet, Direction::UNKNOWN, m, n);
                    ++islandCounter;
                }
            }
        }

        return islandCounter;
    }

private :
    enum class GridItem : char { LAND = '1', WATER = '0' };
    enum class Direction : uint8_t { LEFT, RIGHT, UP, DOWN, UNKNOWN };

    using GridItemUnderlying_t = typename std::underlying_type<GridItem>::type;

    // VC = Visited Cell
    using VCSet_t = std::unordered_set<std::pair<int, int>>;

    [[nodiscard]]
    inline static constexpr GridItemUnderlying_t to(GridItem item) noexcept
    {
        return static_cast<GridItemUnderlying_t>(item);
    }

    void findIsland(
        const std::vector<std::vector<char>>& grid,
        VCSet_t& landVCSet,
        Direction fromDirection,
        int m,
        int n) const
    {
        if (grid[m][n] == to(GridItem::WATER)
            || landVCSet.find({m, n}) != landVCSet.cend())
        {
            return;
        }

        landVCSet.emplace(m, n);

        if (fromDirection != Direction::LEFT
            && n - 1 >= 0)
        {
            findIsland(
                grid, landVCSet, Direction::RIGHT, m, n - 1);
        }

        if (fromDirection != Direction::RIGHT
            && n + 1 < grid[m].size())
        {
            findIsland(
                grid, landVCSet, Direction::LEFT, m, n + 1);
        }

        if (fromDirection != Direction::UP
            && m - 1 >= 0)
        {
            findIsland(
                grid, landVCSet, Direction::DOWN, m - 1, n);
        }

        if (fromDirection != Direction::DOWN
            && m + 1 < grid.size())
        {
            findIsland(
                grid, landVCSet, Direction::UP, m + 1, n);
        }
    }
};

int main()
{
    std::cout << Solution().numIslands({
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}})
              << '\n';
    std::cout << Solution().numIslands({
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}})
              << '\n';

    return 0;
}
