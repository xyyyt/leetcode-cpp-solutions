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

    return 0;
}
