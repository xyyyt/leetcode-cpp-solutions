#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>

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
        if (nums.empty())
        {
            return -1;
        }

        std::unordered_map<int, int> numCounterFromSubarrays;

        for (int n = 0; n + k <= nums.size(); ++n)
        {
            for (int n2 = n; n2 < n + k; ++n2)
            {
                ++numCounterFromSubarrays[nums[n2]];
            }
        }

        using PQueue_t = std::priority_queue<
            std::pair<int, int>,
            std::vector<std::pair<int, int>>,
            CounterNumLess>;

        PQueue_t queue;

        for (auto [num, counter] : numCounterFromSubarrays)
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
    std::cout << Solution().largestInteger({3, 9, 2, 1, 7}, 3) << '\n';
    std::cout << Solution().largestInteger({3, 9, 7, 2, 1, 7}, 4) << '\n';
    std::cout << Solution().largestInteger({0, 0}, 1) << '\n';

    return 0;
}
