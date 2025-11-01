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
            return -1;
        }

        std::unordered_set<int> numsSet(nums.cbegin(), nums.cend());
        int longestConsecSeqLength = 0;

        for (auto num : nums)
        {
            if (numsSet.find(num) != numsSet.cend()
                && numsSet.find(num - 1) == numsSet.cend())
            {
                int consecSeqLength = 0;
                int val = num;

                do
                {
                    ++consecSeqLength;
                    numsSet.erase(val++);
                }
                while (numsSet.find(val) != numsSet.cend());

                longestConsecSeqLength = std::max(
                    longestConsecSeqLength, consecSeqLength);
            }
        }

        return longestConsecSeqLength;
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

    return 0;
}
