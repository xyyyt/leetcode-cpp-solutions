#include <vector>
#include <cassert>

class Solution
{
public :
    int searchInsert(std::vector<int> nums, int target)
    {
        if (nums.empty())
        {
            return -1;
        }

        int insertPos = 0;
        int low = 0;
        int high = nums.size() - 1;

        while (low <= high)
        {
            int mid = (low + high) / 2;

            if (nums[mid] == target)
            {
                insertPos = mid;
                break;
            }
            else if (nums[mid] < target)
            {
                insertPos = mid + 1;
                low = mid + 1;
            }
            else
            {
                insertPos = mid;
                high = mid - 1;
            }
        }

        return insertPos;
    }
};

int main()
{
    assert(Solution().searchInsert({1, 3, 5, 6}, 5) == 2);
    assert(Solution().searchInsert({1, 3, 5, 6}, 2) == 1);
    assert(Solution().searchInsert({1, 3, 5, 6}, 7) == 4);
    assert(Solution().searchInsert({1, 3, 5}, 12) == 3);
    assert(Solution().searchInsert({1, 3, 5}, 0) == 0);
    assert(Solution().searchInsert({1, 3}, 2) == 1);
    assert(Solution().searchInsert({1, 3}, 3) == 1);
    assert(Solution().searchInsert({1}, 0) == 0);
    assert(Solution().searchInsert({1}, 2) == 1);

    return 0;
}
