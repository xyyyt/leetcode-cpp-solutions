#include <vector>
#include <algorithm>
#include <iostream>

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

std::ostream& operator<<(
    std::ostream& os, const std::vector<int>& nums) noexcept
{
    if (nums.empty())
    {
        os << "EMPTY";

        return os;
    }

    auto begin = nums.cbegin();
    auto end = nums.cend();

    os << *begin;
    ++begin;

    while (begin != end)
    {
        os << ", " << *begin;
        ++begin;
    }

    return os;
}

int main()
{
    {
        std::vector<int> nums1{1, 2, 3, 0, 0, 0};
        std::vector<int> nums2{2, 5, 6};

        Solution().merge(nums1, 3, nums2, nums2.size());
        std::cout << nums1 << '\n';
    }

    {
        std::vector<int> nums1{1};
        std::vector<int> nums2;

        Solution().merge(nums1, 1, nums2, nums2.size());
        std::cout << nums1 << '\n';
    }

    {
        std::vector<int> nums1{0};
        std::vector<int> nums2{1};

        Solution().merge(nums1, 0, nums2, nums2.size());
        std::cout << nums1 << '\n';
    }

    return 0;
}
