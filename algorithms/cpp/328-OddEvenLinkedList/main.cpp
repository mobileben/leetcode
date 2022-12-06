//
// Created by Benjamin Lee on 12/5/22.
// https://leetcode.com/problems/odd-even-linked-list/
//

/*
 *
 *  Requirements dictate
 *  - First node is considered odd, second node is considered even, and so on
 *  - Must be solved using O(1) space complexity and O(n) time complexity
 *
 *  The Brute force method will go one node at a time
 *
 *  A faster method would be to go 2 nodes at a time. This is possible because
 *  [ 1 ]
 *  odd = head; //
 *  even = head->next; // nullptr;
 *
 *  [ 1, 2 ]
 *  odd = head; // 1
 *  even = head->next; // 2
 *
 *  [ 1, 2, 3 ]
 *  odd = head; // 1
 *  even = head->next; // 2
 *
 *  odd->next = even->next; // 3
 *  odd = odd->next; // 3
 *  even->next = odd->next; // nullptr
 *  even = even->next; // nullptr
 *
 *  odd->next = evenHead;
 *
 *  [ 1, 2, 3, 4 ]
 *  odd = head; // 1
 *  even = head->next; // 2
 *
 *  odd->next = even->next; // 3
 *  odd = odd->next; // 3
 *  even->next = odd->next; // 4
 *  even = even->next; // 4
 *
 *  odd->next = evenHead;
 *
 *  [ 1, 2, 3, 4, 5 ]
 *  odd = head; // 1
 *  even = head->next; // 2
 *
 *  odd->next = even->next; // 3
 *  odd = odd->next; // 3
 *  even->next = odd->next; // 4
 *  even = even->next; // 4
 *
 *  odd->next = even->next; // 5
 *  odd = odd->next; // 5
 *  even->next = odd->next; // nullptr
 *  even = even->next; // nullptr
 *
 *  odd->next = evenHead;
 *
 *  Time Complexity: O(n)
 *  Space Complexity: O(1)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include "../include/SinglyLinkedList.h"

class Solution {
public:
#ifdef BRUTE
    ListNode *oddEvenList(ListNode *head) {
        // Trivial rejection
        if (!head) {
            return head;
        }

        ListNode *even = head->next;
        ListNode *prevOdd = nullptr;
        ListNode *prevEven = nullptr;
        ListNode *node = head;
        ListNode *next;
        int count = 0;

        while (node) {
            next = node->next;
            if (count & 1) {
                // Even node
                if (prevEven) {
                    prevEven->next = node;
                }
                prevEven = node;
                prevEven->next = nullptr;   // Mark as end
            } else {
                // Odd node
                if (prevOdd) {
                    prevOdd->next = node;
                }
                prevOdd = node;
            }
            ++count;
            node = next;
        }

        prevOdd->next = even;

        // We know that head is always odd
        return head;
    }
#else
    ListNode *oddEvenList(ListNode *head) {
        // Trivial rejection
        if (!head) {
            return head;
        }

        ListNode *odd = head;
        ListNode *evenHead = head->next;
        ListNode *even = evenHead;

        while (even && even->next) {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }

        odd->next = evenHead;

        // We know that head is always odd
        return head;
    }
#endif /* BRUTE */
};

TEST_CASE("OddEvenLinkedList", "algorithm") {
    Solution soln;
    List testCase0{0};
    List testCase1{1, 0};
    List testCase2{1, 0, 2};
    List testCase3{1, 0, 2, 10};
    List testCase4{1, 2, 3, 4, 5};
    List testCase5{2, 1, 3, 5, 6, 4, 7};

    auto actual0 = List(soln.oddEvenList(testCase0.head)).toVector();
    auto actual1 = List(soln.oddEvenList(testCase1.head)).toVector();
    auto actual2 = List(soln.oddEvenList(testCase2.head)).toVector();
    auto actual3 = List(soln.oddEvenList(testCase3.head)).toVector();
    auto actual4 = List(soln.oddEvenList(testCase4.head)).toVector();
    auto actual5 = List(soln.oddEvenList(testCase5.head)).toVector();

    std::vector<int> expected0{0};
    std::vector<int> expected1{1, 0};
    std::vector<int> expected2{1, 2, 0};
    std::vector<int> expected3{1, 2, 0, 10};
    std::vector<int> expected4{1, 3, 5, 2, 4};
    std::vector<int> expected5{2, 3, 6, 7, 1, 5, 4};

    CHECK(actual0 == expected0);
    CHECK(actual1 == expected1);
    CHECK(actual2 == expected2);
    CHECK(actual3 == expected3);
    CHECK(actual4 == expected4);
    CHECK(actual5 == expected5);
}
