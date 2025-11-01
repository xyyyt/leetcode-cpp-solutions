#include <vector>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    int lengthOfLIS(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return -1;
        }

        int lisLength = 1;

        for (int n = 0; n < nums.size(); ++n)
        {
            for (int n2 = n + 1; n2 < nums.size(); ++n2)
            {
                if (nums[n2] > nums[n])
                {
                    int lisLength2 = 2 + lengthOfLIS(nums, n2, n2 + 1);

                    lisLength = std::max(lisLength, lisLength2);
                }
            }
        }

        return lisLength;
    }

private :
    [[nodiscard]]
    int lengthOfLIS(
        const std::vector<int>& nums, int n, int n2) const
    {
        if (n >= nums.size())
        {
            return 0;
        }

        int lisLength = 0;

        while (n2 < nums.size())
        {
            if (nums[n2] > nums[n])
            {
                int lisLength2 = 1 + lengthOfLIS(nums, n2, n2 + 1);

                lisLength = std::max(lisLength, lisLength2);
            }

            ++n2;
        }

        return lisLength;
    }
};

int main()
{
    assert(Solution().lengthOfLIS({10, 9, 2, 5, 3, 7, 101, 18})
           == 4);
    assert(Solution().lengthOfLIS({0, 1, 0, 3, 2, 3})
           == 4);
    assert(Solution().lengthOfLIS({7, 7, 7, 7, 7, 7, 7})
           == 1);
    assert(Solution().lengthOfLIS({1, 2, 3, 4, 5})
           == 5);
    assert(Solution().lengthOfLIS({5, 4, 3, 2, 1})
           == 1);
    assert(Solution().lengthOfLIS({1, 3, 2, 4, 3, 5})
           == 4);
    assert(Solution().lengthOfLIS({9, 1, 3, 7, 5, 6, 20})
           == 5);
    assert(Solution().lengthOfLIS({2, 2, 2, 3, 4, 4, 5})
           == 4);
    assert(Solution().lengthOfLIS({4, 10, 4, 3, 8, 9})
           == 3);
    assert(Solution().lengthOfLIS({1, 2, 4, 3, 5, 4, 7, 2})
           == 5);

    return 0;
}
