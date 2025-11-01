#include <string>
#include <limits>
#include <iostream>

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
            int nullVal = std::numeric_limits<int>::min();

            data.append(
                reinterpret_cast<const char *>(&nullVal),
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

std::ostream& operator<<(
    std::ostream& os, const TreeNode *root) noexcept
{
    if (!root)
    {
        os << "EMPTY";

        return os;
    }

    struct
    {
        std::ostream& os;

        void operator()(const TreeNode *node) const noexcept
        {
            if (!node)
            {
                return;
            }

            os << ", " << node->val;
            (*this)(node->left);
            (*this)(node->right);
        }
    } traverseTree{os};

    std::cout << root->val;
    traverseTree(root->left);
    traverseTree(root->right);

    return os;
}

int main()
{
    {
        Codec serDeser;

        std::cout <<
            serDeser.deserialize(serDeser.serialize(new TreeNode(1)))
                  << '\n';
    }

    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);

        Codec serDeser;

        std::cout <<
            serDeser.deserialize(serDeser.serialize(root))
                  << '\n';
    }

    {
        TreeNode *root = new TreeNode(1);

        root->right = new TreeNode(2);

        Codec serDeser;

        std::cout <<
            serDeser.deserialize(serDeser.serialize(root))
                  << '\n';
    }

    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);
        root->right = new TreeNode(3);

        Codec serDeser;

        std::cout <<
            serDeser.deserialize(serDeser.serialize(root))
                  << '\n';
    }

    {
        TreeNode *root = new TreeNode(1);

        root->right = new TreeNode(2);
        root->right->left = new TreeNode(3);

        Codec serDeser;

        std::cout <<
            serDeser.deserialize(serDeser.serialize(root))
                  << '\n';
    }

    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->right->left = new TreeNode(4);
        root->right->right = new TreeNode(5);

        Codec serDeser;

        std::cout <<
            serDeser.deserialize(serDeser.serialize(root))
                  << '\n';
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

        std::cout <<
            serDeser.deserialize(serDeser.serialize(root))
                  << '\n';
    }

    {
        Codec serDeser;

        std::cout <<
            serDeser.deserialize(serDeser.serialize(nullptr))
                  << '\n';
    }

    return 0;
}
