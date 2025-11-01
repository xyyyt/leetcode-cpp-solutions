#include <string>
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
public:
    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        if (!head)
        {
            return nullptr;
        }
        else if (left >= right)
        {
            return head;
        }

        ListNode *prev = nullptr;
        ListNode *curr = head;
        int n = 1;

        while (n < left && curr)
        {
            prev = curr;
            curr = curr->next;
            ++n;
        }

        bool headMustBeReversed = (n == 1);
        ListNode *prevBeforeLeft = prev;
        ListNode *leftNode = curr;

        while (n <= right && curr)
        {
            ListNode *tmp = curr->next;

            curr->next = prev;
            prev = curr;
            curr = tmp;
            ++n;
        }

        if (prevBeforeLeft)
        {
            prevBeforeLeft->next = prev;
        }

        leftNode->next = curr;

        return (headMustBeReversed) ? prev : head;
    }
};

// Recursive solution
// class Solution
// {
// public :
//     ListNode *reverseBetween(ListNode *head, int left, int right)
//     {
//         if (!head)
//         {
//             return nullptr;
//         }
//         else if (left >= right)
//         {
//             return head;
//         }

//         ListNode *prevBeforeLeft = nullptr;
//         ListNode *nextAfterRight = nullptr;
//         bool headMustBeReversed = false;

//         return reverseBetween(
//             head,
//             head,
//             nullptr,
//             &prevBeforeLeft,
//             &nextAfterRight,
//             headMustBeReversed,
//             left,
//             right,
//             1);
//     }

// private :
//     [[nodiscard]]
//     ListNode *reverseBetween(
//         ListNode *head,
//         ListNode *current,
//         ListNode *previous,
//         ListNode **prevBeforeLeft,
//         ListNode **nextAfterRight,
//         bool& headMustBeReversed,
//         int left,
//         int right,
//         int n) const noexcept
//     {
//         if (!current)
//         {
//             return nullptr;
//         }

//         if (n == right)
//         {
//             *nextAfterRight = current->next;
//             current->next = previous;

//             if (*prevBeforeLeft)
//             {
//                 (*prevBeforeLeft)->next = current;
//             }

//             return (headMustBeReversed) ? current : head;
//         }
//         else if (n >= left)
//         {
//             if (n == 1)
//             {
//                 headMustBeReversed = true;
//             }

//             if (n == left)
//             {
//                 *prevBeforeLeft = previous;
//             }

//             ListNode *node = reverseBetween(
//                 head,
//                 current->next,
//                 current,
//                 prevBeforeLeft,
//                 nextAfterRight,
//                 headMustBeReversed,
//                 left,
//                 right,
//                 n + 1);

//             current->next = (n == left) ? *nextAfterRight : previous;

//             return node;
//         }
//         else
//         {
//             return reverseBetween(
//                 head,
//                 current->next,
//                 current,
//                 prevBeforeLeft,
//                 nextAfterRight,
//                 headMustBeReversed,
//                 left,
//                 right,
//                 n + 1);
//         }
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

        std::cout << Solution().reverseBetween(head, 2, 4) << '\n';
    }

    {
        ListNode *head = new ListNode(2);

        head->next = new ListNode(3);
        head->next->next = new ListNode(4);

        std::cout << Solution().reverseBetween(head, 1, 3) << '\n';
    }

    {
        ListNode *head = new ListNode(5);

        std::cout << Solution().reverseBetween(head, 1, 1) << '\n';
    }

    return 0;
}
