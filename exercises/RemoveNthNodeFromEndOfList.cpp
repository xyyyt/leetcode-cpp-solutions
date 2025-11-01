#include <vector>
#include <cassert>

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

void check(
    const ListNode *head, std::vector<int> expected)
{
    int n = 0;

    while (head)
    {
        assert(n < expected.size());
        assert(head->val == expected[n++]);
        head = head->next;
    }

    assert(n == expected.size());
}

int main()
{
    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);

        check(Solution().removeNthFromEnd(head, 2),
              {1, 2, 3, 5});
    }

    {
        check(Solution().removeNthFromEnd(new ListNode(1), 1),
              {});
    }

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);

        check(Solution().removeNthFromEnd(head, 1),
              {1});
    }

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);
        head->next->next = new ListNode(3);

        check(Solution().removeNthFromEnd(head, 1),
              {1, 2});
    }

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);
        head->next->next = new ListNode(3);

        check(Solution().removeNthFromEnd(head, 3),
              {2, 3});
    }

    {
        ListNode *head = new ListNode(1);

        check(Solution().removeNthFromEnd(head, 1),
              {});
    }

    {
        ListNode *head = new ListNode(10);

        head->next = new ListNode(20);
        head->next->next = new ListNode(30);
        head->next->next->next = new ListNode(40);
        head->next->next->next->next = new ListNode(50);

        check(Solution().removeNthFromEnd(head, 3),
              {10, 20, 40, 50});
    }

    {
        ListNode *head = new ListNode(1);
        ListNode *cur = head;

        for (int i = 2; i <= 10; ++i)
        {
            cur->next = new ListNode(i);
            cur = cur->next;
        }

        check(Solution().removeNthFromEnd(head, 1),
              {1, 2, 3, 4, 5, 6, 7, 8, 9});
    }

    {
        ListNode *head = new ListNode(1);
        ListNode *cur = head;

        for (int i = 2; i <= 10; ++i)
        {
            cur->next = new ListNode(i);
            cur = cur->next;
        }

        check(Solution().removeNthFromEnd(head, 10),
              {2, 3, 4, 5, 6, 7, 8, 9, 10});
    }

    {
        ListNode *head = new ListNode(5);

        head->next = new ListNode(6);
        head->next->next = new ListNode(7);
        head->next->next->next = new ListNode(8);

        check(Solution().removeNthFromEnd(head, 2),
              {5, 6, 8});
    }

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);

        check(Solution().removeNthFromEnd(head, 1),
              {1});
    }

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);

        check(Solution().removeNthFromEnd(head, 2),
              {2});
    }

    return 0;
}
