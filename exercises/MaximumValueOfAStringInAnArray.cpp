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

    return 0;
}
