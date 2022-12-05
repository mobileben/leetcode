//
// Created by Benjamin Lee on 12/4/22.
// https://leetcode.com/problems/merge-two-sorted-lists/
//

/*
 * It isn't clear from the requirements if we are allowed to permute the existing lists. We are going to treat it as
 * such, as if we do not, it will incur the overhead of memory allocation;
 *
 * Time Complexity(n+m)
 * Space Complexity: O(1)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include "../include/SinglyLinkedList.h"

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        // Trivial rejection
        if (list1 == nullptr) {
            return list2;
        } else if (list2 == nullptr) {
            return list1;
        }

        ListNode placeholder{-1};
        ListNode *prev = &placeholder; // Utilize a prev pointer to provide the node to connect to

        while (list1 && list2) {
            if (list1->val <= list2->val) {
                prev->next = list1;
                list1 = list1->next;
            } else {
                prev->next = list2;
                list2 = list2->next;
            }
            prev = prev->next;
        }
        // list1 or list2 may still have some nodes left. One list may be exhausted before the other.
        // Append the remainder, if any
        prev->next = list1 == nullptr ? list2 : list1;
        return placeholder.next;
    }
};

TEST_CASE("MergeTwoSortedLists", "algorithm") {
    Solution soln;
    List list1_0{1, 2, 4};
    List list2_0{1, 3, 4};
    List list1_1{};
    List list2_1{0};
    List list1_2{};
    List list2_2{};
    List list1_3{0};
    List list2_3{};
    List list1_4{1, 3, 4};
    List list2_4{1, 2, 4};

    std::vector<int> soln0{1, 1, 2, 3, 4, 4};
    std::vector<int> soln1{0};
    std::vector<int> soln2{};
    std::vector<int> soln3{0};
    std::vector<int> soln4{1, 1, 2, 3, 4, 4};

    auto merged0 = List(soln.mergeTwoLists(list1_0.head, list2_0.head));
    auto results0 = merged0.toVector();
    auto merged1 = List(soln.mergeTwoLists(list1_1.head, list2_1.head));
    auto results1 = merged1.toVector();
    auto merged2 = List(soln.mergeTwoLists(list1_2.head, list2_2.head));
    auto results2 = merged2.toVector();
    auto merged3 = List(soln.mergeTwoLists(list1_3.head, list2_3.head));
    auto results3 = merged3.toVector();
    auto merged4 = List(soln.mergeTwoLists(list1_4.head, list2_4.head));
    auto results4 = merged4.toVector();
    CHECK(results0 == soln0);
    CHECK(results1 == soln1);
    CHECK(results2 == soln2);
    CHECK(results3 == soln3);
    CHECK(results4 == soln4);
}