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
        Direction directionWhereToGo,
        int posY,
        int posX,
        int i) const
    {
        matrix[posY][posX] = i;
        vcSet.emplace(posY, posX);

        if (directionWhereToGo == Direction::RIGHT)
        {
            if (posX < matrix[posY].size() - 1
                && vcSet.find({posY, posX + 1}) == vcSet.cend())
            {
                fillMatrix(
                    matrix,
                    vcSet,
                    Direction::RIGHT,
                    posY,
                    posX + 1,
                    i + 1);
            }
            else if (posY < matrix.size() - 1
                     && vcSet.find({posY + 1, posX}) == vcSet.cend())
            {
                fillMatrix(
                    matrix,
                    vcSet,
                    Direction::DOWN,
                    posY + 1,
                    posX,
                    i + 1);
            }
        }
        else if (directionWhereToGo == Direction::DOWN)
        {
            if (posY < matrix.size() - 1
                && vcSet.find({posY + 1, posX}) == vcSet.cend())
            {
                fillMatrix(
                    matrix,
                    vcSet,
                    Direction::DOWN,
                    posY + 1,
                    posX,
                    i + 1);
            }
            else if (posX > 0
                     && vcSet.find({posY, posX - 1}) == vcSet.cend())
            {
                fillMatrix(
                    matrix,
                    vcSet,
                    Direction::LEFT,
                    posY,
                    posX - 1,
                    i + 1);
            }
        }
        else if (directionWhereToGo == Direction::LEFT)
        {
            if (posX > 0
                && vcSet.find({posY, posX - 1}) == vcSet.cend())
            {
                fillMatrix(
                    matrix,
                    vcSet,
                    Direction::LEFT,
                    posY,
                    posX - 1,
                    i + 1);
            }
            else if (posY > 0
                     && vcSet.find({posY - 1, posX}) == vcSet.cend())
            {
                fillMatrix(
                    matrix,
                    vcSet,
                    Direction::UP,
                    posY - 1,
                    posX,
                    i + 1);
            }
        }
        else if (directionWhereToGo == Direction::UP)
        {
            if (posY > 0
                && vcSet.find({posY - 1, posX}) == vcSet.cend())
            {
                fillMatrix(
                    matrix,
                    vcSet,
                    Direction::UP,
                    posY - 1,
                    posX,
                    i + 1);
            }
            else if (posX < matrix[posY].size() - 1
                     && vcSet.find({posY, posX + 1}) == vcSet.cend())
            {
                fillMatrix(
                    matrix,
                    vcSet,
                    Direction::RIGHT,
                    posY,
                    posX + 1,
                    i + 1);
            }
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
    std::cout << Solution().generateMatrix(3) << '\n';
    std::cout << Solution().generateMatrix(1) << '\n';

    return 0;
}
