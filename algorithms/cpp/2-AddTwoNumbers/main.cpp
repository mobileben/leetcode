//
// Created by Benjamin Lee on 12/6/22.
// https://leetcode.com/problems/add-two-numbers/
//

/*
 *  Both numbers are stored in reverse order in a linked list.
 *  The instructions are not clear if you can cannibalize existing ListNodes, but we will be doing so.
 *
 *  The brute/naive approach would be to convert into numbers, add them, then put it back into a linked list.
 *  However,  the max number of nodes is 100 (range is [1, 100]). Thus this will
 *  go beyond. Hence, this solution is not valid.
 *
 *  Thus the process is to go through each digit and manage the carries.
 *
 *  Time Complexity: O(max(n, m))
 *  Space Complexity: O(max(n, m))
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include "../include/SinglyLinkedList.h"

class Solution {
public:
    ListNode *addTwoNumbers(ListNode * l1, ListNode *l2) {
        int sum, carry = 0;
        int v1 = 0, v2 = 0;
        ListNode *node1 = l1, *node2 = l2;
        ListNode *head = new ListNode{0};
        ListNode *last = head;

        while (node1 || node2) {
            if (node1) {
                v1 = node1->val;
                node1 = node1->next;
            } else {
                v1 = 0;
            }
            if (node2) {
                v2 = node2->val;
                node2 = node2->next;
            } else {
                v2 = 0;
            }

            sum = v1 + v2 + carry;
            carry = sum >= 10; // Could also use `carry = sum / 10`
            if (carry) {
                sum -= 10; // Could also forgo this and later use `sum % 10`
            }

            last = last->next = new ListNode{sum};
        }

        if (carry) {
            last = last->next = new ListNode{1};
        }

        return head->next;
    }
};

TEST_CASE("AddTwoNumbers", "algorithm") {
    Solution soln;
    List testCaseA0{0};
    List testCaseB0{0};
    List testCaseA1{0};
    List testCaseB1{1};
    List testCaseA2{1};
    List testCaseB2{0};
    List testCaseA3{0, 0, 1};
    List testCaseB3{3, 4, 5};
    List testCaseA4{2, 4, 3};
    List testCaseB4{5, 6, 4};
    List testCaseA5{9, 9, 9, 9, 9, 9, 9};
    List testCaseB5{9, 9, 9 , 9};
    List testCaseA6{9, 9, 9 , 9};
    List testCaseB6{9, 9, 9, 9, 9, 9, 9};
    List testCaseA7{9};
    List testCaseB7{1, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    List testCaseA8{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
    List testCaseB8{5,6,4};

    List actual0 = List(soln.addTwoNumbers(testCaseA0.head, testCaseB0.head));
    List actual1 = List(soln.addTwoNumbers(testCaseA1.head, testCaseB1.head));
    List actual2 = List(soln.addTwoNumbers(testCaseA2.head, testCaseB2.head));
    List actual3 = List(soln.addTwoNumbers(testCaseA3.head, testCaseB3.head));
    List actual4 = List(soln.addTwoNumbers(testCaseA4.head, testCaseB4.head));
    List actual5 = List(soln.addTwoNumbers(testCaseA5.head, testCaseB5.head));
    List actual6 = List(soln.addTwoNumbers(testCaseA6.head, testCaseB6.head));
    List actual7 = List(soln.addTwoNumbers(testCaseA7.head, testCaseB7.head));
    List actual8 = List(soln.addTwoNumbers(testCaseA8.head, testCaseB8.head));

    List expected0{0};
    List expected1{1};
    List expected2{1};
    List expected3{3, 4, 6};
    List expected4{7, 0, 8};
    List expected5{8, 9, 9, 9, 0, 0, 0, 1};
    List expected6{8, 9, 9, 9, 0, 0, 0, 1};
    List expected7{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    List expected8{6,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};

    CHECK(actual0 == expected0);
    CHECK(actual1 == expected1);
    CHECK(actual2 == expected2);
    CHECK(actual3 == expected3);
    CHECK(actual4 == expected4);
    CHECK(actual5 == expected5);
    CHECK(actual6 == expected6);
    CHECK(actual7 == expected7);
    CHECK(actual8 == expected8);

}