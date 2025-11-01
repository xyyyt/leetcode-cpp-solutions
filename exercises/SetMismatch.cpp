#include <vector>
#include <algorithm>
#include <iostream>

class Solution
{
public :
    std::vector<int> findErrorNums(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return {};
        }

        std::sort(nums.begin(), nums.end());

        int n = 0;

        while (n < nums.size() - 1)
        {
            if (nums[n + 1] != nums[n] + 1)
            {
                break;
            }

            ++n;
        }

        return {nums[n], nums[n] + 1};
    }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<int>& errorNums) noexcept
{
    if (errorNums.empty())
    {
        os << "EMPTY";

        return os;
    }

    auto begin = errorNums.cbegin();
    auto end = errorNums.cend();

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
    std::cout << Solution().findErrorNums({1, 2, 2, 4}) << '\n';
    std::cout << Solution().findErrorNums({1, 1}) << '\n';

    return 0;
}
