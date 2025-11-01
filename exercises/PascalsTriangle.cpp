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

        using InitList_t = std::initializer_list<int>;

        std::vector<std::vector<int>> triangle;

        triangle.reserve(numRows);
        triangle.emplace_back(InitList_t{1});

        if (numRows == 1)
        {
            return triangle;
        }

        triangle.emplace_back(InitList_t{1, 1});

        if (numRows == 2)
        {
            return triangle;
        }

        for (int n = 2; n < numRows; ++n)
        {
            std::vector<int> row;
            const auto& previousRow = triangle[n - 1];

            row.reserve(previousRow.size() + 1);
            row.emplace_back(1);

            for (int n2 = 0; n2 < previousRow.size() - 1; ++n2)
            {
                row.emplace_back(previousRow[n2] + previousRow[n2 + 1]);
            }

            row.emplace_back(1);
            triangle.emplace_back(std::move(row));
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

    return 0;
}
