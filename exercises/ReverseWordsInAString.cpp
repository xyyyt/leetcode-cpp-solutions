#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <cassert>

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

        if (words.empty())
        {
            return {};
        }

        std::reverse(words.begin(), words.end());

        std::string res;
        auto begin = words.cbegin();
        auto end = words.cend();

        res.assign(begin->data(), begin->size());
        ++begin;

        while (begin != end)
        {
            res.push_back(' ');
            res.append(begin->data(), begin->size());
            ++begin;
        }

        return res;
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
    assert(Solution().reverseWords("the sky is blue")
           == "blue is sky the");
    assert(Solution().reverseWords("  hello world  ")
           == "world hello");
    assert(Solution().reverseWords("a good   example")
           == "example good a");
    assert(Solution().reverseWords("hello")
           == "hello");
    assert(Solution().reverseWords(" ")
           == "");
    assert(Solution().reverseWords("a1 b2 c3")
           == "c3 b2 a1");
    assert(Solution().reverseWords("hello @world !test")
           == "!test @world hello");
    assert(Solution().reverseWords(" this is a test ")
           == "test a is this");
    assert(Solution().reverseWords("a b")
           == "b a");
    assert(Solution().reverseWords("one two three four five six")
           == "six five four three two one");
    assert(Solution().reverseWords("hello, world!")
           == "world! hello,");

    return 0;
}
