#include <vector>
#include <unordered_set>
#include <cassert>

class Solution
{
public :
    int longestConsecutive(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return 0;
        }

        std::unordered_set<int> numsSet(nums.cbegin(), nums.cend());

        // lcs = longest consecutive sequence
        int lcsLength = 0;

        for (auto num : nums)
        {
            if (numsSet.find(num) != numsSet.cend()
                && numsSet.find(num - 1) == numsSet.cend())
            {
                // cs = consecutive sequence
                int csLength = 0;

                int val = num;

                do
                {
                    ++csLength;
                    numsSet.erase(val++);
                }
                while (numsSet.find(val) != numsSet.cend());

                lcsLength = std::max(lcsLength, csLength);
            }
        }

        return lcsLength;
    }
};

int main()
{
    assert(Solution().longestConsecutive(
        {100, 4, 200, 1, 3, 2})
           == 4);
    assert(Solution().longestConsecutive(
        {0, 3, 7, 2, 5, 8, 4, 6, 0, 1})
           == 9);
    assert(Solution().longestConsecutive(
        {1, 0, 1, 2})
           == 3);
    assert(Solution().longestConsecutive(
        {100, 4, 200, 1, 3, 2})
           == 4);
    assert(Solution().longestConsecutive(
        {1, 2, 3, 4, 5})
           == 5);
    assert(Solution().longestConsecutive(
        {5, 4, 3, 2, 1})
           == 5);
    assert(Solution().longestConsecutive(
        {10, 30, 50})
           == 1);
    assert(Solution().longestConsecutive(
        {-1, -2, -3, 10})
           == 3);
    assert(Solution().longestConsecutive(
        {42})
           == 1);
    assert(Solution().longestConsecutive(
        {})
           == 0);
    assert(Solution().longestConsecutive(
        {1000, -1, 0, 1, 2, 999})
           == 4);

    return 0;
}
