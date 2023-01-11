//
// Created by Benjamin Lee on 1/10/23.
// https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/
// Medium
// Topics: Hash Table, Tree, Depth-First Search, Breadth-First Search
//

/*
 * What we can observe from our traversal
 *
 *      0
 *    /   \
 *   1     2
 *  / \   /  \
 * 4   5 3    6
 *
 * In this case, 0 is our only apple, the time would be 0.
 *
 *      0
 *    /   \
 *   1     2
 *  / \   /  \
 * 4   5 3    6
 *
 * In this case, if 1 is our only apple, then our time would be 2, which would be 0->1 then 1->0
 *
 *      0
 *    /   \
 *   1     2
 *  / \   /  \
 * 4   5 3    6
 *
 * In this case, if 4 is our only apple, then our time would be 4, which would be 0->1, 1-4, 4->1, and then 1->0.
 * We can see a pattern here, where each unit contributes 2 ticks. In this case here, we know that 1->4 and 4->1 give us
 * 2 ticks. We will "realize" this when we process node 4. The question is how do we then percolate this upwards? We need
 * a way for 1 to recognize it has to contribute to time.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <map>
#include <stack>

class Solution {
public:
    int dfs(int node, int parent, std::map<int, std::vector<int>>& adjacency, std::vector<bool>& hasApple) {
        int time = 0;
        for (auto child : adjacency[node]) {
            if (child == parent) {
                continue;
            }
            auto ctime = dfs(child, node, adjacency, hasApple);
            // ctime > 0 when our child has an apple OR if a sub-child has an apple, we need to add 2 for the back and
            // forth.
            if (ctime || hasApple[child]) {
                time += ctime + 2;
            }
        }
        return time;
    }

    int minTime(int n, std::vector<std::vector<int>>& edges, std::vector<bool> hasApple) {
        std::map<int, std::vector<int>> adjacency;

        for (auto& edge : edges) {
            adjacency[edge[0]].push_back(edge[1]);
            adjacency[edge[1]].push_back(edge[0]);
        }

        return dfs(0, -1, adjacency, hasApple);
    }
};

TEST_CASE("MinimumTimeToCollectApples", "algorithm") {
    Solution soln;
    std::vector<std::vector<int>> edges0{{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}};
    std::vector<bool> hasApples0{false, false, true, false, true, true, false};
    std::vector<std::vector<int>> edges1{{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}};
    std::vector<bool> hasApples1{false, false, true, false, false, true, false};
    std::vector<std::vector<int>> edges2{{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}};
    std::vector<bool> hasApples2{false, false, false, false, false, false, false};
    std::vector<std::vector<int>> edges3{{0, 2}, {0, 3}, {1, 3}};
    std::vector<bool> hasApples3{false, true, false, false};

    CHECK(soln.minTime(7, edges0, hasApples0) == 8);
    CHECK(soln.minTime(7, edges1, hasApples1) == 6);
    CHECK(soln.minTime(7, edges2, hasApples2) == 0);
    CHECK(soln.minTime(4, edges3, hasApples3) == 4);
}