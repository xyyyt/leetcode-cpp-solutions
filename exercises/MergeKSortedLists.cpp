#include <vector>
#include <iostream>

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
        ListNode *list = new ListNode(1);

        list->next = new ListNode(4);
        list->next->next = new ListNode(5);

        ListNode *list2 = new ListNode(1);

        list2->next = new ListNode(3);
        list2->next->next = new ListNode(4);

        ListNode *list3 = new ListNode(2);

        list3->next = new ListNode(6);

        std::cout << Solution().mergeKLists({list, list2, list3}) << '\n';
    }

    {
        std::cout << Solution().mergeKLists({}) << '\n';
    }

    {
        std::cout << Solution().mergeKLists({nullptr}) << '\n';
    }

    return 0;
}
