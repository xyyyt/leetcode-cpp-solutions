#include <vector>
#include <unordered_set>
#include <queue>
#include <type_traits>
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
    int nearestExit(
        std::vector<std::vector<char>> maze, std::vector<int> entrance)
    {
        if (maze.empty() || entrance.size() < 2)
        {
            return -1;
        }

        VCSet_t vcSet;
        CQueue_t cQueue;
        int stepCounter = 0;

        cQueue.emplace(entrance[0], entrance[1]);

        while (!cQueue.empty())
        {
            CQueue_t cQueue2 = std::move(cQueue);

            while (!cQueue2.empty())
            {
                auto [y, x] = cQueue2.front();

                cQueue2.pop();
                vcSet.emplace(y, x);

                if (isExit(maze.size(),
                           maze[y].size(),
                           y,
                           x,
                           stepCounter))
                {
                    return stepCounter;
                }

                if (x - 1 >= 0
                    && maze[y][x - 1] != to(MazeItem::WALL)
                    && vcSet.find({y, x - 1}) == vcSet.cend())
                {
                    cQueue.emplace(y, x - 1);
                }

                if (x + 1 < maze[y].size()
                    && maze[y][x + 1] != to(MazeItem::WALL)
                    && vcSet.find({y, x + 1}) == vcSet.cend())
                {
                    cQueue.emplace(y, x + 1);
                }

                if (y - 1 >= 0
                    && maze[y - 1][x] != to(MazeItem::WALL)
                    && vcSet.find({y - 1, x}) == vcSet.cend())
                {
                    cQueue.emplace(y - 1, x + 1);
                }

                if (y + 1 < maze.size()
                    && maze[y + 1][x] != to(MazeItem::WALL)
                    && vcSet.find({y + 1, x}) == vcSet.cend())
                {
                    cQueue.emplace(y + 1, x);
                }
            }

            ++stepCounter;
        }

        return -1;
    }

private :
    enum class MazeItem : char { EMPTY = '.', WALL = '+' };

    using MazeItemUnderlying_t = typename std::underlying_type<MazeItem>::type;

    // VC = Visited Cell
    using VCSet_t = std::unordered_set<std::pair<int, int>>;

    // C = Cell
    using CQueue_t = std::queue<std::pair<int, int>>;

    [[nodiscard]]
    inline static constexpr MazeItemUnderlying_t to(MazeItem item) noexcept
    {
        return static_cast<MazeItemUnderlying_t>(item);
    }

    [[nodiscard]]
    inline static constexpr bool isExit(
        int maxMazeY, int maxMazeX, int y, int x, int stepCounter) noexcept
    {
        return stepCounter > 0
            && (x - 1 < 0
                || x + 1 >= maxMazeX
                || y - 1 < 0
                || y + 1 >= maxMazeY);
    }
};

int main()
{
    assert(Solution().nearestExit(
        {{'+','+','.','+'},
         {'.','.','.','+'},
         {'+','+','+','.'}},
        {1, 2})
           == 1);
    assert(Solution().nearestExit(
        {{'+','+','+'},
         {'.','.','.'},
         {'+','+','+'}},
        {1, 0})
           == 2);
    assert(Solution().nearestExit(
        {{'.', '+'}},
        {0, 0})
           == -1);
    assert(Solution().nearestExit(
        {{'.','+'},
         {'.','+'}},
        {1, 0})
           == 1);
    assert(Solution().nearestExit(
        {{'.','.','+'},
         {'+','.','+'},
         {'.','.','.'}},
        {1, 1})
           == 1);
    assert(Solution().nearestExit(
        {{'+','+','+'},
         {'+','.','+'},
         {'+','+','+'}},
        {1, 1})
          == -1);
    assert(Solution().nearestExit(
        {{'+'},
         {'.'},
         {'.'},
         {'.'}},
        {2, 0})
          == 1);

    return 0;
}
