#include <vector>
#include <cassert>

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
    assert(Solution().fourSumCount({1, 2}, {-2, -1}, {-1, 2}, {0, 2}) == 2);
    assert(Solution().fourSumCount({0}, {0}, {0}, {0}) == 1);
    assert(Solution().fourSumCount({}, {}, {}, {}) == 0);
    assert(Solution().fourSumCount({1}, {-1}, {0}, {0}) == 1);
    assert(Solution().fourSumCount({0, 0}, {0}, {0}, {0}) == 2);
    assert(Solution().fourSumCount({1}, {1}, {1}, {1}) == 0);
    assert(Solution().fourSumCount({1, 2}, {-2, -1}, {-1, 2}, {0, 2}) == 3);
    assert(Solution().fourSumCount({2, -1}, {-2, 1}, {0, 1}, {-1, 0}) == 4);

    return 0;
}
