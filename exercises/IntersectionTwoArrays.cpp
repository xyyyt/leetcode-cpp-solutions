#include <vector>
#include <unordered_map>
#include <iostream>

class Solution
{
public :
    std::vector<int> intersection(const std::vector<int>& nums1,
                                  const std::vector<int>& nums2)
    {
        std::unordered_map<int, int> numCounter;

        numCounter.reserve(nums1.size());

        for (auto num : nums1)
        {
            numCounter[num] = 0;
        }

        for (auto num : nums2)
        {
            auto it = numCounter.find(num);

            if (it != numCounter.cend())
            {
                ++it->second;
            }
        }

        std::vector<int> nums3;

        nums3.reserve(numCounter.size());

        for (auto [num, counter] : numCounter)
        {
            if (counter > 0)
            {
                nums3.emplace_back(num);
            }
        }

        return nums3;
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
    std::cout << Solution().intersection({1, 2, 2, 1}, {2, 2}) << '\n';
    std::cout << Solution().intersection({4, 9, 5}, {9, 4, 9, 8, 4}) << '\n';;

    return 0;
}
