#include <vector>
#include <unordered_set>
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
    std::vector<int> spiralOrder(std::vector<std::vector<int>> matrix)
    {
        if (matrix.empty())
        {
            return {};
        }

        std::vector<int> elements;
        VCSet_t vcSet;

        spiralOrder(matrix, elements, vcSet, Direction::RIGHT, 0, 0);

        return elements;
    }

private :
    enum class Direction : uint8_t { LEFT, RIGHT, UP, DOWN };

    // VC = Visited Cell
    using VCSet_t = std::unordered_set<std::pair<int, int>>;

    void spiralOrder(
        const std::vector<std::vector<int>>& matrix,
        std::vector<int>& elements,
        VCSet_t& vcSet,
        Direction direction,
        int y,
        int x) const
    {
        elements.emplace_back(matrix[y][x]);
        vcSet.emplace(y, x);

        if (direction == Direction::RIGHT)
        {
            if (x < matrix[y].size() - 1
                && vcSet.find({y, x + 1}) == vcSet.cend())
            {
                spiralOrder(
                    matrix,
                    elements,
                    vcSet,
                    Direction::RIGHT,
                    y,
                    x + 1);
            }
            else if (y < matrix.size() - 1
                     && vcSet.find({y + 1, x}) == vcSet.cend())
            {
                spiralOrder(
                    matrix,
                    elements,
                    vcSet,
                    Direction::DOWN,
                    y + 1,
                    x);
            }
        }
        else if (direction == Direction::DOWN)
        {
            if (y < matrix.size() - 1
                && vcSet.find({y + 1, x}) == vcSet.cend())
            {
                spiralOrder(
                    matrix,
                    elements,
                    vcSet,
                    Direction::DOWN,
                    y + 1,
                    x);
            }
            else if (x > 0
                     && vcSet.find({y, x - 1}) == vcSet.cend())
            {
                spiralOrder(
                    matrix,
                    elements,
                    vcSet,
                    Direction::LEFT,
                    y,
                    x - 1);
            }
        }
        else if (direction == Direction::LEFT)
        {
            if (x > 0
                && vcSet.find({y, x - 1}) == vcSet.cend())
            {
                spiralOrder(
                    matrix,
                    elements,
                    vcSet,
                    Direction::LEFT,
                    y,
                    x - 1);
            }
            else if (y > 0
                     && vcSet.find({y - 1, x}) == vcSet.cend())
            {
                spiralOrder(
                    matrix,
                    elements,
                    vcSet,
                    Direction::UP,
                    y - 1,
                    x);
            }
        }
        else if (direction == Direction::UP)
        {
            if (y > 0
                && vcSet.find({y - 1, x}) == vcSet.cend())
            {
                spiralOrder(
                    matrix,
                    elements,
                    vcSet,
                    Direction::UP,
                    y - 1,
                    x);
            }
            else if (x < matrix[y].size() - 1
                     && vcSet.find({y, x + 1}) == vcSet.cend())
            {
                spiralOrder(
                    matrix,
                    elements,
                    vcSet,
                    Direction::RIGHT,
                    y,
                    x + 1);
            }
        }
    }
};

inline void check(
    const std::vector<int>& elements,
    std::vector<int> expected)
{
    assert(elements == expected);
}

int main()
{
    check(Solution().spiralOrder(
        {{1, 2, 3},
         {4, 5, 6},
         {7, 8, 9}}),
          {1, 2, 3, 6, 9, 8, 7, 4, 5});
    check(Solution().spiralOrder(
        {{1, 2, 3, 4},
         {5, 6, 7, 8},
         {9, 10, 11, 12}}),
          {1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7});
    check(Solution().spiralOrder(
        {{1}}),
          {1});
    check(Solution().spiralOrder(
        {{1, 2},
         {3, 4}}),
          {1, 2, 4, 3});
    check(Solution().spiralOrder(
        {{1},
         {2},
         {3},
         {4}}),
          {1, 2, 3, 4});
    check(Solution().spiralOrder(
        {{1, 2, 3, 4}}),
          {1, 2, 3, 4});
    check(Solution().spiralOrder(
        {{1,  2,  3},
         {4,  5,  6}}),
          {1, 2, 3, 6, 5, 4});
    check(Solution().spiralOrder(
        {{1,  2},
         {3,  4},
         {5,  6}}),
          {1, 2, 4, 6, 5, 3});
    check(Solution().spiralOrder(
        {{1,  2,  3},
         {4,  5,  6},
         {7,  8,  9},
         {10, 11, 12}}),
          {1, 2, 3, 6, 9, 12, 11, 10, 7, 4, 5, 8});
    check(Solution().spiralOrder(
        {{1,  2,  3,  4,  5},
         {6,  7,  8,  9,  10},
         {11, 12, 13, 14, 15}}),
          {1, 2, 3, 4, 5, 10, 15, 14, 13, 12, 11, 6, 7, 8, 9});

    return 0;
}
