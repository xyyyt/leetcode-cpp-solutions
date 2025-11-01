#include <vector>
#include <algorithm>
#include <iostream>

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
    std::cout << std::boolalpha;
    std::cout << Solution().canAttendMeetings(
        {{0, 30}, {5, 10}, {15, 20}})
              << '\n';
    std::cout << Solution().canAttendMeetings(
        {{5, 8}, {9, 15}})
              << '\n';
    std::cout << Solution().canAttendMeetings(
        {{6, 12}, {1, 4}, {5, 6}})
              << '\n';
    std::cout << Solution().canAttendMeetings(
        {{14, 17}, {17, 20}})
              << '\n';
    std::cout << Solution().canAttendMeetings(
        {{17, 20}, {14, 17}, {5, 9}, {9, 14}})
              << '\n';

    return 0;
}
