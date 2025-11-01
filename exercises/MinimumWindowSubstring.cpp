#include <string>
#include <string_view>
#include <unordered_map>
#include <iostream>

class Solution
{
public :
    std::string minWindow(std::string s, std::string t)
    {
        if (s.empty() || t.empty())
        {
            return {};
        }

        std::string_view sv = s;
        std::string_view minWindowSubstr;
        CharCounter_t tCharCounter = getCharCounter(t);
        CharCounter_t windowCharCounter;
        int windowStart = 0;
        int windowEnd = 0;

        while (windowEnd < sv.size())
        {
            /* increase window by moving right pointer until all
               't' parameter characters are covered */
            {
                std::string_view minWindowSubstr2;

                while (windowEnd < sv.size()
                       && minWindowSubstr2.empty())
                {
                    ++windowCharCounter[sv[windowEnd]];

                    if (tCharCounter.find(sv[windowEnd]) != tCharCounter.cend()
                        && windowCharCounterMeetsRequirements(
                            tCharCounter, windowCharCounter))
                    {
                        minWindowSubstr2 = sv.substr(
                            windowStart, (windowEnd - windowStart) + 1);
                    }

                    ++windowEnd;
                }

                if (minWindowSubstr.empty()
                    || (!minWindowSubstr2.empty()
                        && minWindowSubstr2.size() < minWindowSubstr.size()))
                {
                    minWindowSubstr = minWindowSubstr2;
                }
            }

            /* decrease window by moving left pointer until all
               't' parameter characters aren't covered anymore */
            {
                std::string_view minWindowSubstr2;

                while (windowStart < windowEnd
                       && windowCharCounterMeetsRequirements(
                           tCharCounter, windowCharCounter))
                {
                    if (tCharCounter.find(sv[windowStart]) != tCharCounter.cend())
                    {
                        minWindowSubstr2 = sv.substr(
                            windowStart, windowEnd - windowStart);
                    }

                    --windowCharCounter[sv[windowStart]];
                    ++windowStart;
                }

                if (minWindowSubstr.empty()
                    || (!minWindowSubstr2.empty()
                        && minWindowSubstr2.size() < minWindowSubstr.size()))
                {
                    minWindowSubstr = minWindowSubstr2;
                }
            }
        }

        return std::string(minWindowSubstr.data(), minWindowSubstr.size());
    }

private :
    using CharCounter_t = std::unordered_map<char, int>;

    [[nodiscard]]
    inline CharCounter_t getCharCounter(
        const std::string& str) const
    {
        CharCounter_t charCounter;

        charCounter.reserve(str.size());

        for (auto c : str)
        {
            ++charCounter[c];
        }

        return charCounter;
    }

    [[nodiscard]]
    bool windowCharCounterMeetsRequirements(
        const CharCounter_t& tCharCounter,
        const CharCounter_t& windowCharCounter) const
    {
        for (auto [c, counter] : tCharCounter)
        {
            auto it = windowCharCounter.find(c);

            if (it == windowCharCounter.cend()
                || it->second < counter)
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    std::cout << "\"" << Solution().minWindow(
        "ADOBECODEBANC", "ABC")
              << "\"\n";
    std::cout << "\"" << Solution().minWindow(
        "a", "a")
              << "\"\n";
    std::cout << "\"" << Solution().minWindow(
        "A", "AA")
              << "\"\n";
    std::cout << "\"" << Solution().minWindow(
        "aaaaaaaaaaaabbbbbcdd", "abcdd")
              << "\"\n";
    std::cout << "\"" << Solution().minWindow(
        "caccaacaaaabbcaccaccc", "acccacbccc")
              << "\"\n";
    std::cout << "\"" << Solution().minWindow(
        "babb", "baba")
              << "\"\n";
    std::cout << "\"" << Solution().minWindow(
        "CCBBAA", "ABC")
              << "\"\n";
    std::cout << "\"" << Solution().minWindow(
        "BDANCCABPAETC", "ABC")
              << "\"\n";
    std::cout << "\"" << Solution().minWindow(
        "ZBcDAbcc", "Abc")
              << "\"\n";

    return 0;
}
