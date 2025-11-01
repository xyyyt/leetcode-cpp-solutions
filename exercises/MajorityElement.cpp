#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>

class Solution
{
public :
    int majorityElement(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return -1;
        }

        std::unordered_map<int, int> numCounter;

        numCounter.reserve(nums.size());

        for (auto num : nums)
        {
            ++numCounter[num];
        }

        using PQueue_t = std::priority_queue<
            std::pair<int, int>,
            std::vector<std::pair<int, int>>,
            std::greater<std::pair<int, int>>>;

        PQueue_t queue;

        for (auto [num, counter] : numCounter)
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
    std::cout << Solution().majorityElement({3, 2, 3}) << '\n';
    std::cout << Solution().majorityElement({2, 2, 1, 1, 2, 2, 2}) << '\n';

    return 0;
}
