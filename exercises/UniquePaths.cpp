#include <cassert>

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
    assert(Solution().uniquePaths(3, 7) == 28);
    assert(Solution().uniquePaths(3, 2) == 3);
    assert(Solution().uniquePaths(1, 1) == 1);
    assert(Solution().uniquePaths(1, 5) == 1);
    assert(Solution().uniquePaths(7, 1) == 1);
    assert(Solution().uniquePaths(2, 2) == 2);
    assert(Solution().uniquePaths(3, 3) == 6);
    assert(Solution().uniquePaths(4, 4) == 20);
    assert(Solution().uniquePaths(3, 7) == 28);
    assert(Solution().uniquePaths(2, 20) == 20);
    assert(Solution().uniquePaths(15, 2) == 15);
    assert(Solution().uniquePaths(10, 10) == 48620);

    return 0;
}
