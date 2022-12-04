//
// Created by Benjamin Lee on 12/3/22.
// https://leetcode.com/problems/valid-parentheses/
//

/*
 * Stack is the best structure to use to solve this problem.
 * We need to prevent the interleaving of brace types, and this can be determined
 * when we choose to close a brace type by simply examining the top most element on the stack.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <stack>

class Solution {
public:
    bool isValid(std::string s) {
        std::stack<char> open;
        for (auto ch : s) {
            if (ch == '(' || ch == '[' || ch == '{') {
                open.push(ch);
            } else if (ch == ')') {
                if (open.size() && open.top() == '(') {
                    open.pop();
                } else {
                    return false;
                }
            } else if (ch == ']') {
                if (open.size() && open.top() == '[') {
                    open.pop();
                } else {
                    return false;
                }
            } else if (ch == '}') {
                if (open.size() && open.top() == '{') {
                    open.pop();
                } else {
                    return false;
                }
            } else {
                // Could do some form assert here, but spec indicates would only have bracket chars.
                // Just do nothing (or could have easily just omitted this).
            }
        }
        // Stack will be empty when successful
        return open.size() == 0;
    }
};

TEST_CASE("ValidParentheses", "algorithm") {
    Solution soln;
    std::string testCase0 = "()";
    std::string testCase1 = "()[]{}";
    std::string testCase2 = "(]";
    std::string testCase3 = "((())";
    std::string testCase4 = "([[{}]])";
    std::string testCase5 = "([[{}])";

    CHECK(soln.isValid(testCase0) == true);
    CHECK(soln.isValid(testCase1) == true);
    CHECK(soln.isValid(testCase2) == false);
    CHECK(soln.isValid(testCase3) == false);
    CHECK(soln.isValid(testCase4) == true);
    CHECK(soln.isValid(testCase5) == false);
}