#include <string>
#include <algorithm>
#include <cctype>
#include <cassert>

class Solution
{
public :
    bool isPalindrome(std::string s)
    {
        s.erase(std::remove_if(s.begin(),
                               s.end(),
                               [](char c) noexcept -> bool
                               {
                                   return !std::isalnum(c);
                               }),
                s.end());

        if (s.empty())
        {
            return true;
        }

        std::transform(s.begin(), s.end(), s.begin(), ::tolower);

        return std::equal(
            s.cbegin(), s.cbegin() + (s.size() / 2), s.crbegin());
    }
};

int main()
{
    assert(Solution().isPalindrome("A man, a plan, a canal: Panama"));
    assert(!Solution().isPalindrome("race a car"));
    assert(Solution().isPalindrome(" "));

    return 0;
}
