#include <vector>
#include <string>
#include <charconv>
#include <sstream>
#include <cassert>

class Solution
{
public :
    std::string encode(std::vector<std::string> strs)
    {
        if (strs.empty())
        {
            return {};
        }

        constexpr char DELIMETER = ';';
        std::stringstream ss;

        ss << strs.size() << DELIMETER;

        for (const auto& str : strs)
        {
            ss << str.size() << DELIMETER << str.c_str();
        }

        return ss.str();
    }

    std::vector<std::string> decode(std::string str)
    {
        if (str.empty())
        {
            return {};
        }

        constexpr char DELIMETER = ';';
        std::vector<std::string> decoded;
        size_t pos = str.find_first_of(DELIMETER);

        if (pos == std::string::npos)
        {
            return {};
        }

        size_t size = 0;
        auto res = std::from_chars(
            str.data(), str.data() + pos, size);

        if (res.ec != std::errc{})
        {
            return {};
        }

        decoded.reserve(size);
        pos += 1;

        while (pos < str.size())
        {
            int pos2 = pos;

            pos = str.find_first_of(DELIMETER, pos2);

            if (pos == std::string::npos)
            {
                return {};
            }

            res = std::from_chars(
                str.data() + pos2, str.data() + pos, size);

            if (res.ec != std::errc())
            {
                return {};
            }

            std::string s;

            s.reserve(size);
            pos += 1;

            for (int n = 0; n < size; ++n)
            {
                s.push_back(str[pos++]);
            }

            decoded.emplace_back(std::move(s));
        }

        return decoded;
    }
};

inline void check(
    const std::vector<std::string>& strs,
    std::vector<std::string> expected)
{
    assert(strs == expected);
}

int main()
{
    Solution s;

    check(s.decode(s.encode({"leet", "code", "love", "you"})),
          {"leet", "code", "love", "you"});
    check(s.decode(s.encode({"we", "say", ":", "yes"})),
          {"we", "say", ":", "yes"});
    check(s.decode(s.encode({"64don\'t32", "27quit9", "124me5"})),
          {"64don\'t32", "27quit9", "124me5"});
    check(s.decode(s.encode({"hello", "world"})),
          {"hello", "world"});
    check(s.decode(s.encode({"", "abc", ""})),
          {"", "abc", ""});
    check(s.decode(s.encode({"123", "45"})),
          {"123", "45"});
    check(s.decode(s.encode({"a#b", "##", "#hello#"})),
          {"a#b", "##", "#hello#"});
    check(s.decode(s.encode({})),
          {});

    return 0;
}
