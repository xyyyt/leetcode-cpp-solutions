#include <string>
#include <cassert>

class Solution
{
public :
    int lengthOfLastWord(std::string s)
    {
        if (s.empty())
        {
            return 0;
        }

        size_t pos = s.find_last_not_of(' ');

        if (pos == std::string::npos)
        {
            return 0;
        }

        int length = 0;

        do
        {
            ++length;

            if (pos == 0)
            {
                break;
            }

            --pos;
        }
        while (s[pos] != ' ');

        return length;
    }
};

int main()
{
    assert(Solution().lengthOfLastWord("Hello World") == 5);
    assert(Solution().lengthOfLastWord("   fly me   to   the moon  ") == 4);
    assert(Solution().lengthOfLastWord("luffy is still joyboy") == 6);
    assert(Solution().lengthOfLastWord("a          ") == 1);
    assert(Solution().lengthOfLastWord("      ") == 0);

    return 0;
}
