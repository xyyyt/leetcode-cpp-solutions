#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

class Solution
{
public :
    std::vector<int> sortedSquares(std::vector<int> nums)
    {
        std::vector<int> squares;

        squares.reserve(nums.size());

        for (auto num : nums)
        {
            squares.emplace_back(std::pow(num, 2));
        }

        std::sort(squares.begin(), squares.end());

        return squares;
    }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<int>& squares) noexcept
{
    if (squares.empty())
    {
        os << "EMPTY";

        return os;
    }

    auto begin = squares.cbegin();
    auto end = squares.cend();

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
    std::cout << Solution().sortedSquares({-4, -1, 0, 3, 10}) << '\n';
    std::cout << Solution().sortedSquares({-7, -3, 2, 3, 11}) << '\n';

    return 0;
}
