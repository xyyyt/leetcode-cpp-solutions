#include <vector>
#include <unordered_map>
#include <queue>
#include <cassert>

struct CounterNumLess
{
    [[nodiscard]]
    bool operator()(
        const std::pair<int, int>& lhs,
        const std::pair<int, int>& rhs) const noexcept
    {
        return (lhs.first == rhs.first) ?
            lhs.second >= rhs.second : lhs.first < rhs.first;
    }
};

class Solution
{
public :
    int largestInteger(std::vector<int> nums, int k)
    {
        if (nums.empty() || k <= 0)
        {
            return -1;
        }

        std::unordered_map<int, int> numCountersFromSubarrays;

        for (int n = 0; n + k <= nums.size(); ++n)
        {
            for (int n2 = n; n2 < n + k; ++n2)
            {
                ++numCountersFromSubarrays[nums[n2]];
            }
        }

        using PQueue_t = std::priority_queue<
            std::pair<int, int>,
            std::vector<std::pair<int, int>>,
            CounterNumLess>;

        PQueue_t queue;

        for (auto [num, counter] : numCountersFromSubarrays)
        {
            queue.emplace(counter, num);

            if (queue.size() > 1)
            {
                queue.pop();
            }
        }

        return (queue.top().first == 1) ? queue.top().second : -1;
    }
};

int main()
{
    assert(Solution().largestInteger({3, 9, 2, 1, 7}, 3) == 7);
    assert(Solution().largestInteger({3, 9, 7, 2, 1, 7}, 4) == 3);
    assert(Solution().largestInteger({0, 0}, 1) == -1);
    assert(Solution().largestInteger({1}, 1) == 1);
    assert(Solution().largestInteger({1, 2}, 1) == 2);
    assert(Solution().largestInteger({1, 2}, 2) == 2);
    assert(Solution().largestInteger({1, 2, 3, 4}, 2) == 4);
    assert(Solution().largestInteger({2, 2, 2}, -1) == -1);
    assert(Solution().largestInteger({1, 2, 3, 4, 5, 6}, 3) == 6);
    assert(Solution().largestInteger({10, 20, 30, 40, 50}, 4) == 50);
    assert(Solution().largestInteger({}, 1) == -1);
    assert(Solution().largestInteger({5}, 1) == 5);
    assert(Solution().largestInteger({1, 1, 1, 1}, 2) == -1);
    assert(Solution().largestInteger({100, 200, 300, 400}, 4) == 400);

    return 0;
}
