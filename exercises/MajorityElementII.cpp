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

        std::unordered_map<int, int> numCounters;

        numCounters.reserve(nums.size());

        for (auto num : nums)
        {
            ++numCounters[num];
        }

        std::vector<int> majorities;

        majorities.reserve(numCounters.size());

        for (auto [num, counter] : numCounters)
        {
            if (counter > nums.size() / 3)
            {
                majorities.emplace_back(num);
            }
        }

        return majorities;
    }
};

inline void check(
    const std::vector<int>& majorities,
    std::vector<int> expected)
{
    assert(majorities == expected);
}

int main()
{
    check(Solution().majorityElement({3, 2, 3}), {3});
    check(Solution().majorityElement({1}), {1});
    check(Solution().majorityElement({1, 2}), {2, 1});
    check(Solution().majorityElement({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}), {});
    check(Solution().majorityElement({10, 10, 10, 20, 20, 20, 30, 30, 30, 10}), {10});
    check(Solution().majorityElement({100, 200, 100, 100, 300, 100, 400, 100, 500}), {100});
    check(Solution().majorityElement({}), {});
    check(Solution().majorityElement({0, 0, 0, 0}), {0});

    return 0;
}
