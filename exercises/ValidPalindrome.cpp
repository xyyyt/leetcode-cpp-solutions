#include <string>
#include <algorithm>
#include <cctype>
#include <cassert>

class Solution
{
public :
    bool isPalindrome(std::string s)
    {
        if (s.empty())
        {
            return true;
        }

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
    assert(Solution().isPalindrome(""));
    assert(Solution().isPalindrome("z"));
    assert(Solution().isPalindrome("!!!"));
    assert(Solution().isPalindrome("1a2a1"));
    assert(Solution().isPalindrome("No lemon, no melon"));
    assert(!Solution().isPalindrome("hello"));
    assert(Solution().isPalindrome("abBA"));
    assert(Solution().isPalindrome("Madam"));
    assert(Solution().isPalindrome("Was it a car or a cat I saw"));

    return 0;
}
