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
    ListNode *reverseOn(ListNode *head, int leftValue, int rightValue)
    {
        if (!head)
        {
            return nullptr;
        }

        ListNode *leftPrev = nullptr;
        ListNode *leftNode = nullptr;
        ListNode *rightPrev = nullptr;
        ListNode *rightNode = nullptr;
        ListNode *prev = nullptr;

        for (ListNode *curr = head; curr; curr = curr->next)
        {
            if (curr->val == leftValue)
            {
                leftPrev = prev;
                leftNode = curr;
            }
            if (curr->val == rightValue)
            {
                rightPrev = prev;
                rightNode = curr;

                break;
            }

            prev = curr;
        }

        if (!leftNode || !rightNode)
        {
            return head;
        }

        ListNode *nextTmp = leftNode->next;

        leftNode->next = rightNode->next;

        if (rightPrev)
        {
            rightPrev->next = leftNode;
        }

        rightNode->next = nextTmp;

        if (leftPrev)
        {
            leftPrev->next = rightNode;
        }

        return (leftNode->val == head->val) ? rightNode : head;
    }
};

// Recursive solution
// class Solution
// {
// public :
//     ListNode *reverseOn(ListNode *head, int leftValue, int rightValue)
//     {
//         if (!head)
//         {
//             return nullptr;
//         }

//         ListNode *leftNode = nullptr;
//         ListNode *leftPrev = nullptr;

//         return reverseOn(
//             head, head, nullptr, &leftNode, &leftPrev, leftValue, rightValue);
//     }

// private :
//     [[nodiscard]]
//     ListNode *reverseOn(
//         ListNode *head,
//         ListNode *current,
//         ListNode *previous,
//         ListNode **leftNode,
//         ListNode **leftPrev,
//         int leftValue,
//         int rightValue) const noexcept
//     {
//         if (!current)
//         {
//             return nullptr;
//         }

//         if (current->val == leftValue)
//         {
//             *leftNode = current;
//             *leftPrev = previous;
//         }

//         if (current->val == rightValue)
//         {
//             if (!*leftNode)
//             {
//                 return head;
//             }

//             ListNode *nextTmp = (*leftNode)->next;

//             (*leftNode)->next = current->next;

//             if (previous)
//             {
//                 previous->next = *leftNode;
//             }

//             current->next = nextTmp;

//             if (*leftPrev)
//             {
//                 (*leftPrev)->next = current;
//             }

//             return ((*leftNode)->val == head->val) ? current : head;
//         }
//         else
//         {
//             ListNode *node = reverseOn(
//                 head, current->next, current, leftNode, leftPrev, leftValue, rightValue);

//             return (node) ? node : head;
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

        check(Solution().reverseOn(head, 2, 4),
              {1, 4, 3, 2, 5});
    }

    {
        ListNode *head = new ListNode(2);

        head->next = new ListNode(3);
        head->next->next = new ListNode(4);

        check(Solution().reverseOn(head, 2, 4),
              {4, 3, 2});
    }

    {
        ListNode *head = new ListNode(5);

        check(Solution().reverseOn(head, 1, 1),
              {5});
    }

    return 0;
}
