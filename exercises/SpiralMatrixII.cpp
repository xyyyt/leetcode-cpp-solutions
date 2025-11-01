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
    std::vector<std::vector<int>> generateMatrix(int n)
    {
        if (n < 1)
        {
            return {};
        }

        std::vector<std::vector<int>> matrix = buildMatrix(n);
        VCSet_t vcSet;

        fillMatrix(matrix, vcSet, Direction::RIGHT, 0, 0, 1);

        return matrix;
    }

private :
    enum class Direction : uint8_t { LEFT, RIGHT, UP, DOWN };

    // VC = Visited Cell
    using VCSet_t = std::unordered_set<std::pair<int, int>>;

    [[nodiscard]]
    inline std::vector<std::vector<int>> buildMatrix(int n) const
    {
        std::vector<std::vector<int>> matrix(n);

        for (int n2 = 0; n2 < n; ++n2)
        {
            matrix[n2].resize(n);
        }

        return matrix;
    }

    void fillMatrix(
        std::vector<std::vector<int>>& matrix,
        VCSet_t& vcSet,
        Direction direction,
        int y,
        int x,
        int i) const
    {
        matrix[y][x] = i;
        vcSet.emplace(y, x);

        if (direction == Direction::RIGHT)
        {
            if (x < matrix[y].size() - 1
                && vcSet.find({y, x + 1}) == vcSet.cend())
            {
                fillMatrix(
                    matrix,
                    vcSet,
                    Direction::RIGHT,
                    y,
                    x + 1,
                    i + 1);
            }
            else if (y < matrix.size() - 1
                     && vcSet.find({y + 1, x}) == vcSet.cend())
            {
                fillMatrix(
                    matrix,
                    vcSet,
                    Direction::DOWN,
                    y + 1,
                    x,
                    i + 1);
            }
        }
        else if (direction == Direction::DOWN)
        {
            if (y < matrix.size() - 1
                && vcSet.find({y + 1, x}) == vcSet.cend())
            {
                fillMatrix(
                    matrix,
                    vcSet,
                    Direction::DOWN,
                    y + 1,
                    x,
                    i + 1);
            }
            else if (x > 0
                     && vcSet.find({y, x - 1}) == vcSet.cend())
            {
                fillMatrix(
                    matrix,
                    vcSet,
                    Direction::LEFT,
                    y,
                    x - 1,
                    i + 1);
            }
        }
        else if (direction == Direction::LEFT)
        {
            if (x > 0
                && vcSet.find({y, x - 1}) == vcSet.cend())
            {
                fillMatrix(
                    matrix,
                    vcSet,
                    Direction::LEFT,
                    y,
                    x - 1,
                    i + 1);
            }
            else if (y > 0
                     && vcSet.find({y - 1, x}) == vcSet.cend())
            {
                fillMatrix(
                    matrix,
                    vcSet,
                    Direction::UP,
                    y - 1,
                    x,
                    i + 1);
            }
        }
        else if (direction == Direction::UP)
        {
            if (y > 0
                && vcSet.find({y - 1, x}) == vcSet.cend())
            {
                fillMatrix(
                    matrix,
                    vcSet,
                    Direction::UP,
                    y - 1,
                    x,
                    i + 1);
            }
            else if (x < matrix[y].size() - 1
                     && vcSet.find({y, x + 1}) == vcSet.cend())
            {
                fillMatrix(
                    matrix,
                    vcSet,
                    Direction::RIGHT,
                    y,
                    x + 1,
                    i + 1);
            }
        }
    }
};

inline void check(
    const std::vector<std::vector<int>>& matrix,
    std::vector<std::vector<int>> expected)
{
    assert(matrix == expected);
}

int main()
{
    check(Solution().generateMatrix(3),
          {{1, 2, 3},
           {8, 9, 4},
           {7, 6, 5}});
    check(Solution().generateMatrix(1),
          {{1}});
    check(Solution().generateMatrix(2),
          {{1, 2},
           {4, 3}});
    check(Solution().generateMatrix(4),
          {{1,  2,  3,  4},
           {12, 13, 14, 5},
           {11, 16, 15, 6},
           {10, 9,  8,  7}});
    check(Solution().generateMatrix(5),
          {{1,  2,  3,  4,  5},
           {16, 17, 18, 19, 6},
           {15, 24, 25, 20, 7},
           {14, 23, 22, 21, 8},
           {13, 12, 11, 10, 9}});
    check(Solution().generateMatrix(6),
          {{1,  2,  3,  4,  5,  6},
           {20, 21, 22, 23, 24, 7},
           {19, 32, 33, 34, 25, 8},
           {18, 31, 36, 35, 26, 9},
           {17, 30, 29, 28, 27, 10},
           {16, 15, 14, 13, 12, 11}});

    return 0;
}
