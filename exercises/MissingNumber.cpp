#include <vector>
#include <unordered_set>
#include <cassert>

class Solution
{
public :
    int missingNumber(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return -1;
        }

        std::unordered_set<int> numSet;

        numSet.reserve(nums.size());

        for (auto num : nums)
        {
            numSet.emplace(num);
        }

        int n = 0;

        while (n < nums.size())
        {
            if (numSet.find(n) == numSet.cend())
            {
                break;
            }

            ++n;
        }

        return n;
    }
};

int main()
{
    assert(Solution().missingNumber({3, 0, 1}) == 2);
    assert(Solution().missingNumber({0, 1}) == 2);
    assert(Solution().missingNumber({9, 6, 4, 2, 3, 5, 7, 0, 1}) == 8);
    assert(Solution().missingNumber({1, 2, 3}) == 0);
    assert(Solution().missingNumber({0}) == 1);
    assert(Solution().missingNumber({1}) == 0);
    assert(Solution().missingNumber({0, 1, 2, 3, 4, 6, 7, 8, 9, 10}) == 5);
    assert(Solution().missingNumber({0, 1, 2, 3, 4, 5, 6, 7, 8}) == 9);
    assert(Solution().missingNumber({0, 2, 3, 4, 5}) == 1);

    return 0;
}
