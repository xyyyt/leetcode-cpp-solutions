#include <vector>
#include <queue>
#include <iostream>

class Solution
{
public :
    int minMeetingRooms(std::vector<std::vector<int>> intervals)
    {
        if (intervals.empty())
        {
            return 0;
        }

        using PQueue_t = std::priority_queue<
            std::vector<int>,
            std::vector<std::vector<int>>,
            std::greater<std::vector<int>>>;

        PQueue_t queue;

        for (const auto& interval : intervals)
        {
            queue.emplace(interval);
        }

        int nbDaysRequired = 0;

        while (!queue.empty())
        {
            auto interval = queue.top();

            queue.pop();

            std::queue<std::vector<int>> queue2;

            while (!queue.empty())
            {
                auto interval2 = queue.top();

                queue.pop();

                if ((interval2[0] >= interval[0]
                     && interval2[0] < interval[1])
                    || (interval2[1] > interval[0]
                        && interval2[1] <= interval[1]))
                {
                    queue2.emplace(std::move(interval2));
                }
            }

            while (!queue2.empty())
            {
                queue.emplace(std::move(queue2.front()));
                queue2.pop();
            }

            ++nbDaysRequired;
        }

        return nbDaysRequired;
    }
};

int main()
{
    std::cout << Solution().minMeetingRooms({{0, 40}, {5, 10}, {15, 20}}) << '\n';
    std::cout << Solution().minMeetingRooms({{4, 9}}) << '\n';
    std::cout << Solution().minMeetingRooms({{7, 10}, {2, 4}}) << '\n';
    std::cout << Solution().minMeetingRooms({{8, 10}, {7, 9}, {2, 6}, {3, 5}}) << '\n';

    return 0;
}
