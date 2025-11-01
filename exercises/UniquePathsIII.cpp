#include <vector>
#include <unordered_set>
// #include <list>
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
    int uniquePathsIII(std::vector<std::vector<int>> grid)
    {
        if (grid.empty())
        {
            return -1;
        }

        int totalEmptySquare = getTotalEmptySquare(grid);

        for (int y = 0; y < grid.size(); ++y)
        {
            for (int x = 0; x < grid[y].size(); ++x)
            {
                if (grid[y][x] == to(Square::STARTING))
                {
                    return uniquePathsIII(
                        grid,
                        totalEmptySquare,
                        {},
                        // {},
                        Direction::UNKNOWN,
                        y,
                        x);
                }
            }
        }

        return -1;
    }

private :
    enum class Square : int8_t
    {
        STARTING = 1,
        ENDING = 2,
        EMPTY = 0,
        OBSTACLE = -1
    };

    enum class Direction : uint8_t { LEFT, RIGHT, UP, DOWN, UNKNOWN };

    using SquareUnderlying_t = typename std::underlying_type<Square>::type;

    // VC = Visited Cell
    using VCSet_t = std::unordered_set<std::pair<int, int>>;
    // using VCSetConstIterator_t = VCSet_t::const_iterator;

    // For debug only
    // using VCList_t = std::list<VCSetConstIterator_t>;

    [[nodiscard]]
    inline static constexpr SquareUnderlying_t to(Square square) noexcept
    {
        return static_cast<SquareUnderlying_t>(square);
    }

    [[nodiscard]]
    inline int getTotalEmptySquare(
        const std::vector<std::vector<int>>& grid) const
    {
        int totalEmptySquare = 0;

        for (int y = 0; y < grid.size(); ++y)
        {
            for (int x = 0; x < grid[y].size(); ++x)
            {
                if (grid[y][x] == to(Square::EMPTY))
                {
                    ++totalEmptySquare;
                }
            }
        }

        return totalEmptySquare;
    }

    [[nodiscard]]
    int uniquePathsIII(
        const std::vector<std::vector<int>>& grid,
        int totalEmptySquare,
        const VCSet_t& vcSet,
        // const VCList_t& vcList,
        Direction from,
        int y,
        int x) const
    {
        if (grid[y][x] == to(Square::ENDING))
        {
            // for (const auto& itFromVCSet : vcList)
            // {
            //     std::cout << "y : "
            //               << itFromVCSet->first
            //               << ", x : "
            //               << itFromVCSet->second
            //               << '\n';
            // }

            /* vcSet.size() - 1 because starting square
               doesn't count as a empty square */
            return vcSet.size() - 1 == totalEmptySquare;
        }

        if (vcSet.find({y, x}) != vcSet.cend()
            || grid[y][x] == to(Square::OBSTACLE))
        {
            return 0;
        }

        auto moveToCell = [&](
            Direction from2,
            int y2,
            int x2) -> int
        {
            VCSet_t vcSet2 = vcSet;
            // VCList_t vcList2 = vcList;

            [[maybe_unused]] auto res = vcSet2.emplace(
                y, x);

            // vcList2.emplace_back(res.first);

            return uniquePathsIII(
                grid,
                totalEmptySquare,
                vcSet2,
                // vcList2,
                from2,
                y2,
                x2);
        };
        int uniquePathsCounter = 0;

        if (from != Direction::LEFT
            && x - 1 >= 0)
        {
            uniquePathsCounter +=
                moveToCell(Direction::RIGHT,
                           y,
                           x - 1);
        }

        if (from != Direction::RIGHT
            && x + 1 < grid[y].size())
        {
            uniquePathsCounter +=
                moveToCell(Direction::LEFT,
                           y,
                           x + 1);
        }

        if (from != Direction::UP
            && y - 1 >= 0)
        {
            uniquePathsCounter +=
                moveToCell(Direction::DOWN,
                           y - 1,
                           x);
        }

        if (from != Direction::DOWN
            && y + 1 < grid.size())
        {
            uniquePathsCounter +=
                moveToCell(Direction::UP,
                           y + 1,
                           x);
        }

        return uniquePathsCounter;
    }
};

int main()
{
    assert(Solution().uniquePathsIII(
        {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 2, -1}})
           == 2);
    assert(Solution().uniquePathsIII(
        {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 2}})
           == 4);
    assert(Solution().uniquePathsIII(
        {{0, 1}, {2, 0}})
           == 0);
    assert(Solution().uniquePathsIII(
        {{1, 2}})
           == 1);
    assert(Solution().uniquePathsIII(
        {{1, -1, 2}})
           == 0);

    return 0;
}
