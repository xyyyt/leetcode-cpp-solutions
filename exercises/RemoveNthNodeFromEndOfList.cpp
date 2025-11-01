#include <iostream>

// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) { }
    ListNode(int x) : val(x), next(nullptr) { }
    ListNode(int x, ListNode *next) : val(x), next(next) { }
};

class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        if (!head)
        {
            return nullptr;
        }

        int n2 = 0;

        return removeNthFromEnd(nullptr, head, n, n2);
    }

private :
    ListNode *removeNthFromEnd(
        ListNode *prev, ListNode *curr, int n, int& n2) const
    {
        if (!curr)
        {
            return nullptr;
        }

        removeNthFromEnd(curr, curr->next, n, n2);
        ++n2;

        ListNode *node = curr;

        if (n == n2)
        {
            if (prev)
            {
                prev->next = curr->next;
            }
            else
            {
                node = node->next;
            }

            delete curr;
        }

        return node;
    }
};

std::ostream& operator<<(
    std::ostream& os, const ListNode *head) noexcept
{
    if (!head)
    {
        os << "EMPTY";

        return os;
    }

    os << head->val;
    head = head->next;

    while (head)
    {
        os << ", " << head->val;
        head = head->next;
    }

    return os;
}

int main()
{
    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);

        std::cout << Solution().removeNthFromEnd(head, 2) << '\n';
    }

    {
        std::cout << Solution().removeNthFromEnd(new ListNode(1), 1) << '\n';
    }

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);

        std::cout << Solution().removeNthFromEnd(head, 1) << '\n';
    }

    return 0;
}
