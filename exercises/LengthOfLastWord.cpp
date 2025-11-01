#include <string>
#include <iostream>

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
    std::cout << Solution().lengthOfLastWord("Hello World") << '\n';
    std::cout << Solution().lengthOfLastWord("   fly me   to   the moon  ") << '\n';
    std::cout << Solution().lengthOfLastWord("luffy is still joyboy") << '\n';
    std::cout << Solution().lengthOfLastWord("a          ") << '\n';
    std::cout << Solution().lengthOfLastWord("      ") << '\n';

    return 0;
}
