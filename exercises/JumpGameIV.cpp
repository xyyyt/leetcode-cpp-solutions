#include <vector>
#include <unordered_set>
#include <limits>
#include <iostream>

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
        const std::unordered_set<int>& indexAlreadyUsed,
        int jumpCounter,
        int pos) const
    {
        if (pos < 0
            || pos >= nums.size()
            || indexAlreadyUsed.find(pos) != indexAlreadyUsed.cend())
        {
            return -1;
        }
        else if (pos == nums.size() - 1)
        {
            return jumpCounter;
        }

        std::unordered_set<int> indexAlreadyUsed2 = indexAlreadyUsed;

        indexAlreadyUsed2.emplace(pos);

        int jumpCounterMin = std::numeric_limits<int>::max();

        if (int res = minJumps(
                nums, indexAlreadyUsed2, jumpCounter + 1, pos + 1);
            res != -1)
        {
            jumpCounterMin = std::min(jumpCounterMin, res);
        }

        if (int res = minJumps(
                nums, indexAlreadyUsed2, jumpCounter + 1, pos - 1);
            res != -1)
        {
            jumpCounterMin = std::min(jumpCounterMin, res);
        }

        for (int n = 0; n < nums.size(); ++n)
        {
            if (nums[n] == nums[pos] && n != pos)
            {
                if (int res = minJumps(
                        nums, indexAlreadyUsed2, jumpCounter + 1, n);
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
    std::cout << Solution().minJumps(
        {100, -23, -23, 404, 100, 23, 23, 23, 3, 404})
              << '\n';
    std::cout << Solution().minJumps(
        {7})
              << '\n';
    std::cout << Solution().minJumps(
        {7, 6, 9, 6, 9, 6, 9, 7})
              << '\n';

    return 0;
}
