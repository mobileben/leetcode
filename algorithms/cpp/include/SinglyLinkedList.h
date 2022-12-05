//
// Created by Benjamin Lee on 12/4/22.
//

#ifndef LEETCODE_SINGLYLINKEDLIST_H
#define LEETCODE_SINGLYLINKEDLIST_H

#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}

protected:
    friend bool operator==(const ListNode&, const ListNode&);
};

bool operator==(const ListNode& lhs, const ListNode& rhs) {
    return lhs.val == rhs.val;
}

struct List {
    ListNode *head;

    List() : head(nullptr) {}
    List(ListNode *head) : head(head) {}
    List(std::initializer_list<int> elements) : head(nullptr) {
        ListNode *curr = nullptr;
        for (auto elem : elements) {
            auto node = new ListNode(elem);
            if (!curr) {
                head = node;
            } else {
                curr->next = node;
            }
            curr = node;
        }
    }

    size_t size() const {
        size_t count = 0;
        auto node = head;
        while (node) {
            ++count;
            node = node->next;
        }
        return count;
    }

    void add(int x) {
        if (!head) {
            head = new ListNode(x);
        } else {
            auto node = head;
            while (node) {
                if (!node->next) {
                    node->next = new ListNode(x);
                    break;
                }
                node = node->next;
            }
        }
    }

    void print() {
        auto node = head;
        while (node) {
            std::cout << node -> val << " ";
            node = node->next;
        }
        std::cout << std::endl;
    }

    std::vector<int> toVector() const {
        std::vector<int> out;
        auto node = head;
        while (node) {
            out.push_back(node->val);
            node = node->next;
        }
        return out;
    }

protected:
    friend bool operator==(const List&, const List&);
};

bool operator==(const List& lhs, const List& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }

    auto lNode = lhs.head;
    auto rNode = rhs.head;
    while (lNode && rNode) {
        if (lNode->val != rNode->val) {
            return false;
        }
        lNode = lNode->next;
        rNode = rNode->next;
    }
    return true;
}

#endif //LEETCODE_SINGLYLINKEDLIST_H
