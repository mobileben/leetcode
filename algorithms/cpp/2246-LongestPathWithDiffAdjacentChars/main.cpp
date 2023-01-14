//
// Created by Benjamin Lee on 1/13/23.
// https://leetcode.com/problems/longest-path-with-different-adjacent-characters/
// Hard
// Topics: Array, String, Tree, Depth-First Search, Graph, Topological Sort
//

/*
 * Depth-First Search is a good approach to solve this. When approaching this problem we can look at a few cases
 *
 * {-1}
 * "a"
 * This will result in 1: 0
 * 0-a
 *
 *
 * {-1, 0}
 * "aa"
 * This will result in 1: 0 or 1
 *
 *  0-a
 *  /
 * 1-a
 *
 * {-1, 0}
 * "ab"
 * This will result in 2: 1 - 0
 *  0-a
 *  /
 * 1-b
 *
 * {-1, 0, 0}
 * "aab"
 * This will result in 2: 2-0
 *
 *  0-a
 *  /  \
 * 1-a 2-b
 *
 * {-1, 0, 0}
 * "abb"
 * This will result in 3: 1 - 0 - 2
 *
 *  0-a
 *  /  \
 * 1-a 2-b
 *
 * {-1, 0, 0, 1}
 * "abbc"
 * This will result in 4: 3 - 1 - 0 - 2
 *    0-a
 *    / \
 *  1-b 2-b
 *  /
 * 3-c
 *
 * {-1, 0, 0, 1, 3, 3}
 * "aaebcd"
 * This will result in 5: 4 - 3 - 1 - 0 - 2
 *      0-a
 *      / \
 *    1-d 2-e
 *    /
 *  3-b
 *  /  \
 * 4-e 5-d
 *
 * What we can see is that the longest path is actually dependent on the 2 longest legs/paths/chains. This means to
 * solve, we want to determine the top 2 legs (if applicable)
 *
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <unordered_map>

class Solution {
public:
    int dfs(int node, int& max, std::unordered_map<int, std::vector<int>>& adj, std::string& s) {
        int max1 = 0;   // Max leg
        int max2 = 0;   // Next to max leg

        for (auto child : adj[node]) {
            auto leg = dfs(child, max, adj, s);

            // If we are the same node as our parents, we no longer contribute to the leg
            if (s[child] == s[node]) {
                continue;
            }

            if (leg > max1) {
                max2 = max1;
                max1 = leg;
            } else if (leg > max2) {
                max2 = leg;
            }
        }

        int longest = max1 + max2 + 1;
        if (longest > max) {
            max = longest;
        }

        return max1 + 1;
    }

    int longestPath(std::vector<int>& parent, std::string s) {
        std::unordered_map<int, std::vector<int>> adj;
        int max = 0;

        for (int i=1;i<parent.size();++i) {
            adj[parent[i]].push_back(i);
        }

        dfs(0, max, adj, s);
        return max;
    }
};

TEST_CASE("LongestPathWithDiffAdjacentChars", "algorithm") {
    Solution soln;
    std::vector<int> parent0{-1, 0, 0, 1, 1, 2};
    std::string s0 = "abacbe";
    std::vector<int> parent1{-1, 0, 0, 0};
    std::string s1 = "aabc";
    std::vector<int> parent2{-1, 0, 1};
    std::string s2 = "aab";
    std::vector<int> parent3{-1};
    std::string s3 = "a";
    std::vector<int> parent4{-1, 0, 0, 1, 3, 3};
    std::string s4 = "aaebcd";
    std::vector<int> parent5{-1, 0, 0, 1, 3, 3, 4, 5};
    std::string s5 = "aaebcdfg";
    std::vector<int> parent6{-1, 0};
    std::string s6 = "aa";
    std::vector<int> parent7{-1, 0};
    std::string s7 = "ab";

    CHECK(soln.longestPath(parent0, s0) == 3);
    CHECK(soln.longestPath(parent1, s1) == 3);
    CHECK(soln.longestPath(parent2, s2) == 2);
    CHECK(soln.longestPath(parent3, s3) == 1);
    CHECK(soln.longestPath(parent4, s4) == 3);
    CHECK(soln.longestPath(parent5, s5) == 5);
    CHECK(soln.longestPath(parent6, s6) == 1);
    CHECK(soln.longestPath(parent7, s7) == 2);
}
