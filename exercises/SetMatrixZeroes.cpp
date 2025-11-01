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
    void setZeroes(std::vector<std::vector<int>>& matrix)
    {
        if (matrix.empty())
        {
            return;
        }

        CSTZSet_t cstzSet;

        for (int y = 0; y < matrix.size(); ++y)
        {
            for (int x = 0; x < matrix[y].size(); ++x)
            {
                if (matrix[y][x] == 0)
                {
                    cstzSet.emplace(y, x);
                }
            }
        }

        for (auto [y, x] : cstzSet)
        {
            setEntireRangeToZero(
                matrix,
                Direction::RIGHT,
                y,
                x);
            setEntireRangeToZero(
                matrix,
                Direction::DOWN,
                y,
                x);
            setEntireRangeToZero(
                matrix,
                Direction::LEFT,
                y,
                x);
            setEntireRangeToZero(
                matrix,
                Direction::UP,
                y,
                x);
        }
    }

private :
    enum class Direction : uint8_t { LEFT, RIGHT, UP, DOWN };

    // CSTZ = CellsSetToZero
    using CSTZSet_t = std::unordered_set<std::pair<int, int>>;

    void setEntireRangeToZero(
         std::vector<std::vector<int>>& matrix,
         Direction direction,
         int y,
         int x) const
    {
        matrix[y][x] = 0;

        if (direction == Direction::LEFT
            && x - 1 >= 0)
        {
            setEntireRangeToZero(
                matrix,
                Direction::LEFT,
                y,
                x - 1);
        }
        else if (direction == Direction::RIGHT
                 && x + 1 < matrix[y].size())
        {
            setEntireRangeToZero(
                matrix,
                Direction::RIGHT,
                y,
                x + 1);
        }
        else if (direction == Direction::UP
                 && y - 1 >= 0)
        {
            setEntireRangeToZero(
                matrix,
                Direction::UP,
                y - 1,
                x);
        }
        else if (direction == Direction::DOWN
                 && y + 1 < matrix.size())
        {
            setEntireRangeToZero(
                matrix,
                Direction::DOWN,
                y + 1,
                x);
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
    {
        std::vector<std::vector<int>> matrix{
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1}};

        Solution().setZeroes(matrix);
        check(matrix,
              {{1, 0, 1},
               {0, 0, 0},
               {1, 0, 1}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {0, 1, 2, 0},
            {3, 4, 5, 2},
            {1, 3, 1, 5}};

        Solution().setZeroes(matrix);
        check(matrix,
              {{0, 0, 0, 0},
               {0, 4, 5, 0},
               {0, 3, 1, 0}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}};

        Solution().setZeroes(matrix);
        check(matrix,
              {{1, 2, 3},
               {4, 5, 6},
               {7, 8, 9}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {0, 2, 3},
            {4, 5, 6},
            {7, 8, 9}};

        Solution().setZeroes(matrix);
        check(matrix,
              {{0, 0, 0},
               {0, 5, 6},
               {0, 8, 9}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {1, 2, 0},
            {4, 5, 6},
            {7, 8, 9}};

        Solution().setZeroes(matrix);
        check(matrix,
              {{0, 0, 0},
               {4, 5, 0},
               {7, 8, 0}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {1, 2, 3},
            {4, 0, 6},
            {7, 8, 9}};

        Solution().setZeroes(matrix);
        check(matrix,
              {{1, 0, 3},
               {0, 0, 0},
               {7, 0, 9}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {1, 2, 3, 4},
            {5, 6, 0, 8},
            {9, 10, 11, 12}};

        Solution().setZeroes(matrix);
        check(matrix,
              {{1, 2, 0, 4},
               {0, 0, 0, 0},
               {9, 10, 0, 12}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {1, 0, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {0, 14, 15, 16}};

        Solution().setZeroes(matrix);
        check(matrix,
              {{0, 0, 0, 0},
               {0, 0, 7, 8},
               {0, 0, 11, 12},
               {0, 0, 0, 0}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {1},
            {0},
            {3}};

        Solution().setZeroes(matrix);
        check(matrix,
              {{0},
               {0},
               {0}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {1, 2, 3, 0}};

        Solution().setZeroes(matrix);
        check(matrix,
              {{0, 0, 0, 0}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {0, 1, 2, 3}};

        Solution().setZeroes(matrix);
        check(matrix,
              {{0, 0, 0, 0}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {1, 2, 3},
            {4, 5, 6}};

        Solution().setZeroes(matrix);
        check(matrix,
              {{1, 2, 3},
               {4, 5, 6}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {0, 0},
            {0, 0}};

        Solution().setZeroes(matrix);
        check(matrix,
              {{0, 0},
               {0, 0}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {1, 2},
            {3, 4},
            {5, 0},
            {7, 8}};

        Solution().setZeroes(matrix);
        check(matrix,
              {{1, 0},
               {3, 0},
               {0, 0},
               {7, 0}});
    }

    return 0;
}
