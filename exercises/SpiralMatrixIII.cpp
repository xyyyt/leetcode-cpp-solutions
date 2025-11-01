#include <vector>
#include <iostream>

class Solution
{
public :
    std::vector<std::vector<int>> spiralMatrixIII(
        int rows,
        int cols,
        int rStart,
        int cStart)
    {
        if (rows <= 0
            || cols <= 0
            || (rStart < 0 || rStart >= rows)
            || (cStart < 0 || cStart >= cols))
        {
            return {};
        }

        std::vector<std::vector<int>> positions;
        bool firstCellIsUsed = false;
        bool lastCellIsUsed = false;

        positions.reserve(rows * cols);
        fillPositions(
            rows,
            cols,
            positions,
            firstCellIsUsed,
            lastCellIsUsed,
            Direction::RIGHT,
            0,
            1,
            0,
            rStart,
            cStart);

        return positions;
    }

private :
    enum class Direction : uint8_t { LEFT, RIGHT, UP, DOWN };

    void fillPositions(
        int rows,
        int cols,
        std::vector<std::vector<int>>& positions,
        bool& firstCellIsUsed,
        bool& lastCellIsUsed,
        Direction directionWhereToGo,
        int currentDirectionChangeNb,
        int maxStep,
        int currentStep,
        int posY,
        int posX) const
    {
        /* check if first grid cell (0, 0) and last grid cell (rows - 1, cols - 1)
           have been used (i.e : the entire grid has been covered) */
        if (firstCellIsUsed && lastCellIsUsed)
        {
            return;
        }

        // check if position is inside of the grid
        if ((posY >= 0 && posY < rows) && (posX >= 0 && posX < cols))
        {
            using InitList_t = std::initializer_list<int>;

            positions.emplace_back(InitList_t{posY, posX});
        }

        if (posY == 0 && posX == 0)
        {
            firstCellIsUsed = true;
        }
        else if (posY == rows - 1 && posX == cols - 1)
        {
            lastCellIsUsed = true;
        }

        /* after each two direction change, maxStep must be
           increased to allow the spiral walkening correctly */
        auto getMaxStepOnDirectionChange = [
            currentDirectionChangeNb, maxStep]() noexcept -> int
        {
            bool spiralWidening =
                ((currentDirectionChangeNb + 1) % 2 == 0);

            return (spiralWidening) ? maxStep + 1 : maxStep;
        };

        if (directionWhereToGo == Direction::RIGHT)
        {
            if (currentStep == maxStep)
            {
                fillPositions(
                    rows,
                    cols,
                    positions,
                    firstCellIsUsed,
                    lastCellIsUsed,
                    Direction::DOWN,
                    currentDirectionChangeNb + 1,
                    getMaxStepOnDirectionChange(),
                    1,
                    posY + 1,
                    posX);
            }
            else
            {
                fillPositions(
                    rows,
                    cols,
                    positions,
                    firstCellIsUsed,
                    lastCellIsUsed,
                    directionWhereToGo,
                    currentDirectionChangeNb,
                    maxStep,
                    currentStep + 1,
                    posY,
                    posX + 1);
            }
        }
        else if (directionWhereToGo == Direction::DOWN)
        {
            if (currentStep == maxStep)
            {
                fillPositions(
                    rows,
                    cols,
                    positions,
                    firstCellIsUsed,
                    lastCellIsUsed,
                    Direction::LEFT,
                    currentDirectionChangeNb + 1,
                    getMaxStepOnDirectionChange(),
                    1,
                    posY,
                    posX - 1);
            }
            else
            {
                fillPositions(
                    rows,
                    cols,
                    positions,
                    firstCellIsUsed,
                    lastCellIsUsed,
                    Direction::DOWN,
                    currentDirectionChangeNb,
                    maxStep,
                    currentStep + 1,
                    posY + 1,
                    posX);
            }
        }
        else if (directionWhereToGo == Direction::LEFT)
        {
            if (currentStep == maxStep)
            {
                fillPositions(
                    rows,
                    cols,
                    positions,
                    firstCellIsUsed,
                    lastCellIsUsed,
                    Direction::UP,
                    currentDirectionChangeNb + 1,
                    getMaxStepOnDirectionChange(),
                    1,
                    posY - 1,
                    posX);
            }
            else
            {
                fillPositions(
                    rows,
                    cols,
                    positions,
                    firstCellIsUsed,
                    lastCellIsUsed,
                    Direction::LEFT,
                    currentDirectionChangeNb,
                    maxStep,
                    currentStep + 1,
                    posY,
                    posX - 1);
            }
        }
        else if (directionWhereToGo == Direction::UP)
        {
            if (currentStep == maxStep)
            {
                fillPositions(
                    rows,
                    cols,
                    positions,
                    firstCellIsUsed,
                    lastCellIsUsed,
                    Direction::RIGHT,
                    currentDirectionChangeNb + 1,
                    getMaxStepOnDirectionChange(),
                    1,
                    posY,
                    posX + 1);
            }
            else
            {
                fillPositions(
                    rows,
                    cols,
                    positions,
                    firstCellIsUsed,
                    lastCellIsUsed,
                    Direction::UP,
                    currentDirectionChangeNb,
                    maxStep,
                    currentStep + 1,
                    posY - 1,
                    posX);
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
    std::cout << Solution().spiralMatrixIII(1, 4, 0, 0) << '\n';
    std::cout << Solution().spiralMatrixIII(1, 4, 0, 3) << '\n';
    std::cout << Solution().spiralMatrixIII(5, 6, 1, 4) << '\n';

    return 0;
}
