#include <vector>
#include <utility>
#include <cassert>

class Solution
{
public :
    std::vector<std::vector<int>> generate(int numRows)
    {
        if (numRows < 1)
        {
            return {};
        }

        std::vector<std::vector<int>> triangle;

        triangle.resize(numRows);

        for (int n = 0; n < numRows; ++n)
        {
            triangle[n].resize(n + 1, 1);

            for (int n2 = 1;
                 n2 <= static_cast<int>(triangle[n].size()) - 2;
                 ++n2)
            {
                triangle[n][n2] =
                    triangle[n - 1][n2] + triangle[n - 1][n2 - 1];
            }
        }

        return triangle;
    }
};

inline void check(
    const std::vector<std::vector<int>>& triangle,
    std::vector<std::vector<int>> expected)
{
    assert(triangle == expected);
}

int main()
{
    check(Solution().generate(5),
          {{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}});
    check(Solution().generate(1),
          {{1}});
    check(Solution().generate(2),
          {{1}, {1, 1}});

    return 0;
}
