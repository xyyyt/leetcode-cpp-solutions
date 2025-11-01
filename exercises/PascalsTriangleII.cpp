#include <vector>
#include <utility>
#include <iostream>

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

        return triangle[rowIndex];
    }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<int>& row) noexcept
{
    if (row.empty())
    {
        os << "EMPTY";

        return os;
    }

    auto begin = row.cbegin();
    auto end = row.cend();

    os << *begin;
    ++begin;

    while (begin != end)
    {
        os << ", " << *begin;
        ++begin;
    }

    return os;
}

int main()
{
    std::cout << Solution().getRow(3) << '\n';
    std::cout << Solution().getRow(0) << '\n';
    std::cout << Solution().getRow(1) << '\n';

    return 0;
}
