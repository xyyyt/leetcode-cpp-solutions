#include <vector>
#include <cassert>

class Solution
{
public :
    int uniquePathsWithObstacles(std::vector<std::vector<int>> obstacleGrid)
    {
        return (obstacleGrid.empty()) ?
            -1 : uniquePathsWithObstacles(obstacleGrid, 0, 0);
    }

private :
    [[nodiscard]]
    int uniquePathsWithObstacles(
        const std::vector<std::vector<int>>& obstacleGrid,
        int currentPosY,
        int currentPosX) const
    {
        constexpr int OBSTACLE = 1;

        if (obstacleGrid[currentPosY][currentPosX] == OBSTACLE)
        {
            return 0;
        }
        else if (currentPosY == obstacleGrid.size() - 1
                 && currentPosX == obstacleGrid[obstacleGrid.size() - 1].size() - 1)
        {
            return 1;
        }

        int uniquePathsCounter = 0;

        if (currentPosY + 1 < obstacleGrid.size())
        {
            uniquePathsCounter +=
                uniquePathsWithObstacles(
                    obstacleGrid,
                    currentPosY + 1,
                    currentPosX);
        }

        if (currentPosX + 1 < obstacleGrid[currentPosY].size())
        {
            uniquePathsCounter +=
                uniquePathsWithObstacles(
                    obstacleGrid,
                    currentPosY,
                    currentPosX + 1);
        }

        return uniquePathsCounter;
    }
};

int main()
{
    assert(Solution().uniquePathsWithObstacles(
        {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}})
           == 2);
    assert(Solution().uniquePathsWithObstacles(
        {{0, 1}, {0, 0}})
           == 1);
    assert(Solution().uniquePathsWithObstacles(
        {{0}})
           == 1);
    assert(Solution().uniquePathsWithObstacles(
        {{0, 0}, {0, 0}})
           == 2);
    assert(Solution().uniquePathsWithObstacles(
        {{1, 0}, {0, 0}})
           == 0);
    assert(Solution().uniquePathsWithObstacles(
        {{0, 0}, {0, 1}})
           == 0);
    assert(Solution().uniquePathsWithObstacles(
        {{0, 1}, {1, 0}})
           == 0);
    assert(Solution().uniquePathsWithObstacles(
        {{0, 1, 0}, {0, 0, 0}, {0, 0, 0}})
           == 3);
    assert(Solution().uniquePathsWithObstacles(
        {{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}})
           == 4);
    assert(Solution().uniquePathsWithObstacles(
        {{0, 1, 1}, {1, 1, 1}, {1, 1, 0}})
           == 0);

    return 0;
}
