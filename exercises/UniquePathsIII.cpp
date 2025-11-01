#include <vector>
#include <unordered_set>
// #include <list>
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
        Direction fromDirection,
        int posY,
        int posX) const
    {
        if (grid[posY][posX] == to(Square::ENDING))
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
            return (vcSet.size() - 1 == totalEmptySquare) ? 1 : 0;
        }

        if (vcSet.find({posY, posX}) != vcSet.cend()
            || grid[posY][posX] == to(Square::OBSTACLE))
        {
            return 0;
        }

        auto moveToCell = [&](
            Direction fromDirection2,
            int posY2,
            int posX2) -> int
        {
            VCSet_t vcSet2 = vcSet;
            // VCList_t vcList2 = vcList;

            [[maybe_unused]] auto res = vcSet2.emplace(
                posY, posX);

            // vcList2.emplace_back(res.first);

            return uniquePathsIII(
                grid,
                totalEmptySquare,
                vcSet2,
                // vcList2,
                fromDirection2,
                posY2,
                posX2);
        };
        int uniquePathsCounter = 0;

        if (fromDirection != Direction::LEFT
            && posX - 1 >= 0)
        {
            uniquePathsCounter +=
                moveToCell(Direction::RIGHT,
                           posY,
                           posX - 1);
        }

        if (fromDirection != Direction::RIGHT
            && posX + 1 < grid[posY].size())
        {
            uniquePathsCounter +=
                moveToCell(Direction::LEFT,
                           posY,
                           posX + 1);
        }

        if (fromDirection != Direction::UP
            && posY - 1 >= 0)
        {
            uniquePathsCounter +=
                moveToCell(Direction::DOWN,
                           posY - 1,
                           posX);
        }

        if (fromDirection != Direction::DOWN
            && posY + 1 < grid.size())
        {
            uniquePathsCounter +=
                moveToCell(Direction::UP,
                           posY + 1,
                           posX);
        }

        return uniquePathsCounter;
    }
};

int main()
{
    std::cout << Solution().uniquePathsIII(
        {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 2, -1}})
              << '\n';
    std::cout << Solution().uniquePathsIII(
        {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 2}})
              << '\n';
    std::cout << Solution().uniquePathsIII(
        {{0, 1}, {2, 0}})
              << '\n';

    return 0;
}
