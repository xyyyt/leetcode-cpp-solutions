#include <vector>
#include <unordered_set>
#include <limits>
#include <cassert>

class Solution
{
public :
    int minJumps(std::vector<int> nums)
    {
        return minJumps(nums, {}, 0, 0);
    }

private :
    [[nodiscard]]
    int minJumps(
        const std::vector<int>& nums,
        const std::unordered_set<int>& seenIndices,
        int jumpCounter,
        int pos) const
    {
        if (pos < 0
            || pos >= nums.size()
            || seenIndices.find(pos) != seenIndices.cend())
        {
            return -1;
        }
        else if (pos == nums.size() - 1)
        {
            return jumpCounter;
        }

        auto seenIndices2 = seenIndices;

        seenIndices2.emplace(pos);

        int jumpCounterMin = std::numeric_limits<int>::max();

        if (int res = minJumps(
                nums, seenIndices2, jumpCounter + 1, pos + 1);
            res != -1)
        {
            jumpCounterMin = std::min(jumpCounterMin, res);
        }

        if (int res = minJumps(
                nums, seenIndices2, jumpCounter + 1, pos - 1);
            res != -1)
        {
            jumpCounterMin = std::min(jumpCounterMin, res);
        }

        for (int n = 0; n < nums.size(); ++n)
        {
            if (nums[n] == nums[pos] && n != pos)
            {
                if (int res = minJumps(
                        nums, seenIndices2, jumpCounter + 1, n);
                    res != -1)
                {
                    jumpCounterMin = std::min(jumpCounterMin, res);
                }
            }
        }

        return jumpCounterMin;
    }
};

int main()
{
    assert(Solution().minJumps({100, -23, -23, 404, 100, 23, 23, 23, 3, 404}) == 3);
    assert(Solution().minJumps({7}) == 0);
    assert(Solution().minJumps({7, 6, 9, 6, 9, 6, 9, 7}) == 1);
    assert(Solution().minJumps({0}) == 0);
    assert(Solution().minJumps({7, 7}) == 1);
    assert(Solution().minJumps({6, 1, 9}) == 2);

    return 0;
}
