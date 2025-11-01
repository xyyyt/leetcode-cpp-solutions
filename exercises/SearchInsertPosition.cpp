#include <vector>
#include <cassert>

class Solution
{
public :
    int searchInsert(std::vector<int> nums, int target)
    {
        int n = 0;

        while (n < nums.size())
        {
            if (nums[n] >= target)
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
    assert(Solution().searchInsert({1, 3, 5, 6}, 5) == 2);
    assert(Solution().searchInsert({1, 3, 5, 6}, 2) == 1);
    assert(Solution().searchInsert({1, 3, 5, 6}, 7) == 4);

    return 0;
}
