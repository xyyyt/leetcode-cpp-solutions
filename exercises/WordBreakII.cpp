#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream>

class Solution
{
public :
    std::vector<std::string> wordBreak(
        std::string s, std::vector<std::string> wordDict)
    {
        if (s.empty())
        {
            return {};
        }

        std::vector<std::string> sentences;

        wordBreak(s, wordDict, sentences, {});

        return sentences;
    }

private :
    void wordBreak(
        std::string_view s,
        const std::vector<std::string>& wordDict,
        std::vector<std::string>& sentences,
        const std::vector<std::string_view>& partialSentence) const
    {
        if (s.empty())
        {
            auto join = [](
               const std::vector<std::string_view>& completeSentence,
               char delimeter) -> std::string
            {
                std::string sentence;

                if (auto begin = completeSentence.begin(),
                    end = completeSentence.end();
                    begin != end)
                {
                    sentence += *begin;
                    ++begin;

                    while (begin != end)
                    {
                        sentence.push_back(delimeter);
                        sentence.append(*begin);
                        ++begin;
                    }
                }

                return sentence;
            };

            constexpr char DELIMETER = ' ';

            sentences.emplace_back(join(partialSentence, DELIMETER));

            return;
        }

        for (const auto& word : wordDict)
        {
            std::string_view prefix(
                s.data(), std::min(s.size(), word.size()));

            if (prefix == word)
            {
                std::vector<std::string_view> partialSentence2;

                partialSentence2.reserve(partialSentence.size() + 1);
                partialSentence2.assign(
                    partialSentence.cbegin(), partialSentence.cend());
                partialSentence2.emplace_back(word);
                wordBreak(s.substr(
                    word.size()), wordDict, sentences, partialSentence2);
            }
        }
    }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<std::string>& sentences) noexcept
{
    if (sentences.empty())
    {
        os << "EMPTY";

        return os;
    }

    auto begin = sentences.cbegin();
    auto end = sentences.end();

    os << "\"" << *begin << "\"";
    ++begin;

    while (begin != end)
    {
        os << ", " << "\"" << *begin << "\"";
        ++begin;
    }

    return os;
}

int main()
{
    std::cout << Solution().wordBreak("catsanddog",
                                      {"cat","cats","and","sand","dog"})
              << '\n';
    std::cout << Solution().wordBreak("pineapplepenapple",
                                      {"apple","pen","applepen","pine","pineapple"})
              << '\n';
    std::cout << Solution().wordBreak("catsandog",
                                      {"cats","dog","sand","and","cat"})
              << '\n';

    return 0;
}
