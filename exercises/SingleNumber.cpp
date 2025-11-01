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

        std::unordered_map<int, int> numCounter;

        numCounter.reserve(nums.size());

        for (auto num : nums)
        {
            ++numCounter[num];
        }

        std::priority_queue<std::pair<int, int>> queue;

        for (auto [num, counter] : numCounter)
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

    return 0;
}
