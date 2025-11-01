#include <vector>
#include <cassert>

class Solution
{
public :
    std::vector<int> productExceptSelf(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return {};
        }
        else if (nums.size() < 2)
        {
            return {nums[0]};
        }

        std::vector<int> answer(nums.size());

        productExceptSelf(nums, answer, 0);

        return answer;
    }

private :
    void productExceptSelf(
        std::vector<int>& nums, std::vector<int>& answer, int pos) const
    {
        if (pos >= nums.size())
        {
            return;
        }

        if (pos == 0)
        {
            answer[pos] = nums[pos];
        }
        else
        {
            answer[pos] = answer[pos - 1] * nums[pos];
        }

        productExceptSelf(nums, answer, pos + 1);

        if (pos == nums.size() - 1)
        {
            answer[pos] = answer[pos - 1];
        }
        else if (pos == 0)
        {
            answer[pos] = nums[pos + 1];
        }
        else
        {
            answer[pos] = nums[pos + 1] * answer[pos - 1];
            nums[pos] *= nums[pos + 1];
        }
    }
};

inline void check(
    const std::vector<int>& answer, std::vector<int> expected)
{
    assert(answer == expected);
}

int main()
{
    check(Solution().productExceptSelf({1, 2, 3, 4}),
          {24, 12, 8, 6});
    check(Solution().productExceptSelf({-1, 1, 0, -3, 3}),
          {0, 0, 9, 0, 0});
    check(Solution().productExceptSelf({9}),
          {9});
    check(Solution().productExceptSelf({5, 10}),
          {10, 5});
    check(Solution().productExceptSelf({1, 2, 0, 4}),
          {0, 0, 8, 0});
    check(Solution().productExceptSelf({0, 2, 0, 4}),
          {0, 0, 0, 0});
    check(Solution().productExceptSelf({-1, 2, -3, 4}),
          {-24, 12, -8, 6});
    check(Solution().productExceptSelf({-1, -2, -3, -4}),
          {-24, -12, -8, -6});
    check(Solution().productExceptSelf({3, 4}),
          {4, 3});
    check(Solution().productExceptSelf({100, 200, 300}),
          {60000, 30000, 20000});
    check(Solution().productExceptSelf({1, -1, 1, -1}),
          {1, -1, 1, -1});
    check(Solution().productExceptSelf({2, 3, 5, 7, 11}),
          {1155, 770, 462, 330, 210});

    return 0;
}
