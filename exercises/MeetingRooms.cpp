#include <vector>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    bool canAttendMeetings(std::vector<std::vector<int>> intervals)
    {
        if (intervals.empty())
        {
            return false;
        }

        std::sort(intervals.begin(), intervals.end());

        for (int n = 0; n < intervals.size() - 1; ++n)
        {
            const auto& interval = intervals[n];
            const auto& interval2 = intervals[n + 1];

            if ((interval2[0] >= interval[0]
                 && interval2[0] < interval[1])
                || (interval2[1] > interval[0]
                    && interval2[1] <= interval[1]))
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    assert(!Solution().canAttendMeetings(
        {{0, 30}, {5, 10}, {15, 20}}));
    assert(Solution().canAttendMeetings(
        {{5, 8}, {9, 15}}));
    assert(Solution().canAttendMeetings(
        {{6, 12}, {1, 4}, {5, 6}}));
    assert(Solution().canAttendMeetings(
        {{14, 17}, {17, 20}}));
    assert(Solution().canAttendMeetings(
        {{17, 20}, {14, 17}, {5, 9}, {9, 14}}));
    assert(Solution().canAttendMeetings(
        {{1, 3}, {3, 5}, {5, 8}}));
    assert(!Solution().canAttendMeetings(
        {{2, 6}, {4, 7}}));
    assert(!Solution().canAttendMeetings(
        {{1, 10}, {3, 5}, {6, 9}}));
    assert(Solution().canAttendMeetings(
        {{10, 12}, {1, 2}, {3, 5}, {6, 9}}));
    assert(!Solution().canAttendMeetings(
        {{1, 4}, {3, 6}, {5, 8}}));
    assert(!Solution().canAttendMeetings(
        {{4, 9}, {4, 9}}));
    assert(Solution().canAttendMeetings(
        {{7, 11}}));
    assert(Solution().canAttendMeetings(
        {{20, 25}, {1, 3}, {5, 7}, {10, 12}}));
    assert(Solution().canAttendMeetings(
        {{2, 4}, {4, 9}, {9, 12}}));
    assert(!Solution().canAttendMeetings(
        {{2, 4}, {3, 5}}));
    assert(!Solution().canAttendMeetings(
        {{0, 100}, {10, 20}, {30, 40}, {50, 60}}));
    assert(!Solution().canAttendMeetings(
        {{1, 2}, {2, 3}, {2, 2}}));
    assert(!Solution().canAttendMeetings(
        {{-10, -1}, {-5, 3}}));
    assert(Solution().canAttendMeetings(
        {{-20, -10}, {-9, -5}, {-4, -1}}));
    assert(Solution().canAttendMeetings(
        {{1,2},{3,4},{5,6},{7,8},{9,10},{11,12},{13,14}}));

    return 0;
}
