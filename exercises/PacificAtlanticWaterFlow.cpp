#include <vector>
#include <unordered_set>
#include <queue>
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
        int posY,
        int posX) const
    {
        std::queue<std::pair<int, int>> queue;
        VCSet_t vcSet;
        bool reachPacificOcean = false;
        bool reachAtlanticOcean = false;

        queue.emplace(posY, posX);

        while (!queue.empty())
        {
            auto [posY2, posX2] = queue.front();

            queue.pop();

            if (cellCanFlowWaterSet.find({posY2, posX2})
                != cellCanFlowWaterSet.cend())
            {
                return true;
            }

            if (posY2 == 0 || posX2 == 0)
            {
                reachPacificOcean = true;
            }

            if (posY2 == heights.size() - 1
                || posX2 == heights[posY2].size() - 1)
            {
                reachAtlanticOcean = true;
            }

            if (reachPacificOcean && reachAtlanticOcean)
            {
                return true;
            }

            vcSet.emplace(posY2, posX2);

            // go to left cell
            if (posX2 - 1 >= 0
                && heights[posY2][posX2 - 1] <= heights[posY2][posX2]
                && vcSet.find({posY2, posX2 - 1}) == vcSet.cend())
            {
                queue.emplace(posY2, posX2 - 1);
            }

            // go to right cell
            if (posX2 + 1 < heights[posY2].size()
                && heights[posY2][posX2 + 1] <= heights[posY2][posX2]
                && vcSet.find({posY2, posX2 + 1}) == vcSet.cend())
            {
                queue.emplace(posY2, posX2 + 1);
            }

            // go to top cell
            if (posY2 - 1 >= 0
                && heights[posY2 - 1][posX2] <= heights[posY2][posX2]
                && vcSet.find({posY2 - 1, posX2}) == vcSet.end())
            {
                queue.emplace(posY2 - 1, posX2);
            }

            // go to bottom cell
            if (posY2 + 1 < heights.size()
                && heights[posY2 + 1][posX2] <= heights[posY2][posX2]
                && vcSet.find({posY2 + 1, posX2}) == vcSet.cend())
            {
                queue.emplace(posY2 + 1, posX2);
            }
        }

        return false;
    }
};

std::ostream& operator<<(
    std::ostream& os,
    const std::vector<std::vector<int>>& coords) noexcept
{
    if (coords.empty())
    {
        os << "EMPTY";

        return os;
    }

    for (const auto& coord : coords)
    {
        if (coord.empty())
        {
            continue;
        }

        auto begin = coord.cbegin();
        auto end = coord.cend();

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
    std::cout << Solution().pacificAtlantic(
        {{1, 2, 2, 3, 5},
         {3, 2, 3, 4, 4},
         {2, 4, 5, 3, 1},
         {6, 7, 1, 4, 5},
         {5, 1, 1, 2, 4}})
              << '\n';
    std::cout << Solution().pacificAtlantic(
         {{1}})
              << '\n';

    return 0;
}
