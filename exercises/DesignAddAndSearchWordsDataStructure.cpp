#include <unordered_map>
#include <string>
#include <string_view>
#include <iostream>

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
    std::cout << std::boolalpha;

    {
        WordDictionary wordDictionary;

        wordDictionary.addWord("bad");
        wordDictionary.addWord("dad");
        wordDictionary.addWord("mad");
        std::cout << wordDictionary.search("pad");
        std::cout << ", " << wordDictionary.search("bad");
        std::cout << ", " << wordDictionary.search(".ad");
        std::cout << ", " << wordDictionary.search("b..") << '\n';
    }

    {

        WordDictionary wordDictionary;

        std::cout << wordDictionary.search("");
        std::cout << ", " << wordDictionary.search("a");
        std::cout << ", " << wordDictionary.search("ab");
        wordDictionary.addWord("ab");
        wordDictionary.addWord("abc");
        std::cout << ", " << wordDictionary.search("a");
        std::cout << ", " << wordDictionary.search("b");
        std::cout << ", " << wordDictionary.search("ab");
        std::cout << ", " << wordDictionary.search("ab..");
        std::cout << ", " << wordDictionary.search("a.b.");
        std::cout << ", " << wordDictionary.search("..a");
        std::cout << ", " << wordDictionary.search("..c");
        std::cout << ", " << wordDictionary.search(".b");
        std::cout << ", " << wordDictionary.search("..") << '\n';
    }

    return 0;
}
