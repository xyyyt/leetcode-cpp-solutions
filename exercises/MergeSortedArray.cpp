#include <vector>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    void merge(
        std::vector<int>& nums1, int m, std::vector<int>& nums2, int n)
    {
        for (int i = 0, j = 0; i < nums1.size() && j < n; ++i, ++j)
        {
            nums1[i + m] = nums2[j];
        }

        std::sort(nums1.begin(), nums1.end());
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

        Solution().merge(nums1, 3, nums2, nums2.size());
        check(nums1, {1, 2, 2, 3, 5, 6});
    }

    {
        std::vector<int> nums1{1};
        std::vector<int> nums2;

        Solution().merge(nums1, 1, nums2, nums2.size());
        check(nums1, {1});
    }

    {
        std::vector<int> nums1{0};
        std::vector<int> nums2{1};

        Solution().merge(nums1, 0, nums2, nums2.size());
        check(nums1, {1});
    }

    return 0;
}
