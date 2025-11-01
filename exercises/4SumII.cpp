#include <vector>
#include <iostream>

class Solution
{
public :
    int fourSumCount(std::vector<int> nums1,
                     std::vector<int> nums2,
                     std::vector<int> nums3,
                     std::vector<int> nums4)
    {
        if (nums1.empty()
            || nums2.empty()
            || nums3.empty()
            || nums4.empty())
        {
            return 0;
        }

        int count = 0;

        for (int i = 0; i < nums1.size(); ++i)
        {
            for (int j = 0; j < nums2.size(); ++j)
            {
                for (int k = 0; k < nums3.size(); ++k)
                {
                    for (int l = 0; l < nums4.size(); ++l)
                    {
                        constexpr int TARGET = 0;

                        if (nums1[i] + nums2[j] + nums3[k] + nums4[l]
                            == TARGET)
                        {
                            ++count;
                        }
                    }
                }
            }
        }

        return count;
    }
};

int main()
{
    std::cout << Solution().fourSumCount({1, 2}, {-2, -1}, {-1, 2}, {0, 2}) << '\n';
    std::cout << Solution().fourSumCount({0}, {0}, {0}, {0}) << '\n';

    return 0;
}
