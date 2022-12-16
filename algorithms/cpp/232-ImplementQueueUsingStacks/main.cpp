//
// Created by Benjamin Lee on 12/15/22.
// https://leetcode.com/problems/implement-queue-using-stacks/
//

/*
 * A queue is a FIFO structure. When we pop, it pops the first element in the queue.
 * A stack is a LIFO structure. When we pop, it pops the last item in the queue.
 *
 * Two stacks can be used to solve this.
 *
 * During a push, we move all items in master into temp. We add the new item to master, and then copy over all elements
 * back into master.
 *
 * We can think of Time and Space Complexity per op.
 *
 * push:
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * pop:
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <stack>
class MyQueue {
    std::stack<int> master;
    std::stack<int> temp;

public:
    MyQueue() {
    }

    void push(int x) {
        // Drain master to temp
        while(master.size()) {
            temp.push(master.top());
            master.pop();
        }

        master.push(x);

        while(temp.size()) {
            master.push(temp.top());
            temp.pop();
        }
    }

    int pop() {
        auto val = master.top();
        master.pop();
        return val;
    }

    int peek() {
        return master.top();
    }

    bool empty() {
        return master.empty();
    }
};

std::vector<std::string> process(std::vector<std::string> seq, std::vector<std::vector<int>>& values) {
    std::vector<std::string> results;

    // First one is always constructor
    MyQueue queue;
    results.push_back("null");

    for (int i=1;i<seq.size();++i) {
        auto cmd = seq[i];
        auto val = values[i];
        if (cmd == "push") {
            queue.push(val.front());
            results.push_back("null");
        } else if (cmd == "pop") {
            results.push_back(std::to_string(queue.pop()));
        } else if (cmd == "peek") {
            results.push_back(std::to_string(queue.peek()));
        } else { // empty
            results.push_back(queue.empty() ? "true" : "false");
        }
    }

    return results;

}

TEST_CASE("ImplementQueueUsingStacks", "algorithm") {
    std::vector<std::string> seq0{"MyQueue", "empty", "push", "peek", "empty", "pop", "empty"};
    std::vector<std::vector<int>> values0{{}, {}, {1}, {}, {}, {}, {}};
    std::vector<std::string> seq1{"MyQueue", "push", "push", "pop", "pop", "push", "push", "peek", "empty"};
    std::vector<std::vector<int>> values1{{}, {1}, {2}, {}, {}, {3}, {4}, {}, {}};
    std::vector<std::string> seq2{"MyQueue", "push", "push", "peek", "pop", "empty"};
    std::vector<std::vector<int>> values2{{}, {1}, {2}, {}, {}, {}};
    std::vector<std::string> seq3{"MyQueue", "push", "push", "peek", "pop", "empty"};
    std::vector<std::vector<int>> values3{{}, {1}, {2}, {}, {}, {}};
    std::vector<std::string> seq4{"MyQueue", "push", "push", "peek", "pop", "empty"};
    std::vector<std::vector<int>> values4{{}, {1}, {2}, {}, {}, {}};
    std::vector<std::string> seq5{"MyQueue", "push", "push", "peek", "pop", "empty"};
    std::vector<std::vector<int>> values5{{}, {1}, {2}, {}, {}, {}};

    CHECK(process(seq0, values0) == std::vector<std::string>{"null", "true", "null", "1", "false", "1", "true"});
    CHECK(process(seq1, values1) == std::vector<std::string>{"null", "null", "null", "1", "2", "null", "null", "3", "false"});
    CHECK(process(seq2, values2) == std::vector<std::string>{"null", "null", "null", "1", "1", "false"});
    CHECK(process(seq3, values3) == std::vector<std::string>{"null", "null", "null", "1", "1", "false"});
    CHECK(process(seq4, values4) == std::vector<std::string>{"null", "null", "null", "1", "1", "false"});
    CHECK(process(seq5, values5) == std::vector<std::string>{"null", "null", "null", "1", "1", "false"});
}


