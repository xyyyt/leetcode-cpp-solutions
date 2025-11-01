#include <vector>
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

// // Recursive solution
// class Solution
// {
// public :
//     ListNode* reverseList(ListNode *head)
//     {
//         return reverseList(head, nullptr);
//     }

// private :
//     [[nodiscard]]
//     ListNode *reverseList(
//         ListNode *current, ListNode *previous) const noexcept
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

        check(Solution().reverseList(head),
              {5, 4, 3, 2, 1});
    }

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(2);

        check(Solution().reverseList(head),
              {2, 1});
    }

    {
        check(Solution().reverseList(nullptr),
              {});
    }

    {
        ListNode *head = new ListNode(7);

        head->next = new ListNode(8);
        head->next->next = new ListNode(9);
        head->next->next->next = new ListNode(10);

        check(Solution().reverseList(head),
              {10, 9, 8, 7});
}

    {
        ListNode *head = new ListNode(1);

        head->next = new ListNode(1);
        head->next->next = new ListNode(2);

        check(Solution().reverseList(head),
              {2, 1, 1});
    }

    {
        ListNode *head = new ListNode(4);

        head->next = new ListNode(3);

        check(Solution().reverseList(head),
              {3, 4});
    }

    {
        ListNode *head = new ListNode(42);

        check(Solution().reverseList(head),
              {42});
    }

    return 0;
}
