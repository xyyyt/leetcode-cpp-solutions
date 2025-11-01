#include <vector>
#include <queue>
#include <cassert>
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
    assert(Solution().minMeetingRooms({{0, 40}, {5, 10}, {15, 20}}) == 2);
    assert(Solution().minMeetingRooms({{4, 9}}) == 1);
    assert(Solution().minMeetingRooms({{7, 10}, {2, 4}}) == 1);
    assert(Solution().minMeetingRooms({{8, 10}, {7, 9}, {2, 6}, {3, 5}}) == 2);
    assert(Solution().minMeetingRooms({{1, 3}, {3, 5}, {5, 7}}) == 1);
    assert(Solution().minMeetingRooms({{2, 6}, {4, 8}}) == 2);
    assert(Solution().minMeetingRooms({{1, 10}, {2, 9}, {3, 8}}) == 3);
    assert(Solution().minMeetingRooms({{10, 12}, {1, 2}, {4, 6}}) == 1);
    assert(Solution().minMeetingRooms({{1, 4}, {3, 7}, {6, 9}}) == 2);
    assert(Solution().minMeetingRooms({{5, 10}, {5, 10}, {5, 10}}) == 3);
    assert(Solution().minMeetingRooms({{8, 11}}) == 1);
    assert(Solution().minMeetingRooms({{20, 25}, {1, 3}, {5, 7}, {10, 12}}) == 1);
    assert(Solution().minMeetingRooms({{2, 4}, {4, 6}, {6, 9}}) == 1);
    assert(Solution().minMeetingRooms({{2, 4}, {3, 5}}) == 2);
    assert(Solution().minMeetingRooms({{0, 100}, {10, 20}, {30, 40}, {50, 60}}) == 2);
    assert(Solution().minMeetingRooms({{1, 2}, {1, 2}, {1, 2}}) == 3);
    assert(Solution().minMeetingRooms({{-10, -1}, {-5, 3}}) == 2);
    assert(Solution().minMeetingRooms({{-20, -10}, {-9, -5}, {-4, -1}}) == 1);
    assert(Solution().minMeetingRooms({{1,4},{2,5},{7,9},{3,6},{8,10},{9,11}}) == 3);

    return 0;
}
