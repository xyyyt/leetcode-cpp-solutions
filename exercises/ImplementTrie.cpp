#include <unordered_map>
#include <string>
#include <string_view>
#include <iostream>

class Trie
{
public:
    void insert(std::string word)
    {
        insert(_root, word);
    }

    bool search(std::string word)
    {
        return search(_root, word);
    }

    bool startsWith(std::string prefix)
    {
        return startsWith(_root, prefix);
    }

private :
    struct Node
    {
        char c = '\0';
        bool isTerminal = false; // = 'true' is considered as a inserted word
        std::unordered_map<char, Node *> childNodes;
    };

    Node *_root = new Node{'\0', true};

    void insert(Node *node, std::string_view word)
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

        insert(it->second, word.substr(1));
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

        auto it = node->childNodes.find(word[0]);

        return (it != node->childNodes.cend()) ?
            search(it->second, word.substr(1)) : false;
    }

    [[nodiscard]]
    bool startsWith(const Node *node, std::string_view prefix) const
    {
        if (prefix.empty())
        {
            return true;
        }
        else if (node->childNodes.empty())
        {
            return false;
        }

        auto it = node->childNodes.find(prefix[0]);

        return (it != node->childNodes.cend()) ?
            startsWith(it->second, prefix.substr(1)) : false;
    }
};

int main()
{
    std::cout << std::boolalpha;

    {
        Trie trie;

        trie.insert("apple");
        std::cout << trie.search("apple");
        std::cout << ", " << trie.search("app");
        std::cout << ", " << trie.startsWith("app");
        trie.insert("app");
        std::cout << ", " << trie.search("app") << '\n';
    }

    {
        Trie trie;

        trie.insert("and");
        trie.insert("ant");
        trie.insert("do");
        trie.insert("dad");
        std::cout << trie.search("do");
        std::cout << ", " << trie.search("gee");
        std::cout << ", " << trie.search("bat");
        std::cout << ", " << trie.startsWith("o");
        std::cout << ", " << trie.startsWith("ge");
        std::cout << ", " << trie.startsWith("ba");
        std::cout << ", " << trie.startsWith("do");
        std::cout << ", " << trie.startsWith("de");
        std::cout << ", " << trie.startsWith("a");
        std::cout << ", " << trie.startsWith("andantdodad");
        std::cout << ", " << trie.search("andd");
        std::cout << ", " << trie.search("ddddo") << '\n';
    }

    {
        Trie trie;

        std::cout << trie.search("");
        std::cout << ", " << trie.startsWith("");
        std::cout << ", " << trie.search("01234");
        std::cout << ", " << trie.search("56789");
        trie.insert("op123");
        std::cout << ", " << trie.startsWith("p");
        std::cout << ", " << trie.startsWith("o");
        std::cout << ", " << trie.startsWith("op123456789");
        std::cout << ", " << trie.search("p");
        std::cout << ", " << trie.search("o");
        std::cout << ", " << trie.search("op123456789");
        std::cout << ", " << trie.search("op123");
        std::cout << ", " << trie.startsWith("op123") << '\n';
    }

    return 0;
}
