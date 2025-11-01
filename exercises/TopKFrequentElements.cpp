#include <vector>
#include <unordered_map>
#include <queue>
#include <cassert>

class Solution
{
public :
    std::vector<int> topKFrequent(std::vector<int> nums, int k)
    {
        if (nums.empty() || k <= 0)
        {
            return {};
        }

        std::unordered_map<int, int> numCounters;

        numCounters.reserve(nums.size());

        for (auto num : nums)
        {
            ++numCounters[num];
        }

        using PQueue_t = std::priority_queue<
            std::pair<int, int>,
            std::vector<std::pair<int, int>>,
            std::greater<std::pair<int, int>>>;

        PQueue_t pQueue;

        for (auto [num, counter] : numCounters)
        {
            pQueue.emplace(counter, num);

            if (pQueue.size() > k)
            {
                pQueue.pop();
            }
        }

        std::vector<int> mostFrequentElements;

        mostFrequentElements.reserve(pQueue.size());

        while (!pQueue.empty())
        {
            mostFrequentElements.emplace_back(pQueue.top().second);
            pQueue.pop();
        }

        return mostFrequentElements;
    }
};

inline void check(
    const std::vector<int>& mostFrequentElements,
    std::vector<int> expected)
{
    assert(mostFrequentElements == expected);
}

int main()
{
    check(Solution().topKFrequent({1, 1, 1, 2, 2, 3}, 2),
          {2, 1});
    check(Solution().topKFrequent({1}, 1),
          {1});

    return 0;
}
