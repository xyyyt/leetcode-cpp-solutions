#include <vector>
#include <unordered_set>
#include <type_traits>
#include <cstdint>
#include <cassert>

namespace std
{
    template <>
    struct hash<std::pair<int, int>>
    {
        [[nodiscard]]
        size_t operator()(const std::pair<int, int>& pair) const noexcept
        {
            size_t h1 = std::hash<int>{}(pair.first);
            size_t h2 = std::hash<int>{}(pair.second);

            // boost::hash_combine formula
            return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
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
        Direction from,
        int m,
        int n) const
    {
        if (grid[m][n] == to(GridItem::WATER)
            || landVCSet.find({m, n}) != landVCSet.cend())
        {
            return;
        }

        landVCSet.emplace(m, n);

        if (from != Direction::LEFT
            && n - 1 >= 0)
        {
            findIsland(
                grid, landVCSet, Direction::RIGHT, m, n - 1);
        }

        if (from != Direction::RIGHT
            && n + 1 < grid[m].size())
        {
            findIsland(
                grid, landVCSet, Direction::LEFT, m, n + 1);
        }

        if (from != Direction::UP
            && m - 1 >= 0)
        {
            findIsland(
                grid, landVCSet, Direction::DOWN, m - 1, n);
        }

        if (from != Direction::DOWN
            && m + 1 < grid.size())
        {
            findIsland(
                grid, landVCSet, Direction::UP, m + 1, n);
        }
    }
};

int main()
{
    assert(Solution().numIslands({
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}})
        == 1);
    assert(Solution().numIslands({
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}})
        == 3);
    assert(Solution().numIslands({
        {'0', '0', '0'},
        {'0', '0', '0'},
        {'0', '0', '0'}})
        == 0);
    assert(Solution().numIslands({
        {'1', '0', '0'},
        {'0', '0', '0'},
        {'0', '0', '1'}})
        == 2);
    assert(Solution().numIslands({
        {'1', '1', '0'},
        {'1', '1', '0'},
        {'0', '0', '0'}})
        == 1);
    assert(Solution().numIslands({
        {'1', '0', '1'},
        {'0', '1', '0'},
        {'1', '0', '1'}})
        == 5);
    assert(Solution().numIslands({
        {'1', '1', '0', '1'},
        {'0', '1', '0', '0'},
        {'1', '0', '1', '1'},
        {'0', '0', '0', '1'}})
        == 4);
    assert(Solution().numIslands({
        {'1', '1', '1'},
        {'0', '1', '0'},
        {'1', '1', '1'}})
        == 1);
    assert(Solution().numIslands({
        {'1'},
        {'1'},
        {'0'},
        {'1'}})
        == 2);
    assert(Solution().numIslands({
        {'1', '0', '1', '0', '1'}})
        == 3);
    assert(Solution().numIslands({
        {'1', '0', '0', '0'},
        {'0', '0', '1', '0'},
        {'0', '1', '1', '0'},
        {'0', '0', '0', '1'}})
        == 3);

    return 0;
}
