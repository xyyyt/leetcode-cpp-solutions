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
        Direction directionWhereToGo,
        int posY,
        int posX) const
    {
        elements.emplace_back(matrix[posY][posX]);
        vcSet.emplace(posY, posX);

        if (directionWhereToGo == Direction::RIGHT)
        {
            if (posX < matrix[posY].size() - 1
                && vcSet.find({posY, posX + 1}) == vcSet.cend())
            {
                spiralOrder(
                    matrix,
                    elements,
                    vcSet,
                    Direction::RIGHT,
                    posY,
                    posX + 1);
            }
            else if (posY < matrix.size() - 1
                     && vcSet.find({posY + 1, posX}) == vcSet.cend())
            {
                spiralOrder(
                    matrix,
                    elements,
                    vcSet,
                    Direction::DOWN,
                    posY + 1,
                    posX);
            }
        }
        else if (directionWhereToGo == Direction::DOWN)
        {
            if (posY < matrix.size() - 1
                && vcSet.find({posY + 1, posX}) == vcSet.cend())
            {
                spiralOrder(
                    matrix,
                    elements,
                    vcSet,
                    Direction::DOWN,
                    posY + 1,
                    posX);
            }
            else if (posX > 0
                     && vcSet.find({posY, posX - 1}) == vcSet.cend())
            {
                spiralOrder(
                    matrix,
                    elements,
                    vcSet,
                    Direction::LEFT,
                    posY,
                    posX - 1);
            }
        }
        else if (directionWhereToGo == Direction::LEFT)
        {
            if (posX > 0
                && vcSet.find({posY, posX - 1}) == vcSet.cend())
            {
                spiralOrder(
                    matrix,
                    elements,
                    vcSet,
                    Direction::LEFT,
                    posY,
                    posX - 1);
            }
            else if (posY > 0
                     && vcSet.find({posY - 1, posX}) == vcSet.cend())
            {
                spiralOrder(
                    matrix,
                    elements,
                    vcSet,
                    Direction::UP,
                    posY - 1,
                    posX);
            }
        }
        else if (directionWhereToGo == Direction::UP)
        {
            if (posY > 0
                && vcSet.find({posY - 1, posX}) == vcSet.cend())
            {
                spiralOrder(
                    matrix,
                    elements,
                    vcSet,
                    Direction::UP,
                    posY - 1,
                    posX);
            }
            else if (posX < matrix[posY].size() - 1
                     && vcSet.find({posY, posX + 1}) == vcSet.cend())
            {
                spiralOrder(
                    matrix,
                    elements,
                    vcSet,
                    Direction::RIGHT,
                    posY,
                    posX + 1);
            }
        }
    }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<int>& elements) noexcept
{
    if (elements.empty())
    {
        os << "EMPTY";

        return os;
    }

    auto begin = elements.cbegin();
    auto end = elements.cend();

    os << *begin;
    ++begin;

    while (begin != end)
    {
        os << ", " << *begin;
        ++begin;
    }

    return os;
}

int main()
{
    std::cout << Solution().spiralOrder(
        {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}})
              << '\n';
    std::cout << Solution().spiralOrder(
        {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}})
              << '\n';

    return 0;
}
