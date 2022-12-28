//
// Created by Benjamin Lee on 12/28/22.
// https://leetcode.com/problems/merge-k-sorted-lists/
// Hard
// Topic: Linke List, Divide and Conquer, Heap (Priority Queue), Merge Sort
//

/*
 * A brute force way would be to aggregate all values into a singular array, sort, and then re-create linked lists based
 * on this.
 *
 * Time Complexity: O(nlogn)
 * Space Complexity: O(3n) == O(n), O(n) for array, O(n) for sort, O(n) for new linked list
 *
 * Another way to approach this is to use a priority queue which is similar to the overall
 *
 * Time Complexity: O(nlogn)
 * Space Complexity: O(3n)
 *
 * Another brute force method would be to rebuild the new list by comparing every head node and adding the lowest value
 * node, progressing until we're done.
 *
 * Time Complexity: O(kn)
 * Space Complexity: O(n), for the new linked list
 *
 * There is a more optimal way to use the priority queue, by only focusing on the head elements of the lists
 *
 * Time Complexity: O(nlogk)
 * Space Complexity: O(n), O(n) for the list, O(k) for the sort, n typically > k
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <queue>
#include "../include/SinglyLinkedList.h"

class Solution {
public:
#ifdef BRUTE
    ListNode *mergeKLists(std::vector<ListNode *>& lists) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> queue;

        if (lists.empty()) {
            return {};
        }

        ListNode *head = nullptr;
        ListNode *node = nullptr;
        ListNode *last = nullptr;

        for (auto& list : lists) {
            node = list;

            // Connect the lists
            if (!head) head = node;
            if (last) last->next = node;

            while (node) {
                queue.push(node->val);
                last = node;
                node = node->next;
            }
        }

        node = head;
        while (node) {
            node->val = queue.top();
            queue.pop();
            node = node->next;
        }

        return head;
    }
#else
    struct ListNodePtrComparator {
        bool operator()(const ListNode *lhs, const ListNode *rhs) const {
            return lhs->val > rhs->val;
        }
    };

    ListNode *mergeKLists(std::vector<ListNode *>& lists) {
        std::priority_queue<ListNode *, std::vector<ListNode *>, ListNodePtrComparator> queue;
        ListNode *head = new ListNode(-1);  // Dummy holder
        ListNode *ref = head;

        if (lists.empty()) return {};   // Trivial rejection

        for (auto list: lists) {
            if (list) {
                queue.push(list);
            }
        }

        while (queue.size()) {
            auto node = queue.top();
            queue.pop();

            ref->next = new ListNode(node->val);
            ref = ref->next;

            node = node->next;
            if (node) {
                queue.push(node);
            }
        }
        return head->next;
    }
#endif /* BRUTE */
};

TEST_CASE("MergeKSortedLists", "algorithm") {
    Solution soln;
    List list0_0{1, 4, 5};
    List list1_0{1, 3, 4};
    List list2_0{2, 6};
    std::vector<ListNode *> testCase0{list0_0.head, list1_0.head, list2_0.head};
    std::vector<ListNode *> testCase1{};
    List list0_2{};
    List list1_2{1};
    std::vector<ListNode *> testCase2{list0_2.head, list1_2.head};

    List actual0(soln.mergeKLists(testCase0));
    List actual1(soln.mergeKLists(testCase1));
    List actual2(soln.mergeKLists(testCase2));

    CHECK(actual0.toVector() == std::vector<int>{1, 1, 2, 3, 4, 4, 5, 6});
    CHECK(actual1.toVector() == std::vector<int>{});
    CHECK(actual2.toVector() == std::vector<int>{1});
}

