#include <vector>
#include <unordered_set>
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
         Direction directionWhereToGo,
         int posY,
         int posX) const
    {
        matrix[posY][posX] = 0;

        if (directionWhereToGo == Direction::LEFT
            && posX - 1 >= 0)
        {
            setEntireRangeToZero(
                matrix,
                Direction::LEFT,
                posY,
                posX - 1);
        }
        else if (directionWhereToGo == Direction::RIGHT
                 && posX + 1 < matrix[posY].size())
        {
            setEntireRangeToZero(
                matrix,
                Direction::RIGHT,
                posY,
                posX + 1);
        }
        else if (directionWhereToGo == Direction::UP
                 && posY - 1 >= 0)
        {
            setEntireRangeToZero(
                matrix,
                Direction::UP,
                posY - 1,
                posX);
        }
        else if (directionWhereToGo == Direction::DOWN
                 && posY + 1 < matrix.size())
        {
            setEntireRangeToZero(
                matrix,
                Direction::DOWN,
                posY + 1,
                posX);
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

    for (const auto& row : matrix)
    {
        if (row.empty())
        {
            continue;
        }

        auto begin = row.cbegin();
        auto end = row.cend();

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
        std::vector<std::vector<int>> matrix{
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1}};

        Solution().setZeroes(matrix);
        std::cout << matrix << '\n';
    }

    {
        std::vector<std::vector<int>> matrix{
            {0, 1, 2, 0},
            {3, 4, 5, 2},
            {1, 3, 1, 5}};

        Solution().setZeroes(matrix);
        std::cout << matrix << '\n';
    }

    return 0;
}
