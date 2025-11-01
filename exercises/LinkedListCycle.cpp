#include <cstddef>
#include <cassert>

// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) { }
};

class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        if (!head)
        {
            return false;
        }

        const ListNode *tortoise = head;
        const ListNode *hare = head->next;

        while (tortoise)
        {
            if (tortoise == hare)
            {
                return true;
            }

            tortoise = tortoise->next;

            if (hare)
            {
                hare = (hare->next) ?
                    hare->next->next : hare->next;
            }
        }

        return false;
    }
};

int main()
{
    {
        ListNode *head = new ListNode(3);

        head->next = new ListNode(2);
        head->next->next = new ListNode(0);
        head->next->next->next = new ListNode(-4);
        head->next->next->next->next = head->next;

        assert(Solution().hasCycle(head));
    }

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);
        head->next->next = head;

        assert(Solution().hasCycle(head));
    }

    {
        assert(!Solution().hasCycle(new ListNode(1)));
    }

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);
        head->next->next = new ListNode(3);

        assert(!Solution().hasCycle(head));
    }

    {
        ListNode *head = new ListNode(1);

        head->next = head;

        assert(Solution().hasCycle(head));
    }

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);
        head->next->next->next->next->next = head->next->next;

        assert(Solution().hasCycle(head));
    }

    {
        ListNode *head = new ListNode(10);
        ListNode *cur = head;

        for (int i = 0; i < 20; ++i)
        {
            cur->next = new ListNode(i);
            cur = cur->next;
        }

        assert(!Solution().hasCycle(head));
    }

    {
        ListNode *head = new ListNode(10);
        ListNode *cur = head;
        ListNode *cycleEntry = nullptr;

        for (int i = 0; i < 20; ++i)
        {
            cur->next = new ListNode(i);
            cur = cur->next;

            if (i == 5)
            {
                cycleEntry = cur;
            }
        }

        cur->next = cycleEntry;

        assert(Solution().hasCycle(head));
    }

    return 0;
}
