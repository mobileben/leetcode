//
// Created by Benjamin Lee on 12/4/22.
// https://leetcode.com/problems/middle-of-the-linked-list/
//

/*
 * Brute force method would be to do passes.
 * Pass 1 gets the size of the linked list
 * Pass 2 goes to the mid of the list
 *
 * Time Complexity: O(n + n/2) == O(n)
 * Space Complexity: O(1)
 *
 * An alternative to this is to use more space and to copy into a vector, and then return the mid
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * A more efficient way is to use two pointers where you have one fast and one slow pointer. If the fast pointer
 * traverses at twice the rate of the slow, when we reach the end, the slow pointer points to the mid
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include "../include/SinglyLinkedList.h"

class Solution {
public:
#ifdef BRUTE
    ListNode *middleNode(ListNode *head) {
        ListNode *node = head;
        int size = 0;
        if (!head->next) {
            return head;
        }
        while (node) {
            ++size;
            node = node->next;
        }
        int index = 0;
        int mid = size / 2;
        node = head;
        while (node) {
            if (index++ == mid) {
                return node;
            }
            node = node->next;
        }
        return nullptr;
    }
#else
    ListNode *middleNode(ListNode *head) {
        ListNode *fast = head;
        ListNode *slow = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
#endif /* BRUTE */
};

TEST_CASE("MiddleOfTheLinkedList", "algorithm") {
    Solution soln;
    List list0{1};
    List list1{1, 2};
    List list2{1, 2, 3};
    List list3{1, 2, 3, 4};
    List list4{1, 2, 3, 4, 5};
    List list5{1, 2, 3, 4, 5, 6};

    auto results1 = List(soln.middleNode(list1.head)).toVector();
    auto results0 = List(soln.middleNode(list0.head)).toVector();
    //auto results1 = List(soln.middleNode(list1.head)).toVector();
    auto results2 = List(soln.middleNode(list2.head)).toVector();
    auto results3 = List(soln.middleNode(list3.head)).toVector();
    auto results4 = List(soln.middleNode(list4.head)).toVector();
    auto results5 = List(soln.middleNode(list5.head)).toVector();

    auto expected0 = std::vector<int>{1};
    auto expected1 = std::vector<int>{2};
    auto expected2 = std::vector<int>{2, 3};
    auto expected3 = std::vector<int>{3, 4};
    auto expected4 = std::vector<int>{3, 4, 5};
    auto expected5 = std::vector<int>{4, 5, 6};

    CHECK(results0 == expected0);
    CHECK(results1 == expected1);
    CHECK(results2 == expected2);
    CHECK(results3 == expected3);
    CHECK(results4 == expected4);
    CHECK(results5 == expected5);
}

