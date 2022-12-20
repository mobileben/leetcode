//
// Created by Benjamin Lee on 12/18/22.
// https://leetcode.com/problems/find-if-path-exists-in-graph/
//

/*
 * This is graph traversal. So we use either Breadth First Search or Depth First Search to solve this. Both can be done
 * recursively or iteratively.
 *
 * With Breadth First Search, we search all nodes at a given depth first, then proceed downwards.
 *
 * With Depth First Search, we descend downwards as much as possible before backtracking to the children nodes we
 * didn't visit.
 *
 * In both cases, we want to skip nodes we've already seen.
 *
 * To help visualize each, we can take the simple case of the following edge data
 * [ [0, 1], [0, 5], [1, 2], [1, 3], [5, 4] [4, 8] ]
 *
 * We will an adjaceny list that looks like the following. Note we are bi-directional
 *
 * 0 : [ 1, 5 ]
 * 1 : [ 0, 2, 3 ]
 * 2 : [ 1 ]
 * 3 : [ 1 ]
 * 4 : [ 5 ]
 * 5 : [ 4, 8 ]
 * 8 : [ 5 ]
 *
 * This will visually look like
 *
 *          0
 *        /    \
 *       1       5
 *      / \     / \
 *     2   3   4   8
 *
 * For BFS, we use a queue. Breadth first search goes through all the nodes at a layer, so the queue would look like
 *
 * [ 0, 1, 5, 2, 3, 4, 8 ]
 *
 * When filled and not drained. However, operation wise it would look like
 *
 * queue: [ 0 ]
 * op: pop 0
 * queue: [ 1 5 ]
 * op: pop 1
 * queue: [ 5 2 3 ]
 * op: pop 5
 * queue: [ 2 3 4 8 ]
 * op: pop 2
 * queue: [ 3 4 8 ]
 * op: pop 3
 * queue: [ 4 8 ]
 * op: pop 4
 * queue: [ 8 ]
 * op: pop 8
 *
 * For DFS, we use a stack. Depth first search goes through to the bottom. Unlike the queue, we have to look at the stack
 * and ops, as we cannot see the fully filled stack, because popping the stack removes the last item
 *
 * stack: [ 0 ]
 * op: pop 0, push 1, push 5
 * stack: [ 1, 5 ]
 * op: pop 5, push 4, 8
 * stack: [ 1, 4, 8 ]
 * op: pop 8 (bottom)
 * stack: [ 1, 4 ]
 * op: pop 4 (bottom)
 * stack: [ 1 ]
 * op: pop 1, push 2, push 3
 * stack [ 2, 3 ]
 * op: pop 3
 * stack: [ 2 ]
 * op: pop 2
 *
 *
 * Time Complexity: O(v + e) where v is num of verts and e is number of edges. We have time from building the graph
 * from e edges and then traversing v nodes, where we only see each node once
 * Space Complexity: O(v + e) where we have a hashmap of e edges and a seen vector of v length
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <map>
#include <stack>
#include <queue>

class Solution {
public:
    // This is non-recursive, but built out in a method so this file can contain both BFS and DFS
    bool bfs(std::map<int, std::vector<int>>& graph, int source, int destination) {
        std::vector<bool> seen(graph.size());
        std::queue<int> queue;

        queue.push(source);

        while (queue.size()) {
            auto curr = queue.front();
            queue.pop();
            if (curr == destination) {
                return true;
            }

            auto &children = graph[curr];
            for (auto child : children) {
                if (!seen[child]) {
                    seen[child] = true;
                    queue.push(child);
                }
            }
        }
        return false;
    }

    bool dfsIterative(std::map<int, std::vector<int>>& graph, int source, int destination) {
        std::vector<bool> seen(graph.size());
        std::stack<int> stack;

        stack.push(source);

        while (stack.size()) {
            auto curr = stack.top();
            stack.pop();

            if (curr == destination) {
                return true;
            }

            auto& children = graph[curr];
            for (auto child : children) {
                if (!seen[child]) {
                    seen[child] = true;
                    stack.push(child);
                }
            }
        }

        return false;
    }

    bool dfsRecursive(std::map<int, std::vector<int>>& graph, std::vector<bool>& seen, int source, int destination) {
        if (source == destination) {
            return true;
        }

        if (!seen[source]) {
            seen[source] = true;
            auto& children = graph[source];
            for (auto child : children) {
                if (dfsRecursive(graph, seen, child, destination)) {
                    return true;
                }
            }
        }

        return false;
    }

    bool validPath(int n, std::vector<std::vector<int>>& edges, int source, int destination) {
        std::map<int, std::vector<int>> graph;

        for (auto &it : edges) {
            auto node0 = it[0], node1 = it[1];
            graph[node0].push_back(node1);
            graph[node1].push_back(node0);
        }

#ifdef BFS
        return bfs(graph, source, destination);
#elif defined(DFS_ITERATIVE)
        return dfsIterative(graph, source, destination);
#else
        std::vector<bool> seen(graph.size());
        return dfsRecursive(graph, seen, source, destination);
#endif /* BFS */
    }
};

TEST_CASE("FindIfPathExistsInGraph", "algorithm") {
    Solution soln;
    std::vector<std::vector<int>> testCase0{{0, 1}, {1, 2}, {2, 0}};
    std::vector<std::vector<int>> testCase1{{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}};
    std::vector<std::vector<int>> testCase2{{4,3}, {1,4}, {4,8}, {1,7}, {6,4}, {4,2}, {7,4}, {4,0}, {0,9}, {5,4}};

    CHECK(soln.validPath(3, testCase0, 0, 2) == true);
    CHECK(soln.validPath(6, testCase1, 0, 5) == false);
    CHECK(soln.validPath(10, testCase2, 5, 9) == true);
}

