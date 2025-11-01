#include <iostream>

class Solution
{
public :
    int uniquePaths(int m, int n)
    {
        return (m == 0 || n == 0) ? -1 : uniquePaths(m, n, 0, 0);
    }

private :
    [[nodiscard]]
    int uniquePaths(
        int m, int n, int currentPosM, int currentPosN) const noexcept
    {
        if (currentPosM == m - 1 && currentPosN == n - 1)
        {
            return 1;
        }

        int uniquePathsCounter = 0;

        if (currentPosM + 1 < m)
        {
            uniquePathsCounter +=
                uniquePaths(m, n, currentPosM + 1, currentPosN);
        }

        if (currentPosN + 1 < n)
        {
            uniquePathsCounter +=
                uniquePaths(m, n, currentPosM, currentPosN + 1);
        }

        return uniquePathsCounter;
    }
};

int main()
{
    std::cout << Solution().uniquePaths(3, 7) << '\n';
    std::cout << Solution().uniquePaths(3, 2) << '\n';

    return 0;
}
