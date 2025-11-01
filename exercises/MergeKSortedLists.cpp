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
    ListNode *mergeKLists(std::vector<ListNode *> lists)
    {
        if (lists.empty())
        {
            return nullptr;
        }

        ListNode *mergedKLists = nullptr;
        ListNode *last = nullptr;

        while (true)
        {
            int listToUsePos = -1;

            for (int n = 0; n < lists.size(); ++n)
            {
                if (!lists[n])
                {
                    continue;
                }

                if (listToUsePos == -1
                    || lists[listToUsePos]->val >= lists[n]->val)
                {
                    listToUsePos = n;
                }
            }

            if (listToUsePos == -1)
            {
                break;
            }

            addNode(&mergedKLists, &last, lists[listToUsePos]->val);
            lists[listToUsePos] = lists[listToUsePos]->next;
        }

        return mergedKLists;
    }

private :
    inline void addNode(
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
        ListNode *list = new ListNode(1);

        list->next = new ListNode(4);
        list->next->next = new ListNode(5);

        ListNode *list2 = new ListNode(1);

        list2->next = new ListNode(3);
        list2->next->next = new ListNode(4);

        ListNode *list3 = new ListNode(2);

        list3->next = new ListNode(6);

        check(Solution().mergeKLists({list, list2, list3}),
              {1, 1, 2, 3, 4, 4, 5, 6});
    }

    {
        check(Solution().mergeKLists({}), {});
    }

    {
        ListNode *list = new ListNode(1);

        list->next = new ListNode(2);
        list->next->next = new ListNode(3);

        check(Solution().mergeKLists({list}),
              {1, 2, 3});
    }

    {
        ListNode *list = nullptr;
        ListNode *list2 = nullptr;

        check(Solution().mergeKLists({list, list2}),
              {});
    }

    {
        ListNode *list = new ListNode(1);

        list->next = new ListNode(10);

        ListNode *list2 = new ListNode(2);
        ListNode *list3 = new ListNode(3);

        list3->next = new ListNode(4);
        list3->next->next = new ListNode(5);

        check(Solution().mergeKLists({list, list2, list3}),
              {1, 2, 3, 4, 5, 10});
    }

    {
        ListNode *list = new ListNode(5);
        ListNode *list2 = new ListNode(1);
        ListNode *list3 = new ListNode(3);

        check(Solution().mergeKLists({list, list2, list3}),
              {1, 3, 5});
    }

    {
        ListNode *list = new ListNode(2);

        list->next = new ListNode(2);

        ListNode *list2 = new ListNode(2);

        list2->next = new ListNode(2);

        check(Solution().mergeKLists({list, list2}),
              {2, 2, 2, 2});
    }

    {
        ListNode *list = new ListNode(1);
        ListNode *cur = list;

        for (int i = 2; i <= 10; ++i)
        {
            cur->next = new ListNode(i);
            cur = cur->next;
        }

        ListNode *list2 = new ListNode(5);
        ListNode *list3 = new ListNode(7);

        check(Solution().mergeKLists({list, list2, list3}),
              {1, 2, 3, 4, 5, 5, 6, 7, 7, 8, 9, 10});
    }

    {
        ListNode *list = nullptr;
        ListNode *list2 = new ListNode(1);

        list2->next = new ListNode(2);

        ListNode *list3 = nullptr;

        check(Solution().mergeKLists({list, list2, list3}),
              {1, 2});
    }

    {
        std::vector<ListNode*> lists;

        for (int i = 0; i < 10; ++i)
        {
            lists.push_back(new ListNode(i));
        }

        check(Solution().mergeKLists(lists),
              {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    }

    return 0;
}
