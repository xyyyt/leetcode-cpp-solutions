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
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        if (!list1 && !list2)
        {
            return nullptr;
        }

        ListNode *list3 = nullptr;
        ListNode *last = nullptr;

        while (list1 || list2)
        {
            if (list1 && (!list2 || list1->val < list2->val))
            {
                addNode(&list3, &last, list1->val);
                list1 = list1->next;
            }
            else if (list2 && (!list1 || list1->val >= list2->val))
            {
                addNode(&list3, &last, list2->val);
                list2 = list2->next;
            }
        }

        return list3;
    }

private :
    void addNode(
        ListNode **head, ListNode **last, int val) const
    {
        ListNode *node = new ListNode(val);

        if (!*head)
        {
            *head = node;
            *last = *head;
        }
        else
        {
            (*last)->next = node;
            (*last) = (*last)->next;
        }
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
        ListNode *list1 = new ListNode(1);

        list1->next = new ListNode(2);
        list1->next->next = new ListNode(4);

        ListNode *list2 = new ListNode(1);

        list2->next = new ListNode(3);
        list2->next->next = new ListNode(4);

        check(Solution().mergeTwoLists(list1, list2),
              {1, 1, 2, 3, 4, 4});
    }

    {
        check(Solution().mergeTwoLists(nullptr, nullptr),
              {});
    }

    {
        check(Solution().mergeTwoLists(nullptr, new ListNode(0)),
              {0});
    }

    return 0;
}
