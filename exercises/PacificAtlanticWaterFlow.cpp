#include <vector>
#include <unordered_set>
#include <queue>
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
    std::vector<std::vector<int>> pacificAtlantic(
        std::vector<std::vector<int>> heights)
    {
        if (heights.empty())
        {
            return {};
        }

        std::vector<std::vector<int>> coords;
        VCSet_t cellCanFlowWaterSet;

        for (int y = 0; y < heights.size(); ++y)
        {
            for (int x = 0; x < heights[y].size(); ++x)
            {
                if (cellCanFlowWater(
                    heights, cellCanFlowWaterSet, y, x))
                {
                    using InitList_t = std::initializer_list<int>;

                    coords.emplace_back(InitList_t{y, x});
                    cellCanFlowWaterSet.emplace(y, x);
                }
            }
        }

        return coords;
    }

private :
    // VC = Visited Cell
    using VCSet_t = std::unordered_set<std::pair<int, int>>;

    [[nodiscard]]
    bool cellCanFlowWater(
        const std::vector<std::vector<int>>& heights,
        const VCSet_t& cellCanFlowWaterSet,
        int y,
        int x) const
    {
        std::queue<std::pair<int, int>> queue;
        VCSet_t vcSet;
        bool reachPacificOcean = false;
        bool reachAtlanticOcean = false;

        queue.emplace(y, x);

        while (!queue.empty())
        {
            auto [y2, x2] = queue.front();

            queue.pop();

            if (cellCanFlowWaterSet.find({y2, x2})
                != cellCanFlowWaterSet.cend())
            {
                return true;
            }

            if (y2 == 0 || x2 == 0)
            {
                reachPacificOcean = true;
            }

            if (y2 == heights.size() - 1
                || x2 == heights[y2].size() - 1)
            {
                reachAtlanticOcean = true;
            }

            if (reachPacificOcean && reachAtlanticOcean)
            {
                return true;
            }

            vcSet.emplace(y2, x2);

            // go to left cell
            if (x2 - 1 >= 0
                && heights[y2][x2 - 1] <= heights[y2][x2]
                && vcSet.find({y2, x2 - 1}) == vcSet.cend())
            {
                queue.emplace(y2, x2 - 1);
            }

            // go to right cell
            if (x2 + 1 < heights[y2].size()
                && heights[y2][x2 + 1] <= heights[y2][x2]
                && vcSet.find({y2, x2 + 1}) == vcSet.cend())
            {
                queue.emplace(y2, x2 + 1);
            }

            // go to top cell
            if (y2 - 1 >= 0
                && heights[y2 - 1][x2] <= heights[y2][x2]
                && vcSet.find({y2 - 1, x2}) == vcSet.end())
            {
                queue.emplace(y2 - 1, x2);
            }

            // go to bottom cell
            if (y2 + 1 < heights.size()
                && heights[y2 + 1][x2] <= heights[y2][x2]
                && vcSet.find({y2 + 1, x2}) == vcSet.cend())
            {
                queue.emplace(y2 + 1, x2);
            }
        }

        return false;
    }
};

inline void check(
    const std::vector<std::vector<int>>& coords,
    std::vector<std::vector<int>> expected)
{
    assert(coords == expected);
}

int main()
{
    check(Solution().pacificAtlantic(
        {{1, 2, 2, 3, 5},
         {3, 2, 3, 4, 4},
         {2, 4, 5, 3, 1},
         {6, 7, 1, 4, 5},
         {5, 1, 1, 2, 4}}),
          {{0, 4}, {1, 3}, {1, 4}, {2, 2}, {3, 0}, {3, 1}, {4, 0}});
    check(Solution().pacificAtlantic(
        {{1}}),
          {{0, 0}});
    check(Solution().pacificAtlantic(
        {{2, 1},
         {1, 2}}),
          {{0,0}, {0,1}, {1,0}, {1,1}});
    check(Solution().pacificAtlantic(
        {{3, 3, 3},
         {3, 1, 3},
         {3, 3, 3}}),
          {{0,0}, {0,1}, {0,2}, {1,0}, {1,2}, {2,0}, {2,1}, {2,2}});
    check(Solution().pacificAtlantic(
        {{10, 9, 8, 7},
         {11, 5, 4, 6},
         {12, 3, 2, 1}}),
          {{0,0}, {0,1}, {0,2}, {0,3}, {1,0}, {2,0}});
    check(Solution().pacificAtlantic(
        {{5, 4, 3, 2, 1},
         {6, 7, 8, 9,10}}),
          {{0,0}, {0,1}, {0,2}, {0,3}, {0,4},
           {1,0}, {1,1}, {1,2}, {1,3}, {1,4}});
    check(Solution().pacificAtlantic(
        {{10, 10},
         {10, 1},
         {10, 10}}),
          {{0,0}, {0,1}, {1,0}, {2,0}, {2,1}});

    return 0;
}
