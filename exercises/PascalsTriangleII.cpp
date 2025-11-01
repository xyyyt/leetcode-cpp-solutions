#include <vector>
#include <utility>
#include <cassert>

class Solution
{
public :
    std::vector<int> getRow(int rowIndex)
    {
        if (rowIndex < 0)
        {
            return {};
        }

        using InitList_t = std::initializer_list<int>;

        std::vector<std::vector<int>> triangle;

        triangle.reserve(rowIndex + 1);
        triangle.emplace_back(InitList_t{1});

        if (rowIndex == 0)
        {
            return triangle[0];
        }

        triangle.emplace_back(InitList_t{1, 1});

        if (rowIndex == 1)
        {
            return triangle[1];
        }

        for (int n = 2; n <= rowIndex; ++n)
        {
            const auto& previousRow = triangle[n - 1];
            std::vector<int> row;

            row.reserve(previousRow.size() + 1);
            row.emplace_back(1);

            for (int n2 = 0; n2 < previousRow.size() - 1; ++n2)
            {
                row.emplace_back(previousRow[n2] + previousRow[n2 + 1]);
            }

            row.emplace_back(1);
            triangle.emplace_back(std::move(row));
        }

        return triangle[rowIndex];
    }
};

inline void check(
    const std::vector<int>& row, std::vector<int> expected)
{
    assert(row == expected);
}

int main()
{
    check(Solution().getRow(3), {1, 3, 3, 1});
    check(Solution().getRow(0), {1});
    check(Solution().getRow(1), {1, 1});

    return 0;
}
