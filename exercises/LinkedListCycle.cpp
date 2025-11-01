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

    return 0;
}
