#include <vector>
#include <unordered_set>
#include <queue>
#include <limits>
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
        Direction directionWhereToGo,
        int posY,
        int posX) const
    {
        vcSet.emplace(posY, posX);
        vtrQueue.emplace(matrix[posY][posX]);
        matrix[posY][posX] = vtrQueue.front();
        vtrQueue.pop();

        if (directionWhereToGo == Direction::RIGHT)
        {
            if (posX + 1 < matrix[posY].size()
                && vcSet.find({posY, posX + 1}) == vcSet.cend())
            {
                rotateMatrix(
                    matrix,
                    vcSet,
                    vtrQueue,
                    Direction::RIGHT,
                    posY,
                    posX + 1);
            }
            else if (posY + 1 < matrix.size()
                     && vcSet.find({posY + 1, posX}) == vcSet.cend())
            {
                rotateMatrix(
                    matrix,
                    vcSet,
                    vtrQueue,
                    Direction::DOWN,
                    posY + 1,
                    posX);
            }
        }
        else if (directionWhereToGo == Direction::DOWN)
        {
            if (posY + 1 < matrix.size()
                && vcSet.find({posY + 1, posX}) == vcSet.cend())
            {
                rotateMatrix(
                    matrix,
                    vcSet,
                    vtrQueue,
                    Direction::DOWN,
                    posY + 1,
                    posX);
            }
            else if (posX - 1 >= 0
                     && vcSet.find({posY, posX - 1}) == vcSet.cend())
            {
                rotateMatrix(
                     matrix,
                     vcSet,
                     vtrQueue,
                     Direction::LEFT,
                     posY,
                     posX - 1);
            }
        }
        else if (directionWhereToGo == Direction::LEFT)
        {
            if (posX - 1 >= 0
                && vcSet.find({posY, posX - 1}) == vcSet.cend())
            {
                rotateMatrix(
                    matrix,
                    vcSet,
                    vtrQueue,
                    Direction::LEFT,
                    posY,
                    posX - 1);
            }
            else if (posY - 1 >= 0)
            {
                if (vcSet.find({posY - 1, posX}) == vcSet.cend())
                {
                    rotateMatrix(
                        matrix,
                        vcSet,
                        vtrQueue,
                        Direction::UP,
                        posY - 1,
                        posX);
                }
                else
                {
                    for (int posX2 = posX; !vtrQueue.empty(); ++posX2)
                    {
                        matrix[posY - 1][posX2] = vtrQueue.front();
                        vtrQueue.pop();
                    }
                }
            }
        }
        else if (directionWhereToGo == Direction::UP)
        {
            if (posY - 1 >= 0
                && vcSet.find({posY - 1, posX}) == vcSet.cend())
            {
                rotateMatrix(
                    matrix,
                    vcSet,
                    vtrQueue,
                    Direction::UP,
                    posY - 1,
                    posX);
            }
            else
            {
                if (posY - 1 >= 0)
                {
                    for (int posX2 = posX; !vtrQueue.empty(); ++posX2)
                    {
                        matrix[posY - 1][posX2] = vtrQueue.front();
                        vtrQueue.pop();
                    }

                    emptyFillVTRQueue(
                        vtrQueue, matrix[posY].size() - (1 + (posX + 1) * 2));
                }

                if (posX + 1 < matrix[posY].size()
                    && vcSet.find({posY, posX + 1}) == vcSet.cend())
                {
                    rotateMatrix(
                        matrix,
                        vcSet,
                        vtrQueue,
                        Direction::RIGHT,
                        posY,
                        posX + 1);
                }
            }
        }
    }

    void emptyFillVTRQueue(VTRQueue_t& vtrQueue, int size) const
    {
        constexpr int MIN_VALUE = std::numeric_limits<int>::min();

        for (int n = 0; n < size; ++n)
        {
            vtrQueue.emplace(MIN_VALUE);
        }
    }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<std::vector<int>>& matrix) noexcept
{
    if (matrix.empty())
    {
        os << "EMPTY";

        return os;
    }

    for (const auto& range : matrix)
    {
        if (range.empty())
        {
            continue;
        }

        auto begin = range.cbegin();
        auto end = range.cend();

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
    {
        std::vector<std::vector<int>> matrix{{1}};

        Solution().rotate(matrix);

        // expectation after rotate : 1

        std::cout << matrix << '\n';
    }

    {
        std::vector<std::vector<int>> matrix{
            {1, 2},
            {3, 4}};

        Solution().rotate(matrix);

        // expectation after rotate : 3 1
        //                            4 2

        std::cout << matrix << '\n';
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

        std::cout << matrix << '\n';
    }

    {
        std::vector<std::vector<int>> matrix{
            {5, 1, 9, 11},
            {2, 4, 8, 10},
            {13, 3, 6, 7},
            {15, 14, 12, 16}};

        // expectation after rotate : 15 13  2  5
        //                            14  3  4  1
        //                            12  6  8  9
        //                            16  7 10 11

        Solution().rotate(matrix);
        std::cout << matrix << '\n';
    }

    {
        std::vector<std::vector<int>> matrix{
            {1, 2, 3, 4, 5},
            {6, 7, 8, 9, 10},
            {11, 12, 13, 14, 15},
            {16, 17, 18, 19, 20},
            {21, 22, 23, 24, 25}};

        // expectation after rotate : 21 16 11 6  1
        //                            22 17 12 7  2
        //                            23 18 13 8  3
        //                            24 19 14 9  4
        //                            25 20 15 10 5

        Solution().rotate(matrix);
        std::cout << matrix << '\n';
    }

    return 0;
}
