#include <stack>
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

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode *l, ListNode *l2)
    {
        if (!l && !l2)
        {
            return nullptr;
        }

        ListNode *lCopy = l;
        ListNode *l2Copy = l2;
        ListNode *l3Copy = nullptr;
        ListNode *l3 = nullptr;
        int rest = 0;

        while (lCopy || l2Copy)
        {
            int sum = 0;

            if (lCopy)
            {
                sum += lCopy->val;
            }

            if (l2Copy)
            {
                sum += l2Copy->val;
            }

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

            if (lCopy)
            {
                lCopy = lCopy->next;
            }

            if (l2Copy)
            {
                l2Copy = l2Copy->next;
            }
        }

        if (rest > 0)
        {
            l3Copy->next = new ListNode(rest);
        }

        return l3;
    }
};

void check(
    const ListNode *list, std::vector<int> expected)
{
    int n = 0;

    while (list)
    {
        assert(n < expected.size());
        assert(list->val == expected[n++]);
        list = list->next;
    }

    assert(n == expected.size());
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

        check(l3, {7, 0, 8});
    }

    {
        ListNode *l = new ListNode(0);
        ListNode *l2 = new ListNode(0);
        ListNode *l3 = Solution().addTwoNumbers(l, l2);

        check(l3, {0});
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

        check(l3, {8, 9, 9, 9, 0, 0, 0, 1});
    }

    {
        ListNode *l = new ListNode(9);

        l->next = new ListNode(9);
        l->next->next = new ListNode(9);
        l->next->next->next = new ListNode(9);

        ListNode *l2 = new ListNode(1);
        ListNode *l3 = Solution().addTwoNumbers(l, l2);

        check(l3, {0, 0, 0, 0, 1});
    }

    {
        ListNode *l = new ListNode(1);

        l->next = new ListNode(8);

        ListNode *l2 = new ListNode(0);
        ListNode *l3 = Solution().addTwoNumbers(l, l2);

        check(l3, {1, 8});
    }

    {
        ListNode *l = new ListNode(2);

        l->next = new ListNode(4);
        l->next->next = new ListNode(9);

        ListNode *l2 = new ListNode(5);

        l2->next = new ListNode(6);

        ListNode *l3 = Solution().addTwoNumbers(l, l2);

        check(l3, {7, 0, 0, 1});
    }

    {
        ListNode *l = new ListNode(9);
        ListNode *l2 = new ListNode(1);

        l2->next = new ListNode(9);
        l2->next->next = new ListNode(9);

        ListNode *l3 = Solution().addTwoNumbers(l, l2);

        check(l3, {0, 0, 0, 1});
    }

    {
        ListNode *l = new ListNode(0);
        ListNode *l2 = new ListNode(0);
        ListNode *l3 = Solution().addTwoNumbers(l, l2);

        check(l3, {0});
    }

    {
        ListNode *l = new ListNode(9);

        l->next = new ListNode(9);
        l->next->next = new ListNode(1);

        ListNode *l2 = new ListNode(1);
        ListNode *l3 = Solution().addTwoNumbers(l, l2);

        check(l3, {0, 0, 2});
    }

    {
        ListNode *l = new ListNode(5);
        ListNode *l2 = new ListNode(7);
        ListNode *l3 = Solution().addTwoNumbers(l, l2);

        check(l3, {2, 1});
    }

    {
        ListNode *l = new ListNode(1);
        ListNode *l2 = new ListNode(9);
        ListNode *l3 = Solution().addTwoNumbers(l, l2);

        check(l3, {0, 1});
    }

    return 0;
}
