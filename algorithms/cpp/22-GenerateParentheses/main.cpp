//
// Created by Benjamin Lee on 12/11/22.
// https://leetcode.com/problems/generate-parentheses/description/
//

/*
 * Pure brute force, which will no doubt cause TLE would be to find every combination of parens, picking out ones which
 * are valid.
 *
 * Time Complexity: O(2^2n * n)
 * Space Complexity: O(2^2n * n)
 *
 * Backtracking is a good way to do approach this. We can look at establishing a couple of rules for this.
 * - n open parens, n close parens
 * - We can add a close when close < open
 *
 * We can then descend downwards and try and add an open in one path, and add a close in another path (this makes a tree)
 *
 * This then translates to
 * - Add open if open < n
 * - Add close if close < open
 * - Has combination if open == closed == n
 *
 * Time Complexity: O(4^n / sqrt(n)). This is the nth Catalan number
 * Space Complexity: O(4^n / sqrt(n))
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
    void backtrack(int open, int close, int n, std::string& stack, std::vector<std::string>& results) {
        if (open == close && open == n) {
            results.push_back(stack);
            return;
        }

        if (open < n) {
            stack.push_back('(');
            backtrack(open + 1, close, n, stack, results);
            stack.pop_back();
        }

        if (close < open) {
            stack.push_back(')');
            backtrack(open, close + 1, n, stack, results);
            stack.pop_back();
        }
    }

    std::vector<std::string> generateParenthesis(int n) {
        std::string stack;
        std::vector<std::string> results;
        backtrack(0, 0, n, stack, results);
        return results;
    }
};

TEST_CASE("GenerateParentheses", "algorithm") {
    Solution soln;
    std::vector<std::string> actual1 = soln.generateParenthesis(2);
    std::vector<std::string> actual0 = soln.generateParenthesis(1);
    std::vector<std::string> actual2 = soln.generateParenthesis(3);
    std::vector<std::string> actual3 = soln.generateParenthesis(4);
    std::vector<std::string> actual4 = soln.generateParenthesis(5);

    std::vector<std::string> expected0{"()"};
    std::vector<std::string> expected1{"(())","()()"};
    std::vector<std::string> expected2{"((()))","(()())","(())()","()(())","()()()"};
    std::vector<std::string> expected3{"(((())))","((()()))","((())())","((()))()","(()(()))","(()()())","(()())()","(())(())","(())()()","()((()))","()(()())","()(())()","()()(())","()()()()"};
    std::vector<std::string> expected4{"((((()))))","(((()())))","(((())()))","(((()))())","(((())))()","((()(())))","((()()()))","((()())())","((()()))()","((())(()))","((())()())","((())())()","((()))(())","((()))()()","(()((())))","(()(()()))","(()(())())","(()(()))()","(()()(()))","(()()()())","(()()())()","(()())(())","(()())()()","(())((()))","(())(()())","(())(())()","(())()(())","(())()()()","()(((())))","()((()()))","()((())())","()((()))()","()(()(()))","()(()()())","()(()())()","()(())(())","()(())()()","()()((()))","()()(()())","()()(())()","()()()(())","()()()()()"};

    CHECK(actual0 == expected0);
    CHECK(actual1 == expected1);
    CHECK(actual2 == expected2);
    CHECK(actual3 == expected3);
    CHECK(actual4 == expected4);
}

