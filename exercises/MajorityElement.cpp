#include <vector>
#include <unordered_map>
#include <queue>
#include <cassert>

class Solution
{
public :
    int majorityElement(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return -1;
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

        PQueue_t queue;

        for (auto [num, counter] : numCounters)
        {
            queue.emplace(counter, num);

            if (queue.size() > 1)
            {
                queue.pop();
            }
        }

        return (queue.top().first > nums.size() / 2) ?
            queue.top().second : -1;
    }
};

int main()
{
    assert(Solution().majorityElement({3, 2, 3}) == 3);
    assert(Solution().majorityElement({2, 2, 1, 1, 2, 2, 2}) == 2);
    assert(Solution().majorityElement({1}) == 1);
    assert(Solution().majorityElement({1, 1, 2, 2, 2}) == 2);
    assert(Solution().majorityElement({4, 4, 4, 5, 5}) == 4);
    assert(Solution().majorityElement({6, 7, 6, 6, 8, 6, 9}) == 6);
    assert(Solution().majorityElement({10, 10, 10, 20, 20, 10, 30, 10, 40, 10}) == 10);
    assert(Solution().majorityElement({0, 0, 0, 0}) == 0);
    assert(Solution().majorityElement({-1, -1, -1, 2, 2}) == -1);

    return 0;
}
