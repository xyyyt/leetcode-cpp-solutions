#include <vector>
#include <iostream>

class Solution
{
public :
    std::vector<int> countBits(int n)
    {
        std::vector<int> ans;
        size_t max = n + 1;

        ans.reserve(max);

        for (int i = 0; i < max; ++i)
        {
            int oneBitCounter = 0;
            int j = i;

            while (j != 0)
            {
                oneBitCounter += ((j % 2) != 0);
                j /= 2;
            }

            ans.emplace_back(oneBitCounter);
        }

        return ans;
    }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<int>& ans) noexcept
{
    if (ans.empty())
    {
        os << "EMPTY";

        return os;
    }

    auto begin = ans.cbegin();
    auto end = ans.cend();

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
    std::cout << Solution().countBits(2) << '\n';
    std::cout << Solution().countBits(5) << '\n';

    return 0;
}
