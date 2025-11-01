#include <vector>
#include <unordered_map>
#include <cassert>

class Solution
{
public :
    std::vector<int> findErrorNums(std::vector<int> nums)
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

        int numOccursTwice = 0;
        int missingNum = 0;

        for (int n = 1; n <= nums.size(); ++n)
        {
            auto it = numCounters.find(n);

            if (it != numCounters.cend())
            {
                if (it->second == 2)
                {
                    numOccursTwice = n;
                }
            }
            else
            {
                missingNum = n;
            }
        }

        return {numOccursTwice, missingNum};
    }
};

inline void check(
    const std::vector<int>& errorNums,
    std::vector<int> expected)
{
    assert(errorNums == expected);
}

int main()
{
    check(Solution().findErrorNums({1, 2, 2, 4}), {2, 3});
    check(Solution().findErrorNums({1, 1}), {1, 2});
    check(Solution().findErrorNums({2, 2, 3, 4, 5}), {2, 1});
    check(Solution().findErrorNums({1, 2, 3, 5, 5}), {5, 4});
    check(Solution().findErrorNums({1, 3, 3, 4, 5}), {3, 2});
    check(Solution().findErrorNums({1, 2, 3, 4, 4}), {4, 5});
    check(Solution().findErrorNums({2, 3, 4, 5, 5}), {5, 1});
    check(Solution().findErrorNums({3, 2, 2}), {2, 1});
    check(Solution().findErrorNums({1, 2, 3, 4, 6, 6}), {6, 5});
    check(Solution().findErrorNums({1, 2, 3, 4, 5, 7, 7, 8, 9, 10}), {7, 6});

    return 0;
}
