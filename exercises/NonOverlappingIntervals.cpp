#include <vector>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    int eraseOverlapIntervals(
        std::vector<std::vector<int>> intervals)
    {
        if (intervals.size() < 2)
        {
            return 0;
        }

        std::sort(intervals.begin(), intervals.end());

        const auto *interval = &intervals[0];
        int minRFNO = 0; // RFNO = Removal For Non Overlapping

        for (int n = 1; n < intervals.size(); ++n)
        {
            if (intervals[n][0] < (*interval)[1])
            {
                ++minRFNO;
            }
            else
            {
                interval = &intervals[n];
            }
        }

        return minRFNO;
    }
};

int main()
{
    assert(Solution().eraseOverlapIntervals(
        {{1, 2}, {2, 3}, {3, 4}, {1, 3}})
           == 1);
    assert(Solution().eraseOverlapIntervals(
        {{1, 2}, {1, 2}, {1, 2}})
           == 2);
    assert(Solution().eraseOverlapIntervals(
        {{1, 2}, {2, 3}})
           == 0);
    assert(Solution().eraseOverlapIntervals(
        {{1, 2}, {5, 10}, {18, 35}, {40, 45}})
           == 0);

    return 0;
}
