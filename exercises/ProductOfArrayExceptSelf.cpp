#include <vector>
#include <iostream>

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

std::ostream& operator<<(
    std::ostream& os, const std::vector<int>& answer) noexcept
{
    if (answer.empty())
    {
        os << "EMPTY";

        return os;
    }

    auto begin = answer.cbegin();
    auto end = answer.cend();

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
    std::cout << Solution().productExceptSelf({1, 2, 3, 4}) << '\n';
    std::cout << Solution().productExceptSelf({-1, 1, 0, -3, 3}) << '\n';
    std::cout << Solution().productExceptSelf({9}) << '\n';
    std::cout << Solution().productExceptSelf({5, 10}) << '\n';

    return 0;
}
