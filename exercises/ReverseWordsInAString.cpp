#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <iostream>

class Solution
{
public :
    std::string reverseWords(std::string s)
    {
        if (s.empty())
        {
            return {};
        }

        std::vector<std::string_view> words = split(s);

        std::reverse(words.begin(), words.end());

        std::string reversedWords;
        auto begin = words.cbegin();
        auto end = words.cend();

        reversedWords.assign(begin->data(), begin->size());
        ++begin;

        while (begin != end)
        {
            reversedWords.push_back(' ');
            reversedWords.append(begin->data(), begin->size());
            ++begin;
        }

        return reversedWords;
    }

private :
    [[nodiscard]]
    inline std::vector<std::string_view> split(
        std::string_view s) const
    {
        constexpr const char *DELIMS = " ";
        std::vector<std::string_view> words;
        size_t res = 0;
        size_t pos = 0;

        while ((res = s.find_first_not_of(DELIMS, pos))
               != std::string_view::npos)
        {
            pos = s.find_first_of(DELIMS, res + 1);
            words.emplace_back(s.substr(res, pos - res));
        }

        return words;
    }
};

int main()
{
    std::cout << Solution().reverseWords("the sky is blue") << '\n';
    std::cout << Solution().reverseWords("  hello world  ") << '\n';
    std::cout << Solution().reverseWords("a good   example") << '\n';

    return 0;
}
