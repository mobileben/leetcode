//
// Created by Benjamin Lee on 12/11/22.
// https://leetcode.com/problems/remove-nth-node-from-end-of-list/
//

/*
 * Brute force method is a 2 pass method where the first pass gets the total length of the list and finds the node
 * to remove and the second pass traverses to the node to remove and removes it.
 *
 * Time Complexity: O(2n) == O(n)
 * Space Complexity: O(1)
 *
 * Faster method is to use two pointers. One is fast and the other is slow. Many fast and slow pointers have fast be 2X
 * the slow. However thep problem here is that one may end up with the case where the slow pointer is past the node
 * to remove by the time the fast pointer is done. To counter act this, we can first move the fast point n steps ahead
 * and the move the fast and slow pointer the same amounts.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 */
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include "../include/SinglyLinkedList.h"

class Solution {
public:
#ifdef BRUTE
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode *node = head;
        int count = 0;

        if (!head) return nullptr;

        while (node) {
            ++count;
            node = node->next;
            if (!node) {
                count -= n;
            }
        }

        int secondCount = 0;
        ListNode *prev = nullptr;

        node = head;
        while (node) {
            if (secondCount == count) {
                if (prev) {
                    prev->next = node->next;
                } else {
                    head = node->next;
                }
                break;
            }
            ++secondCount;
            prev = node;
            node = node->next;
        }

        return head;
    }
#else
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode *slow = head, *fast = head;

        if (!head) return nullptr;

        for (int i=0;i<n;++i) {
            fast = fast->next;
        }

        ListNode *prev = nullptr;

        while(fast) {
            fast = fast->next;
            prev = slow;
            slow = slow->next;
        }

        if (prev) {
            prev->next = slow->next;
        } else {
            head = slow->next;
        }

        return head;
    }
#endif /* BRUTE */
};

TEST_CASE("RemoveNthNodeFromEndOfList", "algorithm") {
    Solution soln;
    List testCase0{1, 2, 3, 4, 5};
    List testCase1{1};
    List testCase2{1, 2};
    List testCase3{1, 2, 3, 4, 5};

    std::vector<int> soln0{1, 2, 3, 5};
    std::vector<int> soln1{};
    std::vector<int> soln2{1};
    std::vector<int> soln3{2, 3, 4, 5};
    std::vector<int> soln4{2, 3, 4};
    std::vector<int> soln5{2, 4};
    std::vector<int> soln6{2};
    std::vector<int> soln7{};

    auto list3 = List(soln.removeNthFromEnd(testCase3.head, 5));
    auto actual0 = List(soln.removeNthFromEnd(testCase0.head, 2)).toVector();
    auto actual1 = List(soln.removeNthFromEnd(testCase1.head, 1)).toVector();
    auto actual2 = List(soln.removeNthFromEnd(testCase2.head, 1)).toVector();
    auto actual3 = list3.toVector();

    auto list4 = List(soln.removeNthFromEnd(list3.head, 1));
    auto actual4 = list4.toVector();
    auto list5 = List(soln.removeNthFromEnd(list4.head, 2));
    auto actual5 = list5.toVector();
    auto list6 = List(soln.removeNthFromEnd(list5.head, 1));
    auto actual6 = list6.toVector();
    auto list7 = List(soln.removeNthFromEnd(list6.head, 1));
    auto actual7 = list7.toVector();

    CHECK(actual0 == soln0);
    CHECK(actual1 == soln1);
    CHECK(actual2 == soln2);
    CHECK(actual3 == soln3);
    CHECK(actual4 == soln4);
    CHECK(actual5 == soln5);
    CHECK(actual6 == soln6);
    CHECK(actual7 == soln7);
}

