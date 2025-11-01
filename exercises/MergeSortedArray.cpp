#include <vector>
#include <cassert>

class Solution
{
public :
    void merge(
        std::vector<int>& nums1, int m, std::vector<int>& nums2, int n)
    {
        if (nums1.empty())
        {
            return;
        }

        int nums1_rIndex = m - 1;
        int nums2_rIndex = n - 1;
        int rIndex = nums1.size() - 1;

        while (nums1_rIndex >= 0 && nums2_rIndex >= 0)
        {
            nums1[rIndex--] = (nums1[nums1_rIndex] < nums2[nums2_rIndex]) ?
                nums2[nums2_rIndex--] : nums1[nums1_rIndex--];
        }

        while (nums2_rIndex >= 0)
        {
            nums1[rIndex--] = nums2[nums2_rIndex--];
        }
    }
};

inline void check(
    const std::vector<int>& nums,
    std::vector<int> expected)
{
    assert(nums == expected);
}

int main()
{
    {
        std::vector<int> nums1{1, 2, 3, 0, 0, 0};
        std::vector<int> nums2{2, 5, 6};

        Solution().merge(nums1, 3, nums2, 3);
        check(nums1, {1, 2, 2, 3, 5, 6});
    }

    {
        std::vector<int> nums1{1};
        std::vector<int> nums2;

        Solution().merge(nums1, 1, nums2, 0);
        check(nums1, {1});
    }

    {
        std::vector<int> nums1{0};
        std::vector<int> nums2{1};

        Solution().merge(nums1, 0, nums2, 1);
        check(nums1, {1});
    }

    {
        std::vector<int> nums1{4, 5, 6, 0, 0, 0};
        std::vector<int> nums2{1, 2, 3};

        Solution().merge(nums1, 3, nums2, 3);
        check(nums1, {1, 2, 3, 4, 5, 6});
    }

    {
        std::vector<int> nums1{1, 2, 3};
        std::vector<int> nums2;

        Solution().merge(nums1, 3, nums2, 0);
        check(nums1, {1, 2, 3});
    }

    {
        std::vector<int> nums1{1, 2, 3, 0, 0, 0};
        std::vector<int> nums2{1, 2, 3};

        Solution().merge(nums1, 3, nums2, 3);
        check(nums1, {1, 1, 2, 2, 3, 3});
    }

    {
        std::vector<int> nums1{10, 20, 30, 0, 0, 0};
        std::vector<int> nums2{1, 2, 3};

        Solution().merge(nums1, 3, nums2, 3);
        check(nums1, {1, 2, 3, 10, 20, 30});
    }

    return 0;
}
