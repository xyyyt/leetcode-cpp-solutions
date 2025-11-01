#include <vector>
#include <string>
#include <cassert>

struct ListNode
{
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) { }
    ListNode(int x) : val(x), next(nullptr) { }
    ListNode(int x, ListNode *next) : val(x), next(next) { }
};

// Iterative solution
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

        check(Solution().reverseBetween(head, 2, 4),
              {1, 4, 3, 2, 5});
    }

    {
        ListNode *head = new ListNode(2);

        head->next = new ListNode(3);
        head->next->next = new ListNode(4);

        check(Solution().reverseBetween(head, 1, 3),
              {4, 3, 2});
    }

    {
        ListNode *head = new ListNode(5);

        check(Solution().reverseBetween(head, 1, 1),
              {5});
    }

    {
        ListNode *head = new ListNode(2);

        head->next = new ListNode(4);
        head->next->next = new ListNode(6);
        head->next->next->next = new ListNode(8);
        head->next->next->next->next = new ListNode(10);

        check(Solution().reverseBetween(head, 1, 3),
              {6, 4, 2, 8, 10});
    }

    {
        ListNode *head = new ListNode(5);

        head->next = new ListNode(7);
        head->next->next = new ListNode(9);
        head->next->next->next = new ListNode(11);

        check(Solution().reverseBetween(head, 2, 3),
              {5, 9, 7, 11});
    }

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);
        head->next->next = new ListNode(3);

        check(Solution().reverseBetween(head, 1, 2),
              {2, 1, 3});
    }

    {
        ListNode *head = new ListNode(4);

        head->next = new ListNode(5);
        head->next->next = new ListNode(6);
        head->next->next->next = new ListNode(7);

        check(Solution().reverseBetween(head, 3, 4),
              {4, 5, 7, 6});
    }

    {
        ListNode *head = new ListNode(9);

        head->next = new ListNode(8);

        check(Solution().reverseBetween(head, 1, 2),
              {8, 9});
    }

    return 0;
}
