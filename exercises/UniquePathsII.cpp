#include <vector>
#include <iostream>

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
        if (currentPosY == obstacleGrid.size() - 1
            && currentPosX == obstacleGrid[obstacleGrid.size() - 1].size() - 1)
        {
            return 1;
        }

        constexpr int OBSTACLE = 1;
        int uniquePathsCounter = 0;

        if (currentPosY + 1 < obstacleGrid.size()
            && obstacleGrid[currentPosY + 1][currentPosX] != OBSTACLE)
        {
            uniquePathsCounter +=
                uniquePathsWithObstacles(
                    obstacleGrid,
                    currentPosY + 1,
                    currentPosX);
        }

        if (currentPosX + 1 < obstacleGrid[currentPosY].size()
            && obstacleGrid[currentPosY][currentPosX + 1] != OBSTACLE)
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
    std::cout << Solution().uniquePathsWithObstacles(
        {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}})
              << '\n';
    std::cout << Solution().uniquePathsWithObstacles(
        {{0, 1}, {0, 0}})
              << '\n';

    return 0;
}
