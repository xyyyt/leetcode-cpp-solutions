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
    void reorderList(ListNode *head)
    {
        if (!head)
        {
            return;
        }

        ListNode *prev = nullptr;
        ListNode *curr = head;
        int n = 0;

        while (curr && curr->next)
        {
            if (n % 2 == 0)
            {
                prev = curr;
                curr = curr->next;
            }
            else
            {
                ListNode *last = reorderList(prev, curr);

                prev->next = last;
                last->next = curr;
                curr = last->next;
            }

            ++n;
        }
    }

private :
    [[nodiscard]]
    ListNode *reorderList(
        ListNode *prev, ListNode *curr) const noexcept
    {
        if (!curr)
        {
            return nullptr;
        }

        ListNode *last = reorderList(curr, curr->next);

        if (last)
        {
            return last;
        }

        prev->next = curr->next;

        return curr;
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

        Solution().reorderList(head);
        check(head, {1, 4, 2, 3});
    }

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);

        Solution().reorderList(head);
        check(head, {1, 5, 2, 4, 3});
    }

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);

        Solution().reorderList(head);
        check(head, {1, 2});
    }

    {
        ListNode *head = new ListNode(1);

        Solution().reorderList(head);
        check(head, {1});
    }

    {
        ListNode *head = new ListNode(10);

        head->next = new ListNode(20);
        head->next->next = new ListNode(30);

        Solution().reorderList(head);
        check(head, {10, 30, 20});
    }

    {
        ListNode *head = new ListNode(1);
        ListNode *cur = head;

        for (int i = 2; i <= 8; ++i)
        {
            cur->next = new ListNode(i);
            cur = cur->next;
        }

        Solution().reorderList(head);
        check(head, {1, 8, 2, 7, 3, 6, 4, 5});
    }

    {
        ListNode *head = new ListNode(1);
        ListNode *cur = head;

        for (int i = 2; i <= 9; ++i)
        {
            cur->next = new ListNode(i);
            cur = cur->next;
        }

        Solution().reorderList(head);
        check(head, {1, 9, 2, 8, 3, 7, 4, 6, 5});
    }

    {
        ListNode *head = new ListNode(5);

        head->next = new ListNode(11);
        head->next->next = new ListNode(7);
        head->next->next->next = new ListNode(9);
        head->next->next->next->next = new ListNode(13);

        Solution().reorderList(head);
        check(head, {5, 13, 11, 9, 7});
    }

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(4);
        head->next->next = new ListNode(2);
        head->next->next->next = new ListNode(3);

        Solution().reorderList(head);
        check(head, {1, 3, 4, 2});
    }

    {
        ListNode *head = new ListNode(2);

        head->next = new ListNode(2);
        head->next->next = new ListNode(2);
        head->next->next->next = new ListNode(2);

        Solution().reorderList(head);
        check(head, {2, 2, 2, 2});
    }

    return 0;
}
