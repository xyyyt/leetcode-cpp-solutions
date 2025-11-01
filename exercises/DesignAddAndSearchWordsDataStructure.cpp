#include <unordered_map>
#include <string>
#include <string_view>
#include <cassert>

class WordDictionary
{
public :
    void addWord(std::string word)
    {
        addWord(_root, word);
    }

    bool search(std::string word)
    {
        return search(_root, word);
    }

private :
    struct Node
    {
        char c = '\0';
        bool isTerminal = false; // = 'true' is considered as a inserted word
        std::unordered_map<char, Node *> childNodes;
    };

    Node *_root = new Node{'\0', true};

    void addWord(Node *node, std::string_view word)
    {
        if (word.empty())
        {
            node->isTerminal = true;

            return;
        }

        auto it = node->childNodes.find(word[0]);

        if (it == node->childNodes.cend())
        {
            it = node->childNodes.emplace(
                word[0], new Node{word[0]}).first;
        }

        addWord(it->second, word.substr(1));
    }

    [[nodiscard]]
    bool search(const Node *node, std::string_view word) const
    {
        if (word.empty())
        {
            return node->isTerminal;
        }
        else if (node->childNodes.empty())
        {
            return false;
        }

        constexpr char ANY = '.';

        if (word[0] == ANY)
        {
            for (auto [_, childNode] : node->childNodes)
            {
                if (search(childNode, word.substr(1)))
                {
                    return true;
                }
            }
        }
        else
        {
            if (auto it = node->childNodes.find(word[0]);
                it != node->childNodes.cend())
            {
                return search(it->second, word.substr(1));
            }
        }

        return false;
    }
};

int main()
{
    {
        WordDictionary wordDictionary;

        wordDictionary.addWord("bad");
        wordDictionary.addWord("dad");
        wordDictionary.addWord("mad");
        assert(!wordDictionary.search("pad"));
        assert(wordDictionary.search("bad"));
        assert(wordDictionary.search(".ad"));
        assert(wordDictionary.search("b.."));
    }

    {

        WordDictionary wordDictionary;

        assert(wordDictionary.search(""));
        assert(!wordDictionary.search("a"));
        assert(!wordDictionary.search("ab"));
        wordDictionary.addWord("ab");
        wordDictionary.addWord("abc");
        assert(!wordDictionary.search("a"));
        assert(!wordDictionary.search("b"));
        assert(wordDictionary.search("ab"));
        assert(!wordDictionary.search("ab.."));
        assert(!wordDictionary.search("a.b."));
        assert(!wordDictionary.search("..a"));
        assert(wordDictionary.search("..c"));
        assert(wordDictionary.search(".b"));
        assert(wordDictionary.search(".."));
    }

    {
        WordDictionary wordDictionary;

        wordDictionary.addWord("bad");
        wordDictionary.addWord("dad");
        wordDictionary.addWord("mad");
        assert(!wordDictionary.search("pad"));
        assert(wordDictionary.search("bad"));
        assert(wordDictionary.search(".ad"));
        assert(wordDictionary.search("b.."));
        wordDictionary.addWord("hello");
        wordDictionary.addWord("hallo");
        wordDictionary.addWord("hullo");
        assert(wordDictionary.search("h.llo"));
        assert(wordDictionary.search("h...."));
        assert(!wordDictionary.search("he..o."));
        assert(wordDictionary.search("....."));
        wordDictionary.addWord("aaa");
        wordDictionary.addWord("aab");
        wordDictionary.addWord("abb");
        assert(wordDictionary.search("a.a"));
        assert(wordDictionary.search("aa."));
        assert(!wordDictionary.search("bbb"));
        assert(wordDictionary.search("..."));
        wordDictionary.addWord("a");
        wordDictionary.addWord("b");
        assert(wordDictionary.search("."));
        assert(wordDictionary.search("a"));
        assert(!wordDictionary.search("c"));
        wordDictionary.addWord("test");
        wordDictionary.addWord("tent");
        assert(wordDictionary.search("te.t"));
        assert(!wordDictionary.search("t..ts"));
    }

    return 0;
}
