#include <vector>
#include <unordered_map>
#include <iostream>

class Solution
{
public :
    std::vector<int> majorityElement(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return {};
        }

        std::unordered_map<int, int> numCounter;

        numCounter.reserve(nums.size());

        for (auto num : nums)
        {
            ++numCounter[num];
        }

        std::vector<int> majorityElements;
        auto begin = numCounter.cbegin();
        auto end = numCounter.cend();

        majorityElements.reserve(numCounter.size());

        while (begin != end)
        {
            if (begin->second > nums.size() / 3)
            {
                majorityElements.emplace_back(begin->first);
            }

            ++begin;
        }

        return majorityElements;
    }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<int>& majorityElements) noexcept
{
    if (majorityElements.empty())
    {
        os << "EMPTY";

        return os;
    }

    auto begin = majorityElements.cbegin();
    auto end = majorityElements.cend();

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
    std::cout << Solution().majorityElement({3, 2, 3}) << '\n';
    std::cout << Solution().majorityElement({1}) << '\n';
    std::cout << Solution().majorityElement({1, 2}) << '\n';

    return 0;
}
