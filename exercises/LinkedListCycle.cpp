#include <iostream>

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

        ListNode *tortoise = head;
        ListNode *hare = head->next;

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
    std::cout << std::boolalpha;

    {
        ListNode *head = new ListNode(3);

        head->next = new ListNode(2);
        head->next->next = new ListNode(0);
        head->next->next->next = new ListNode(-4);
        head->next->next->next->next = head->next;

        std::cout << Solution().hasCycle(head) << '\n';
    }

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);
        head->next->next = head;

        std::cout << Solution().hasCycle(head) << '\n';
    }

    {
        std::cout << Solution().hasCycle(new ListNode(1)) << '\n';
    }

    return 0;
}
