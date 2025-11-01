#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <cassert>

class Solution
{
public :
    int singleNumber(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return std::numeric_limits<int>::min();
        }

        std::unordered_map<int, int> numCounters;

        numCounters.reserve(nums.size());

        for (auto num : nums)
        {
            ++numCounters[num];
        }

        std::priority_queue<std::pair<int, int>> queue;

        for (auto [num, counter] : numCounters)
        {
            queue.emplace(counter, num);

            if (queue.size() > 1)
            {
                queue.pop();
            }
        }

        return (queue.top().first == 1) ?
            queue.top().second : std::numeric_limits<int>::min();
    }
};

int main()
{
    assert(Solution().singleNumber({2, 2, 1}) == 1);
    assert(Solution().singleNumber({4, 1, 2, 1, 2}) == 4);
    assert(Solution().singleNumber({1}) == 1);
    assert(Solution().singleNumber({0, 1, 0}) == 1);
    assert(Solution().singleNumber({17, 17, 99}) == 99);
    assert(Solution().singleNumber({5, 3, 5}) == 3);
    assert(Solution().singleNumber({10, 10, 10, 42, 10}) == 42);
    assert(Solution().singleNumber({100, 200, 100}) == 200);
    assert(Solution().singleNumber({8, 7, 8, 7, 42}) == 42);

    return 0;
}
