#include <vector>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    std::vector<std::vector<int>> merge(
        std::vector<std::vector<int>> intervals)
    {
        if (intervals.empty())
        {
            return {};
        }

        std::sort(intervals.begin(), intervals.end());

        std::vector<std::vector<int>> intervals2;
        std::vector<int> newInterval = intervals[0];

        intervals2.reserve(intervals.size());

        for (int n = 1; n < intervals.size(); ++n)
        {
            const auto& currentInterval = intervals[n];

            if (currentInterval[0] > newInterval[1])
            {
                intervals2.emplace_back(std::move(newInterval));
                newInterval = currentInterval;
            }
            else if (currentInterval[0] == newInterval[1]
                     || (currentInterval[0] < newInterval[0]
                         && currentInterval[1] > newInterval[0])
                     || (currentInterval[0] < newInterval[1]
                         && currentInterval[1] > newInterval[1])
                     || currentInterval[1] == newInterval[0])
            {
                newInterval = mergeIntervals(
                    newInterval, currentInterval);
            }
            else if (currentInterval[1] < newInterval[0])
            {
                intervals2.emplace_back(currentInterval);
            }
        }

        intervals2.emplace_back(std::move(newInterval));

        return intervals2;
    }

private :
    [[nodiscard]]
    inline std::vector<int> mergeIntervals(
        const std::vector<int>& interval,
        const std::vector<int>& interval2) const
    {
        return {std::min(interval[0], interval2[0]),
                std::max(interval[1], interval2[1])};
    }
};

inline void check(
    const std::vector<std::vector<int>>& intervals,
    std::vector<std::vector<int>> expected)
{
    assert(intervals == expected);
}

int main()
{
    check(Solution().merge({{2, 6}, {1, 3}}),
          {{1, 6}});
    check(Solution().merge({{1, 3}, {2, 6}, {8, 10}, {15, 18}}),
          {{1, 6}, {8, 10}, {15, 18}});
    check(Solution().merge({{1, 4}, {4, 5}}),
          {{1, 5}});
    check(Solution().merge({{1, 1}, {2, 2}, {0, 0}, {2, 3}, {1, 3}, {3, 5}, {2, 3}, {3, 5}}),
          {{0, 0}, {1, 5}});
    check(Solution().merge({{8, 10}, {1, 3}, {15, 18}, {2, 6}}),
          {{1, 6}, {8, 10}, {15, 18}});

    return 0;
}
