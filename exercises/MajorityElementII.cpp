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

        majorityElements.reserve(numCounter.size());

        for (auto [num, counter] : numCounter)
        {
            if (counter > nums.size() / 3)
            {
                majorityElements.emplace_back(num);
            }
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
