#include <vector>
#include <cstdint>
#include <cassert>

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
        Direction direction,
        int currentDirectionChangeNb,
        int maxStep,
        int currentStep,
        int y,
        int x) const
    {
        /* check if first grid cell (0, 0) and last grid cell (rows - 1, cols - 1)
           have been used (i.e : the entire grid has been covered) */
        if (firstCellIsUsed && lastCellIsUsed)
        {
            return;
        }

        // check if position is inside of the grid
        if ((y >= 0 && y < rows) && (x >= 0 && x < cols))
        {
            using InitList_t = std::initializer_list<int>;

            positions.emplace_back(InitList_t{y, x});
        }

        if (y == 0 && x == 0)
        {
            firstCellIsUsed = true;
        }
        else if (y == rows - 1 && x == cols - 1)
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

        if (direction == Direction::RIGHT)
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
                    y + 1,
                    x);
            }
            else
            {
                fillPositions(
                    rows,
                    cols,
                    positions,
                    firstCellIsUsed,
                    lastCellIsUsed,
                    direction,
                    currentDirectionChangeNb,
                    maxStep,
                    currentStep + 1,
                    y,
                    x + 1);
            }
        }
        else if (direction == Direction::DOWN)
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
                    y,
                    x - 1);
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
                    y + 1,
                    x);
            }
        }
        else if (direction == Direction::LEFT)
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
                    y - 1,
                    x);
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
                    y,
                    x - 1);
            }
        }
        else if (direction == Direction::UP)
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
                    y,
                    x + 1);
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
                    y - 1,
                    x);
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
    check(Solution().spiralMatrixIII(1, 4, 0, 0),
          {{0, 0}, {0, 1}, {0, 2}, {0, 3}});
    check(Solution().spiralMatrixIII(1, 4, 0, 3),
          {{0, 3}, {0, 2}, {0, 1}, {0, 0}});
    check(Solution().spiralMatrixIII(5, 6, 1, 4),
          {{1, 4}, {1, 5}, {2, 5}, {2, 4}, {2, 3}, {1, 3}, {0, 3}, {0, 4},
           {0, 5}, {3, 5}, {3, 4}, {3, 3}, {3, 2}, {2, 2}, {1, 2}, {0, 2},
           {4, 5}, {4, 4}, {4, 3}, {4, 2}, {4, 1}, {3, 1}, {2, 1}, {1, 1},
           {0, 1}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}});

    return 0;
}
