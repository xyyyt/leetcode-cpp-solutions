#include <unordered_map>
#include <string>
#include <string_view>
#include <iostream>
#include <cassert>

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
    {
        Trie trie;

        trie.insert("apple");
        assert(trie.search("apple"));
        assert(!trie.search("app"));
        assert(trie.startsWith("app"));
        trie.insert("app");
        assert(trie.search("app"));
    }

    {
        Trie trie;

        trie.insert("and");
        trie.insert("ant");
        trie.insert("do");
        trie.insert("dad");
        assert(trie.search("do"));
        assert(!trie.search("gee"));
        assert(!trie.search("bat"));
        assert(!trie.startsWith("o"));
        assert(!trie.startsWith("ge"));
        assert(!trie.startsWith("ba"));
        assert(trie.startsWith("do"));
        assert(!trie.startsWith("de"));
        assert(trie.startsWith("a"));
        assert(!trie.startsWith("andantdodad"));
        assert(!trie.search("andd"));
        assert(!trie.search("ddddo"));
    }

    {
        Trie trie;

        assert(trie.search(""));
        assert(trie.startsWith(""));
        assert(!trie.search("01234"));
        assert(!trie.search("56789"));
        trie.insert("op123");
        assert(!trie.startsWith("p"));
        assert(trie.startsWith("o"));
        assert(!trie.startsWith("op123456789"));
        assert(!trie.search("p"));
        assert(!trie.search("o"));
        assert(!trie.search("op123456789"));
        assert(trie.search("op123"));
        assert(trie.startsWith("op123"));
    }

    {
        Trie trie;

        trie.insert("apple");
        assert(trie.search("apple"));
        assert(!trie.search("app"));
        assert(trie.startsWith("app"));
        trie.insert("app");
        assert(trie.search("app"));
        trie.insert("banana");
        trie.insert("band");
        trie.insert("bandana");
        assert(trie.search("banana"));
        assert(trie.startsWith("ban"));
        assert(!trie.search("ban"));
        assert(trie.search("band"));
        assert(trie.search("bandana"));
        trie.insert("a");
        trie.insert("at");
        assert(trie.search("a"));
        assert(trie.search("at"));
        assert(!trie.search("att"));
        assert(trie.startsWith("a"));
        trie.insert("car");
        trie.insert("cart");
        trie.insert("carbon");
        assert(trie.search("car"));
        assert(!trie.search("cars"));
        assert(trie.startsWith("car"));
        assert(trie.search("cart"));
        assert(trie.search("carbon"));
        assert(!trie.startsWith("zzz"));
        assert(!trie.search("zzz"));
        trie.insert("test");
        trie.insert("tester");
        trie.insert("testing");
        assert(trie.search("test"));
        assert(trie.search("tester"));
        assert(trie.search("testing"));
        assert(!trie.search("testers"));
        assert(trie.startsWith("test"));
    }

    return 0;
}
