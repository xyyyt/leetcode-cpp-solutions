#include <vector>
#include <string>
#include <limits>
#include <cassert>

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) { }
};

class Codec
{
public :
    // Encodes a tree to a single string.
    std::string serialize(TreeNode *root)
    {
        if (!root)
        {
            return {};
        }

        std::string data;

        serialize(root, data);

        return data;
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(std::string data)
    {
        if (data.empty())
        {
            return nullptr;
        }

        int offset = 0;

        return deserialize(data, offset);
    }

private :
    void serialize(
        const TreeNode *node, std::string& data) const
    {
        if (!node)
        {
            constexpr int NULL_VAL = std::numeric_limits<int>::min();

            data.append(
                reinterpret_cast<const char *>(&NULL_VAL),
                sizeof(int));

            return;
        }

        data.append(
            reinterpret_cast<const char *>(&node->val),
            sizeof(int));

        serialize(node->left, data);
        serialize(node->right, data);
    }

    [[nodiscard]]
    TreeNode *deserialize(
        const std::string& data, int& offset) const
    {
        if (offset >= data.size())
        {
            return nullptr;
        }

        int val = *reinterpret_cast<const int *>(
            data.data() + offset);

        offset += sizeof(int);

        if (val == std::numeric_limits<int>::min())
        {
            return nullptr;
        }

        TreeNode *node = new TreeNode(val);

        node->left = deserialize(data, offset);
        node->right = deserialize(data, offset);

        return node;
    }
};

void check(
    const TreeNode *root, std::vector<int> expected)
{
    struct
    {
        void operator()(
            const TreeNode *node,
            const std::vector<int>& expected,
            int& n) const
        {
            if (!node)
            {
                return;
            }

            assert(n < expected.size());
            assert(node->val == expected[n++]);
            (*this)(node->left, expected, n);
            (*this)(node->right, expected, n);
        }
    } inner;
    int n = 0;

    inner(root, expected, n);
    assert(n == expected.size());
}

int main()
{
    {
        Codec serDeser;

        check(serDeser.deserialize(serDeser.serialize(new TreeNode(1))),
              {1});
    }

    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);

        Codec serDeser;

        check(serDeser.deserialize(serDeser.serialize(root)),
              {1, 2});
    }

    {
        TreeNode *root = new TreeNode(1);

        root->right = new TreeNode(2);

        Codec serDeser;

        check(serDeser.deserialize(serDeser.serialize(root)),
              {1, 2});
    }

    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);
        root->right = new TreeNode(3);

        Codec serDeser;

        check(serDeser.deserialize(serDeser.serialize(root)),
              {1, 2, 3});
    }

    {
        TreeNode *root = new TreeNode(1);

        root->right = new TreeNode(2);
        root->right->left = new TreeNode(3);

        Codec serDeser;

        check(serDeser.deserialize(serDeser.serialize(root)),
              {1, 2, 3});
    }

    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->right->left = new TreeNode(4);
        root->right->right = new TreeNode(5);

        Codec serDeser;

        check(serDeser.deserialize(serDeser.serialize(root)),
              {1, 2, 3, 4, 5});
    }

    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);
        root->right = new TreeNode(5);
        root->left->left = new TreeNode(3);
        root->left->left->left = new TreeNode(4);
        root->right->left = new TreeNode(6);
        root->right->left->left = new TreeNode(7);

        Codec serDeser;

        check(serDeser.deserialize(serDeser.serialize(root)),
              {1, 2, 3, 4, 5, 6, 7});
    }

    {
        Codec serDeser;

        check(serDeser.deserialize(serDeser.serialize(nullptr)),
              {});
    }

    return 0;
}
