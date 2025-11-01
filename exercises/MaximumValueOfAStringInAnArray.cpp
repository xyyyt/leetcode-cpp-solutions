#include <vector>
#include <string>
#include <limits>
#include <charconv>
#include <cassert>

class Solution
{
public :
    int maximumValue(std::vector<std::string> strs)
    {
        constexpr int MIN_VALUE = std::numeric_limits<int>::min();

        if (strs.empty())
        {
            return MIN_VALUE;
        }

        int max = MIN_VALUE;

        for (const auto& str : strs)
        {
            const char *data = str.data();
            int value = 0;

            if (auto [ptr, ec] = std::from_chars(
                data, data + str.size(), value);
                !(ec == std::errc{} && ptr == data + str.size()))
            {
                value = str.size();
            }

            max = std::max(max, value);
        }

        return max;
    }
};

int main()
{
    assert(Solution().maximumValue({"alic3", "bob", "3", "4", "0000"})
           == 5);
    assert(Solution().maximumValue({"1", "01", "001", "0001"})
           == 1);
    assert(Solution().maximumValue({"-5", "-0312", "-12"})
           == -5);
    assert(Solution().maximumValue({"3", "-1AbWcd", "-9", "0A"})
           == 7);
    assert(Solution().maximumValue({"abc", "12", "a1b2c3", "999"})
           == 999);
    assert(Solution().maximumValue({"0007", "07", "7"})
           == 7);
    assert(Solution().maximumValue({"a", "bb", "ccc"})
           == 3);
    assert(Solution().maximumValue({"-10", "hello", "world"})
           == 5);
    assert(Solution().maximumValue({"a0b1c2", "xyz9", "123abc"})
           == 6);
    assert(Solution().maximumValue({"000"})
           == 0);
    assert(Solution().maximumValue({"-1", "-22", "-333"})
           == -1);
    assert(Solution().maximumValue({"0", "00", "abc123", "9z", "z9"})
           == 6);
    assert(Solution().maximumValue({"X", "YY", "ZZZ"})
           == 3);
    assert(Solution().maximumValue({"-5", "-2", "-100"})
           == -2);
    assert(Solution().maximumValue({"1", "22", "333", "4444"})
           == 4444);

    return 0;
}
