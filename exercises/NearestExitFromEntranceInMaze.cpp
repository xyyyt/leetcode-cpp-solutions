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
        size_t operator()(const std::pair<int, int>& cell) const noexcept
        {
            return std::hash<int>()(cell.first)
                ^ std::hash<int>()(cell.second);
        }
    };
}

class Solution
{
public :
    int nearestExit(
        std::vector<std::vector<char>> maze, std::vector<int> entrance)
    {
        return (maze.empty() || entrance.empty() || entrance.size() < 2) ?
            -1 : nearestExit(
                     maze,
                     {},
                     // {},
                     0,
                     Direction::UNKNOWN,
                     entrance[0],
                     entrance[1]);
    }

private :
    enum class MazeItem : char { EMPTY = '.', WALL = '+' };
    enum class Direction : uint8_t { LEFT, RIGHT, UP, DOWN, UNKNOWN };

    using MazeItemUnderlying_t = typename std::underlying_type<MazeItem>::type;

    // VC = Visited Cell
    using VCSet_t = std::unordered_set<std::pair<int, int>>;
    // using VCSetConstIterator_t = VCSet_t::const_iterator;

    // For debug only
    // using VCList_t = std::list<VCSetConstIterator_t>;

    [[nodiscard]]
    inline static constexpr MazeItemUnderlying_t to(MazeItem item) noexcept
    {
        return static_cast<MazeItemUnderlying_t>(item);
    }

    [[nodiscard]]
    int nearestExit(
        const std::vector<std::vector<char>>& maze,
        const VCSet_t& vcSet,
        // const VCList_t& vcList,
        int stepCounter,
        Direction fromDirection,
        int posY,
        int posX) const
    {
        if (maze[posY][posX] == to(MazeItem::WALL)
            || vcSet.find({posY, posX}) != vcSet.cend())
        {
            return -1;
        }

        if (maze[posY][posX] == to(MazeItem::EMPTY)
            && ((posY == 0 || posY == maze.size() - 1)
                || (posX == 0 || posX == maze[posY].size() - 1))
            && fromDirection != Direction::UNKNOWN)
        {
            // for (const auto& itFromVCSet : vcList)
            // {
            //     std::cout << "y : "
            //               << itFromVCSet->first
            //               << ", x : "
            //               << itFromVCSet->second
            //               << '\n';
            // }

            // std::cout << "y : "
            //           << posY
            //           << ", x : "
            //           << posX
            //           << "\n\n";

            return stepCounter;
        }

        int stepCounterMin = -1;
        auto moveToCell = [&](
            Direction fromDirection2,
            int posY2,
            int posX2) -> void
        {
            VCSet_t vcSet2 = vcSet;
            // VCList_t vcList = vcList;

            [[maybe_unused]] auto res = vcSet2.emplace(posY, posX);

            // vcList.emplace_back(res.first);

            if (int res = nearestExit(
                    maze,
                    vcSet2,
                    // vcList,
                    stepCounter + 1,
                    fromDirection2,
                    posY2,
                    posX2);
                res != -1)
            {
                stepCounterMin = (stepCounterMin == -1) ?
                    res : std::min(stepCounterMin, res);
            }
        };

        if (fromDirection != Direction::LEFT
            && posX - 1 >= 0)
        {
            moveToCell(Direction::RIGHT, posY, posX - 1);
        }

        if (fromDirection != Direction::RIGHT
            && posX + 1 < maze[posY].size())
        {
            moveToCell(Direction::LEFT, posY, posX + 1);
        }

        if (fromDirection != Direction::UP
            && posY - 1 >= 0)
        {
            moveToCell(Direction::DOWN, posY - 1, posX);
        }

        if (fromDirection != Direction::DOWN
            && posY + 1 < maze.size())
        {
            moveToCell(Direction::UP, posY + 1, posX);
        }

        return stepCounterMin;
    }
};

int main()
{
    std::cout << Solution().nearestExit(
        {{'+','+','.','+'},
         {'.','.','.','+'},
         {'+','+','+','.'}},
        {1, 2})
              << '\n';
    std::cout << Solution().nearestExit(
        {{'+','+','+'},
         {'.','.','.'},
         {'+','+','+'}},
        {1, 0})
              << '\n';
    std::cout << Solution().nearestExit(
        {{'.', '+'}},
        {0, 0})
              << '\n';

    return 0;
}
