//
// Created by Benjamin Lee on 12/17/22.
// https://leetcode.com/problems/evaluate-reverse-polish-notation/
//

/*
 * A stack is ideal for this. We push numbers onto the stack. When we hit an operator, we pop off the last two numbers,
 * apply the op, and then push back the results. The trick is managing the order by which they come off the stack.
 * op2 is first, then op1.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <stack>

class Solution {
    std::set<std::string> operators{"+", "-", "*", "/"};

public:
    int evalRPN(std::vector<std::string>& tokens) {
        std::stack<int64_t> items;

        for (auto item : tokens) {
            // Using set to be a little cleaner in code, so we can reuse
            if (operators.count(item)) {
                auto op2 = items.top();
                items.pop();
                auto op1 = items.top();
                items.pop();
                if (item == "+") {
                    items.push(op1 + op2);
                } else if (item == "-") {
                    items.push(op1 - op2);
                } else if (item == "*") {
                    items.push(op1 * op2);
                } else {
                    items.push(op1 / op2);
                }
            } else {
                items.push(std::stoll(item));
            }
        }

        return items.top();
    }
};

TEST_CASE("EvaluateReversePolishNotation", "algorithm") {
    Solution soln;
    std::vector<std::string> testCase0{"2", "1", "+"};
    std::vector<std::string> testCase1{"2", "1", "-"};
    std::vector<std::string> testCase2{"2", "1", "*"};
    std::vector<std::string> testCase3{"2", "1", "/"};
    std::vector<std::string> testCase4{"2", "1", "+", "3", "*"};
    std::vector<std::string> testCase5{"4", "13", "5", "/", "+"};
    std::vector<std::string> testCase6{"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
    std::vector<std::string> testCase7{"-128","-128","*","-128","*","-128","*","8","*","-1","*"};

    CHECK(soln.evalRPN(testCase7) == -2147483648);
    CHECK(soln.evalRPN(testCase0) == 3);
    CHECK(soln.evalRPN(testCase1) == 1);
    CHECK(soln.evalRPN(testCase2) == 2);
    CHECK(soln.evalRPN(testCase3) == 2);
    CHECK(soln.evalRPN(testCase4) == 9);
    CHECK(soln.evalRPN(testCase5) == 6);
    CHECK(soln.evalRPN(testCase6) == 22);
}