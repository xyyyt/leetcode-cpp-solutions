#include <string>
#include <vector>
#include <cassert>

class Solution
{
public :
    std::string longestCommonPrefix(std::vector<std::string> strs)
    {
        if (strs.size() < 2)
        {
            return "";
        }

        std::string commonPrefix;

        commonPrefix.reserve(strs[0].size());

        for (int n = 0; n < strs[0].size(); ++n)
        {
            int n2 = 1;

            while (n2 < strs.size())
            {
                if (strs[n2][n] != strs[0][n])
                {
                    break;
                }

                ++n2;
            }

            if (n2 < strs.size())
            {
                return commonPrefix;
            }

            commonPrefix.push_back(strs[0][n]);
        }

        return commonPrefix;
    }
};

int main()
{
    assert(Solution().longestCommonPrefix({"flower", "flow", "flight"})
           == "fl");
    assert(Solution().longestCommonPrefix({"dog", "racecar", "car"})
           == "");
    assert(Solution().longestCommonPrefix({""})
           == "");
    assert(Solution().longestCommonPrefix({"interspecies", "interstellar", "interstate"})
           == "inters");
    assert(Solution().longestCommonPrefix({"throne", "throne"})
           == "throne");
    assert(Solution().longestCommonPrefix({"prefix", "preach", "prevent"})
           == "pre");

    return 0;
}
