#include <vector>
#include <unordered_map>
#include <cassert>

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

inline void check(
    const std::vector<int>& majorityElements,
    std::vector<int> expected)
{
    assert(majorityElements == expected);
}

int main()
{
    check(Solution().majorityElement({3, 2, 3}), {3});
    check(Solution().majorityElement({1}), {1});
    check(Solution().majorityElement({1, 2}), {2, 1});

    return 0;
}
