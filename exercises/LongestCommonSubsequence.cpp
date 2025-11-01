#include <string>
#include <iostream>

class Solution
{
public :
    int longestCommonSubsequence(
        std::string text1, std::string text2)
    {
        return (!text1.empty() && !text2.empty()) ?
            longestCommonSubsequence(text1, text2, 0, 0) : 0;
    }

private :
    [[nodiscard]]
    int longestCommonSubsequence(
       const std::string& text1,
       const std::string& text2,
       int text1Pos,
       int text2Pos) const
    {
        if (text1Pos >= text1.size()
            || text2Pos >= text2.size())
        {
            return 0;
        }

        // lcs = longest common subsequence
        int lcs = 0;

        for (int n = text2Pos; n < text2.size(); ++n)
        {
            for (int n2 = text1Pos; n2 < text1.size(); ++n2)
            {
                if (text2[n] == text1[n2])
                {
                    lcs = std::max(
                        lcs,
                        1 + longestCommonSubsequence(
                            text1,
                            text2,
                            n2 + 1,
                            n + 1));
                }
            }
        }

        return lcs;
    }
};

int main()
{
    std::cout << Solution().longestCommonSubsequence("abcde", "ace") << '\n';
    std::cout << Solution().longestCommonSubsequence("abc", "abc") << '\n';
    std::cout << Solution().longestCommonSubsequence("abc", "def") << '\n';
    std::cout << Solution().longestCommonSubsequence("abc", "acd") << '\n';
    std::cout << Solution().longestCommonSubsequence("aggtab", "gxtxayb") << '\n';
    std::cout << Solution().longestCommonSubsequence("abc", "cba") << '\n';

    return 0;
}
