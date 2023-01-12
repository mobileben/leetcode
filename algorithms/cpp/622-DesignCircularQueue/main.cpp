//
// Created by Benjamin Lee on 1/11/23.
// https://leetcode.com/problems/design-circular-queue->
// Medium
// Topics: Array, Linked List, Design, Queue

/*
 * The brute force way is to have a head and tail pointer referencing the index into a std::vector.
 *
 * We can clean this up by tracking only count and capacity, and using modulus to reference the right index.
 *
 * Lastly, we could also use a singly linked list to implement the queue. If one opts for supporting singly linked lists
 * one will have to contend with memory management, which includes the costs of the allocation and deallocation. One
 * way around this is to have a static pool of list elements to draw from.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(n)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <cassert>

class MyCircularQueue {
public:
    static std::vector<std::string> execute(std::vector<std::string>& commands, std::vector<std::vector<int>>& args) {
        assert(commands.size() == args.size());

        std::vector<std::string> results;
        MyCircularQueue *queue = nullptr;
        for (int i = 0; i < commands.size(); ++i) {
            auto cmd = commands[i];
            int arg = args[i].size() ? args[i][0] : 0;

            if (cmd == "MyCircularQueue") {
                queue = new MyCircularQueue(arg);
                results.push_back("null");
            } else if (cmd == "enQueue") {
                if (queue->enQueue(arg)) {
                    results.push_back("true");
                } else {
                    results.push_back("false");
                }
            } else if (cmd == "deQueue") {
                if (queue->deQueue()) {
                    results.push_back("true");
                } else {
                    results.push_back("false");
                }
            } else if (cmd == "Front") {
                results.push_back(std::to_string(queue->Front()));
            } else if (cmd == "Rear") {
                results.push_back(std::to_string(queue->Rear()));
            } else if (cmd == "isEmpty") {
                if (queue->isEmpty()) {
                    results.push_back("true");
                } else {
                    results.push_back("false");
                }
            } else if (cmd == "isFull") {
                if (queue->isFull()) {
                    results.push_back("true");
                } else {
                    results.push_back("false");
                }
            } else {
                assert(false);
            }
        }

        if (queue) {
            delete queue;
        }

        return results;
    }

#ifdef BRUTE
private:
    std::vector<int> v;
    int head;
    int tail;
    int size;

public:
    MyCircularQueue(int k) : head(-1), tail(-1), size(k) {
        v.resize(k);
    }

    bool enQueue(int value) {
        if (head == -1) {
            head = tail = 0;
            v[head] = value;
        } else {
            int next = tail + 1;
            if (next >= size) {
                next -= size;
            }

            if (next == head) {
                return false;
            } else {
                tail = next;
                v[tail] = value;
            }
        }

        return true;
    }

    bool deQueue() {
        if (head == -1) {
            return false;
        } else if (head == tail) {
            head = tail = -1;
        } else {
            int next = head + 1;
            if (next >= size) {
                next -= size;
            }
            head = next;
        }

        return true;
    }

    int Front() {
        return head == -1 ? -1 : v[head];
    }

    int Rear() {
        return head == -1 ? -1 : v[tail];
    }

    bool isEmpty() {
        if (head == -1) {
            return true;
        }
        return false;
    }

    bool isFull() {
        if (head == -1) {
            return false;
        }

        if (tail >= head) {
            return (tail - head + 1) == size;
        } else {
            return (v.size() - head + tail + 1) == size;
        }
    }
#elifdef BETTER
private:
    std::vector<int> v;
    int head;
    int count;
    int capacity;

public:
    MyCircularQueue(int k) : head(0), count(0), capacity(k) {
        v.resize(k);
    }

    bool enQueue(int value) {
        if (count == capacity) {
            return false;
        }

        int index = (head + count) % capacity;
        v[index] = value;
        ++count;
        return true;
    }

    bool deQueue() {
        if (!count) {
            return false;
        }

        head = (head + 1) % capacity;
        --count;

        return true;
    }

    int Front() {
        return count == 0 ? -1 : v[head];
    }

    int Rear() {
        return count == 0 ? -1 : v[(head + count - 1) % capacity];
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }
#else
private:
    struct Node {
        int val;
        Node *next;

        Node(int val) : val(val), next(nullptr) {}
    };

    Node *head;
    Node *tail;
    int count;
    int capacity;

public:
    MyCircularQueue(int k) : head(nullptr), tail(nullptr), count(0), capacity(k) {
    }

    bool enQueue(int value) {
        if (count == capacity) {
            return false;
        }

        auto node = new Node(value);
        ++count;
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = tail->next;
        }

        return true;
    }

    bool deQueue() {
        if (count == 0) {
            return false;
        }

        --count;
        auto next = head->next;
        delete head;
        head = next;
        if (!head) {
            tail = nullptr;
        }

        return true;
    }

    int Front() {
        return head ? head->val : -1;
    }

    int Rear() {
        return tail ? tail->val : -1;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }
#endif /* BRUTE */
};

TEST_CASE("DesignCircularQueue", "algorithm") {
    std::vector<std::string> commands0{"MyCircularQueue", "enQueue", "enQueue", "enQueue", "enQueue", "Rear", "isFull", "deQueue", "enQueue", "Rear"};
    std::vector<std::vector<int>> args0{{3}, {1}, {2}, {3}, {4}, {}, {}, {}, {4}, {}};
    std::vector<std::string> commands1{"MyCircularQueue","enQueue","Rear","Rear","deQueue","enQueue","Rear","deQueue","Front","deQueue","deQueue","deQueue"};
    std::vector<std::vector<int>> args1{{6},{6},{},{},{},{5},{},{},{},{},{},{}};
    std::vector<std::string> commands2{"MyCircularQueue","enQueue","enQueue","deQueue","enQueue","deQueue","enQueue","deQueue","enQueue","deQueue", "Front"};
    std::vector<std::vector<int>> args2{{2},{1},{2},{},{3},{},{3},{},{3},{},{}};

    CHECK(MyCircularQueue::execute(commands0, args0) == std::vector<std::string>{"null", "true", "true", "true", "false", "3", "true", "true", "true", "4"});
    CHECK(MyCircularQueue::execute(commands1, args1) == std::vector<std::string>{"null", "true", "6", "6", "true", "true", "5", "true", "-1", "false", "false", "false"});
    CHECK(MyCircularQueue::execute(commands2, args2) == std::vector<std::string>{"null","true","true","true","true","true","true","true","true","true","3"});
}