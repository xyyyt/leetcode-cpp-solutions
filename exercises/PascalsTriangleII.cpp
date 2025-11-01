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

        std::vector<int> row;

        for (int n = 0; n <= rowIndex; ++n)
        {
            row.resize(n + 1, 1);

            for (int n2 = static_cast<int>(row.size()) - 2;
                 n2 >= 1;
                 --n2)
            {
                row[n2] = row[n2] + row[n2 - 1];
            }
        }

        return row;
    }
};

inline void check(
    const std::vector<int>& row, std::vector<int> expected)
{
    assert(row == expected);
}

int main()
{
    check(Solution().getRow(0), {1});
    check(Solution().getRow(1), {1, 1});
    check(Solution().getRow(2), {1, 2, 1});
    check(Solution().getRow(3), {1, 3, 3, 1});
    check(Solution().getRow(4), {1, 4, 6, 4, 1});

    return 0;
}
