#include <vector>
#include <unordered_map>
#include <queue>
#include <cassert>

struct CounterEvenNumGreater
{
    [[nodiscard]]
    bool operator()(
        const std::pair<int, int>& lhs,
        const std::pair<int, int>& rhs) const noexcept
    {
        return (lhs.first == rhs.first) ?
            lhs.second <= rhs.second : lhs.first > rhs.first;
    }
};

class Solution
{
public :
    int mostFrequentEven(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return -1;
        }

        std::unordered_map<int, int> evenNumCounter;

        evenNumCounter.reserve(nums.size());

        for (auto num : nums)
        {
            if (num % 2 == 0)
            {
                ++evenNumCounter[num];
            }
        }

        if (evenNumCounter.empty())
        {
            return -1;
        }

        using PQueue_t = std::priority_queue<
            std::pair<int, int>,
            std::vector<std::pair<int, int>>,
            CounterEvenNumGreater>;

        PQueue_t queue;

        for (auto [evenNum, counter] : evenNumCounter)
        {
            queue.emplace(counter, evenNum);

            if (queue.size() > 1)
            {
                queue.pop();
            }
        }

        return queue.top().second;
    }
};

int main()
{
    assert(Solution().mostFrequentEven({0, 1, 2, 2, 4, 4, 1}) == 2);
    assert(Solution().mostFrequentEven({4, 4, 4, 9, 2, 4}) == 4);
    assert(Solution().mostFrequentEven({29, 47, 21, 41, 13, 37, 25, 7}) == -1);
    assert(Solution().mostFrequentEven({1, 2, 2, 3}) == 2);
    assert(Solution().mostFrequentEven({1, 2}) == 2);
    assert(Solution().mostFrequentEven({3, 3, 2, 2}) == 2);
    assert(Solution().mostFrequentEven({0, 1, 2, 2, 4, 4, 1}) == 2);
    assert(Solution().mostFrequentEven({}) == -1);
    assert(Solution().mostFrequentEven({4, 4, 1, 2, 4, 3, 3, 3}) == 4);
    assert(Solution().mostFrequentEven({6, 6, 6, 1, 2, 3}) == 6);

    return 0;
}
