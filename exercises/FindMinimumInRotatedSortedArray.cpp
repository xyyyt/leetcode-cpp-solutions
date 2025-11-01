#include <vector>
#include <limits>
#include <cassert>

class Solution
{
public :
    int findMin(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return std::numeric_limits<int>::min();
        }

        int low = 0;
        int high = nums.size() - 1;

        while (low < high)
        {
            if (nums[low] < nums[high])
            {
                break;
            }

            int mid = (low + high) / 2;

            if (nums[mid] > nums[high])
            {
                low = mid + 1;
            }
            else
            {
                high = mid;
            }
        }

        return nums[low];
    }
};

int main()
{
    assert(Solution().findMin({3, 4, 5, 1, 2}) == 1);
    assert(Solution().findMin({4, 5, 6, 7, 0, 1, 2}) == 0);
    assert(Solution().findMin({11, 13, 15, 17}) == 11);
    assert(Solution().findMin({-1, -5, -4, -3, -2}) == -5);
    assert(Solution().findMin({2, 3, 4, 5, 1}) == 1);
    assert(Solution().findMin({5, 1, 2, 3, 4}) == 1);
    assert(Solution().findMin({1, 2, 3, 4, 5}) == 1);
    assert(Solution().findMin({7, 8, 9, 1, 2, 3, 4, 5, 6}) == 1);
    assert(Solution().findMin({6, 7, 1, 2, 3, 4, 5}) == 1);
    assert(Solution().findMin({10, 20, 30, -10, 0}) == -10);
    assert(Solution().findMin({100, 200, 300, 400, 50}) == 50);
    assert(Solution().findMin({9, 1, 2, 3, 4, 5, 6, 7, 8}) == 1);
    assert(Solution().findMin({-3, -2, -1, -10, -9}) == -10);
    assert(Solution().findMin({50, -100, -50, -25}) == -100);
    assert(Solution().findMin({2}) == 2);
    assert(Solution().findMin({9, 0}) == 0);
    assert(Solution().findMin({0, 9}) == 0);

    return 0;
}
