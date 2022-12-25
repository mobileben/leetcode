//
// Created by Benjamin Lee on 12/21/22.
// https://leetcode.com/problems/possible-bipartition/
//

/*
 * The dislikes vector is defines a graph. This becomes a graph traversal problem, which leads us to using BFS or DFS.
 * The trick to this however is also to bucket nodes. There will be 2 nodes. If a node ends up being in the same group
 * as it's parent, then we cannot bipartition everyone
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <map>
#include <stack>
#include <queue>

class Solution {
public:
    bool bfs(int node, std::vector<int>& groups, std::map<int, std::vector<int>>& graph) {
        std::queue<int> queue;

        queue.push(node);
        groups[node] = 0;

        while(queue.size()) {
            node = queue.front();
            queue.pop();

            auto other = groups[node] ^ 1;

            auto& children = graph[node];
            for (auto child : children) {
                auto group = groups[child];

                if (group == -1) {
                    groups[child] = other;
                    queue.push(child);
                } else if (group != other) {
                    return false;
                }
            }
        }

        return true;
    }

    bool dfs(int node, std::vector<int>& groups, std::map<int, std::vector<int>>& graph) {
        std::stack<int> stack;

        stack.push(node);
        groups[node] = 0;

        while (stack.size()) {
            auto node = stack.top();
            stack.pop();

            auto other = groups[node] ^ 1;

            auto& children = graph[node];
            for (auto child : children) {
                auto group = groups[child];
                if (group == -1) {
                    groups[child] = other;
                    stack.push(child);
                } else if (group != other) {
                    return false;
                }
            }
        }
        return true;
    }

    bool possibleBipartition(int n, std::vector<std::vector<int>>& dislikes) {
        std::map<int, std::vector<int>> graph;
        std::vector<int> groups(n, -1);

        for (auto& children : dislikes) {
            // We know that it is always a pair
            auto p0 = children.front();
            auto p1 = children.back();

            // p0 doesn't like p1
            // int value start at 1,not 0, so convert to 0 index
            graph[p0-1].push_back(p1-1);
            graph[p1-1].push_back(p0-1);
        }

        // Start with first person found
        for (int i=0;i<n;++i) {
            if (groups[i] == -1) {
#ifdef BFS
                if (!bfs(i, groups, graph)) {
                    return false;
                }
#else
                if (!dfs(i, groups, graph)) {
                    return false;
                }
#endif /* BFS */
            }
        }
        return true;
    }
};

TEST_CASE("PossibleBipartition", "algorithm") {
    Solution soln;
    std::vector<std::vector<int>> testCase0{{1, 2}, {1, 3}, {2, 4}};
    std::vector<std::vector<int>> testCase1{{1, 2}, {1, 3}, {2, 3}};
    std::vector<std::vector<int>> testCase2{{1, 2}, {2, 3}, {3, 4}, {4, 5}, {1, 5}};
    std::vector<std::vector<int>> testCase3{{1, 2}, {3, 4}, {4, 5}, {3, 5}};
    std::vector<std::vector<int>> testCase4{{1, 2}, {3, 4}, {4, 6}, {3, 5}};
    std::vector<std::vector<int>> testCase5{{4, 7}, {4, 8}, {5, 6}, {1, 6}, {3, 7}, {2, 5}, {5, 8}, {1, 2}, {4, 9}, {6, 10}, {8, 10}, {3, 6}, {2, 10}, {9, 10}, {3, 9}, {2, 3}, {1, 9}, {4, 6}, {5, 7}, {3, 8}, {1, 8}, {1, 7}, {2, 4}};

    CHECK(soln.possibleBipartition(5, testCase3) == false);
    CHECK(soln.possibleBipartition(4, testCase0) == true);
    CHECK(soln.possibleBipartition(3, testCase1) == false);
    CHECK(soln.possibleBipartition(5, testCase2) == false);
    CHECK(soln.possibleBipartition(6, testCase4) == true);
    CHECK(soln.possibleBipartition(10, testCase5) == true);
}
