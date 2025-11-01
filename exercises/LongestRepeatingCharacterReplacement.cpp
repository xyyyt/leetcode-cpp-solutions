#include <string>
#include <iostream>

class Solution
{
public :
    int characterReplacement(std::string s, int k)
    {
        if (s.empty())
        {
            return -1;
        }

        // lrc = longest repeating character
        int lrcSubstrLength = getLRCSubstrLength(s);

        if (k < 1)
        {
            return lrcSubstrLength;
        }

        for (int n = 0; n < s.size(); ++n)
        {
            lrcSubstrLength = std::max(
                lrcSubstrLength,
                characterReplacement(
                    s, k, 0, n, 0));
        }

        return lrcSubstrLength;
    }

private :
    [[nodiscard]]
    int characterReplacement(
        std::string& s, int k, int k2, int n, int pos) const
    {
        if (pos >= s.size())
        {
            return 0;
        }

        int lrcSubstrLength = 0;

        for (int n2 = pos; n2 < s.size(); ++n2)
        {
            if (s[n2] == s[n])
            {
                continue;
            }

            char tmp = s[n2];

            s[n2] = s[n];
            lrcSubstrLength = std::max(
                lrcSubstrLength,
                getLRCSubstrLength(s));

            if (k2 + 1 < k)
            {
                lrcSubstrLength = std::max(
                    lrcSubstrLength,
                    characterReplacement(
                        s, k, k2 + 1, n, pos + 1));
            }

            s[n2] = tmp;
        }

        return lrcSubstrLength;
    }

    [[nodiscard]]
    int getLRCSubstrLength(
        const std::string& s) const noexcept
    {
        int lrcSubstrLength = 0;
        int n = 0;

        while (n < s.size())
        {
            int counter = 1;

            if (n + 1 < s.size() && s[n] == s[n + 1])
            {
                int n2 = n + 1;

                while (n2 < s.size() && s[n2] == s[n])
                {
                    ++counter;
                    ++n2;
                }

                n = n2;
            }
            else
            {
                ++n;
            }

            lrcSubstrLength = std::max(
                lrcSubstrLength, counter);
        }

        return lrcSubstrLength;
    }
};

int main()
{
    std::cout << Solution().characterReplacement("ABAB", 2) << '\n';
    std::cout << Solution().characterReplacement("AABABBA", 1) << '\n';
    std::cout << Solution().characterReplacement("ABBBBABBA", 0) << '\n';

    return 0;
}
