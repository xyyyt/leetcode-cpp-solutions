#include <vector>
#include <utility>
#include <iostream>

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

std::ostream& operator<<(
    std::ostream& os, const std::vector<std::vector<int>>& triangle) noexcept
{
    if (triangle.empty())
    {
        os << "EMPTY";

        return os;
    }

    for (const auto& row : triangle)
    {
        if (row.empty())
        {
            continue;
        }

        auto begin = row.cbegin();
        auto end = row.cend();

        os << '[' << *begin;
        ++begin;

        while (begin != end)
        {
            os << ", " << *begin;
            ++begin;
        }

        os << ']';
    }

    return os;
}

int main()
{
    std::cout << Solution().generate(5) << '\n';
    std::cout << Solution().generate(1) << '\n';

    return 0;
}
