#include <string>
#include <string_view>
#include <charconv>
#include <iostream>

class Solution
{
public :
    int numDecodings(std::string s)
    {
        return (!s.empty()) ? _numDecodings(s) : 0;
    }

private :
    int _numDecodings(std::string_view s) const
    {
        if (s.empty())
        {
            return 1;
        }
        else if (s[0] == '0')
        {
            return 0;
        }

        int fullDecodingCounter = 0;
        auto decodeAllFrom = [&](size_t offset)
        {
            [[maybe_unused]] int value = 0;

            if (auto [_, ec] = std::from_chars(
                s.data(), s.data() + offset, value);
                ec == std::errc{})
            {
                fullDecodingCounter += _numDecodings(s.substr(offset));
            }
        };

        if (s.size() >= 1)
        {
            decodeAllFrom(1);
        }

        if (s.size() >= 2)
        {
            decodeAllFrom(2);
        }

        return fullDecodingCounter;
    }
};

int main()
{
    std::cout << Solution().numDecodings("12") << '\n';
    std::cout << Solution().numDecodings("226") << '\n';
    std::cout << Solution().numDecodings("06") << '\n';
    std::cout << Solution().numDecodings("11106") << '\n';

    return 0;
}
