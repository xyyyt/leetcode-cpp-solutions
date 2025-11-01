#include <vector>
#include <unordered_set>
#include <queue>
#include <limits>
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
    void rotate(std::vector<std::vector<int>>& matrix)
    {
        if (matrix.size() < 2)
        {
            return;
        }

        VCSet_t vcSet;
        VTRQueue_t vtrQueue;

        emptyFillVTRQueue(vtrQueue, matrix[0].size() - 1);
        rotateMatrix(
            matrix,
            vcSet,
            vtrQueue,
            Direction::RIGHT,
            0,
            0);
    }

private :
    enum class Direction : uint8_t { LEFT, RIGHT, UP, DOWN };

    // VTR = ValuesToReinsert
    using VTRQueue_t = std::queue<int>;

    // VC = Visited Cell
    using VCSet_t = std::unordered_set<std::pair<int, int>>;

    void rotateMatrix(
        std::vector<std::vector<int>>& matrix,
        VCSet_t& vcSet,
        VTRQueue_t& vtrQueue,
        Direction direction,
        int y,
        int x) const
    {
        vcSet.emplace(y, x);
        vtrQueue.emplace(matrix[y][x]);
        matrix[y][x] = vtrQueue.front();
        vtrQueue.pop();

        if (direction == Direction::RIGHT)
        {
            if (x + 1 < matrix[y].size()
                && vcSet.find({y, x + 1}) == vcSet.cend())
            {
                rotateMatrix(
                    matrix,
                    vcSet,
                    vtrQueue,
                    Direction::RIGHT,
                    y,
                    x + 1);
            }
            else if (y + 1 < matrix.size()
                     && vcSet.find({y + 1, x}) == vcSet.cend())
            {
                rotateMatrix(
                    matrix,
                    vcSet,
                    vtrQueue,
                    Direction::DOWN,
                    y + 1,
                    x);
            }
        }
        else if (direction == Direction::DOWN)
        {
            if (y + 1 < matrix.size()
                && vcSet.find({y + 1, x}) == vcSet.cend())
            {
                rotateMatrix(
                    matrix,
                    vcSet,
                    vtrQueue,
                    Direction::DOWN,
                    y + 1,
                    x);
            }
            else if (x - 1 >= 0
                     && vcSet.find({y, x - 1}) == vcSet.cend())
            {
                rotateMatrix(
                     matrix,
                     vcSet,
                     vtrQueue,
                     Direction::LEFT,
                     y,
                     x - 1);
            }
        }
        else if (direction == Direction::LEFT)
        {
            if (x - 1 >= 0
                && vcSet.find({y, x - 1}) == vcSet.cend())
            {
                rotateMatrix(
                    matrix,
                    vcSet,
                    vtrQueue,
                    Direction::LEFT,
                    y,
                    x - 1);
            }
            else if (y - 1 >= 0)
            {
                if (vcSet.find({y - 1, x}) == vcSet.cend())
                {
                    rotateMatrix(
                        matrix,
                        vcSet,
                        vtrQueue,
                        Direction::UP,
                        y - 1,
                        x);
                }
                else
                {
                    for (int x2 = x; !vtrQueue.empty(); ++x2)
                    {
                        matrix[y - 1][x2] = vtrQueue.front();
                        vtrQueue.pop();
                    }
                }
            }
        }
        else if (direction == Direction::UP)
        {
            if (y - 1 >= 0
                && vcSet.find({y - 1, x}) == vcSet.cend())
            {
                rotateMatrix(
                    matrix,
                    vcSet,
                    vtrQueue,
                    Direction::UP,
                    y - 1,
                    x);
            }
            else
            {
                if (y - 1 >= 0)
                {
                    for (int x2 = x; !vtrQueue.empty(); ++x2)
                    {
                        matrix[y - 1][x2] = vtrQueue.front();
                        vtrQueue.pop();
                    }

                    emptyFillVTRQueue(
                        vtrQueue, matrix[y].size() - (1 + (x + 1) * 2));
                }

                if (x + 1 < matrix[y].size()
                    && vcSet.find({y, x + 1}) == vcSet.cend())
                {
                    rotateMatrix(
                        matrix,
                        vcSet,
                        vtrQueue,
                        Direction::RIGHT,
                        y,
                        x + 1);
                }
            }
        }
    }

    void emptyFillVTRQueue(VTRQueue_t& vtrQueue, int size) const
    {
        for (int n = 0; n < size; ++n)
        {
            vtrQueue.emplace(std::numeric_limits<int>::min());
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
        std::vector<std::vector<int>> matrix{{1}};

        Solution().rotate(matrix);

        // expectation after rotate : 1

        check(matrix,
              {{1}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {1, 2},
            {3, 4}};

        Solution().rotate(matrix);

        // expectation after rotate : 3 1
        //                            4 2

        check(matrix,
              {{3, 1},
               {4, 2}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}};

        Solution().rotate(matrix);

        // expectation after rotate : 7 4 1
        //                            8 5 2
        //                            9 6 3

        check(matrix,
              {{7, 4, 1},
               {8, 5, 2},
               {9, 6, 3}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {5, 1, 9, 11},
            {2, 4, 8, 10},
            {13, 3, 6, 7},
            {15, 14, 12, 16}};

        Solution().rotate(matrix);

        // expectation after rotate : 15 13  2  5
        //                            14  3  4  1
        //                            12  6  8  9
        //                            16  7 10 11

        check(matrix,
              {{15, 13, 2, 5},
               {14, 3, 4, 1},
               {12, 6, 8, 9},
               {16, 7, 10, 11}});
    }

    {
        std::vector<std::vector<int>> matrix{
            {1, 2, 3, 4, 5},
            {6, 7, 8, 9, 10},
            {11, 12, 13, 14, 15},
            {16, 17, 18, 19, 20},
            {21, 22, 23, 24, 25}};

        Solution().rotate(matrix);

        // expectation after rotate : 21 16 11 6  1
        //                            22 17 12 7  2
        //                            23 18 13 8  3
        //                            24 19 14 9  4
        //                            25 20 15 10 5

        check(matrix,
              {{21, 16, 11, 6, 1},
               {22, 17, 12, 7, 2},
               {23, 18, 13, 8, 3},
               {24, 19, 14, 9, 4},
               {25, 20, 15, 10, 5}});
    }

    return 0;
}
