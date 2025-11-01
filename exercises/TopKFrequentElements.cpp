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
        int n = pQueue.size() - 1;

        mostFrequentElements.resize(pQueue.size());

        while (!pQueue.empty())
        {
            mostFrequentElements[n--] = pQueue.top().second;
            pQueue.pop();
        }

        assert(n < 0);

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
          {1, 2});
    check(Solution().topKFrequent({1}, 1),
          {1});
    check(Solution().topKFrequent({4, 4, 4, 5, 5, 6}, 2),
          {4, 5});
    check(Solution().topKFrequent({1, 2, 3, 4, 5}, 3),
          {5, 4, 3});
    check(Solution().topKFrequent({1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, 3),
          {5, 4, 3});
    check(Solution().topKFrequent({10, 10, 10, 20, 20, 30, 40, 40, 40, 40}, 2),
          {40, 10});
    check(Solution().topKFrequent({}, 0),
          {});
    check(Solution().topKFrequent({1, 2}, 2),
          {2, 1});
    check(Solution().topKFrequent({5, 5, 5, 5}, 1),
          {5});
    check(Solution().topKFrequent({1000000, 999999, 1000000}, 1),
          {1000000});

    return 0;
}
