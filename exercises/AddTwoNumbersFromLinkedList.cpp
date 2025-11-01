#include <iostream>
#include <stack>

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
    ListNode* addTwoNumbers(ListNode *l, ListNode *l2)
    {
        if (!l && !l2)
        {
            return nullptr;
        }

        ListNode *l3 = nullptr;
        ListNode *lCopy = l;
        ListNode *l2Copy = l2;
        ListNode *l3Copy = nullptr;
        int rest = 0;

        while (lCopy || l2Copy)
        {
            int sum = 0;

            sum += (lCopy) ? lCopy->val : 0;
            sum += (l2Copy) ? l2Copy->val : 0;

            int res = (sum + rest) % 10;

            rest = (sum + rest) / 10;

            if (!l3)
            {
                l3 = new ListNode(res);
                l3Copy = l3;
            }
            else
            {
                l3Copy->next = new ListNode(res);
                l3Copy = l3Copy->next;
            }

            lCopy = (lCopy) ? lCopy->next : nullptr;
            l2Copy = (l2Copy) ? l2Copy->next : nullptr;
        }

        if (rest > 0)
        {
            l3Copy->next = new ListNode(rest);
        }

        return l3;
    }
};

std::ostream& operator<<(
    std::ostream& os, const ListNode *list) noexcept
{
    if (!list)
    {
        os << "EMPTY";

        return os;
    }

    os << list->val;
    list = list->next;

    while (list)
    {
        os << ", " << list->val;
        list = list->next;
    }

    return os;
}

int main()
{
    {
        ListNode *l = new ListNode(2);

        l->next = new ListNode(4);
        l->next->next = new ListNode(3);


        ListNode *l2 = new ListNode(5);

        l2->next = new ListNode(6);
        l2->next->next = new ListNode{4};


        ListNode *l3 = Solution().addTwoNumbers(l, l2);

        std::cout << l3 << '\n';
    }

    {
        ListNode *l = new ListNode(0);
        ListNode *l2 = new ListNode(0);
        ListNode *l3 = Solution().addTwoNumbers(l, l2);

        std::cout << l3 << '\n';
    }

    {
        ListNode *l = new ListNode(9);

        l->next = new ListNode(9);
        l->next->next = new ListNode(9);
        l->next->next->next = new ListNode(9);
        l->next->next->next->next = new ListNode(9);
        l->next->next->next->next->next = new ListNode(9);
        l->next->next->next->next->next->next = new ListNode(9);


        ListNode *l2 = new ListNode(9);

        l2->next = new ListNode(9);
        l2->next->next = new ListNode(9);
        l2->next->next->next = new ListNode(9);


        ListNode *l3 = Solution().addTwoNumbers(l, l2);

        std::cout << l3 << '\n';
    }
}
