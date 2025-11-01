#include <iostream>

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
public :
    ListNode* reverseList(ListNode *head)
    {
        if (!head)
        {
            return nullptr;
        }

        ListNode *prev = nullptr;
        ListNode *curr = head;

        while (curr)
        {
            ListNode *tmp = curr->next;

            curr->next = prev;
            prev = curr;
            curr = tmp;
        }

        return prev;
    }
};

// Recursive solution
// class Solution
// {
// public :
//     ListNode* reverseList(ListNode *head)
//     {
//         return (head) ? reverseList(head, nullptr) : nullptr;
//     }

// private :
//     [[nodiscard]]
//     ListNode *reverseList(ListNode *current, ListNode *previous) const noexcept
//     {
//         if (!current)
//         {
//             return nullptr;
//         }

//         ListNode *node = reverseList(current->next, current);

//         current->next = previous;

//         return (node) ? node : current;
//     }
// };

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

        std::cout << Solution().reverseList(head) << '\n';
    }

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);

        std::cout << Solution().reverseList(head) << '\n';
    }

    return 0;
}
