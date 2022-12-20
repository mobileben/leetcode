//
// Created by Benjamin Lee on 12/19/22.
// https://leetcode.com/problems/keys-and-rooms/
//

/*
 * This really is a graph traversal problem. One can think of as the array being passed in as an adjacency list.
 *
 * As this is graph traversal, we can solve this using BFS or DFS.
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <stack>
#include <queue>

class Solution {
public:
    bool bfs(std::vector<std::vector<int>>& graph) {
        std::vector<bool> seen(graph.size());
        std::queue<int> queue;

        queue.push(0);
        seen[0] = true;

        while(queue.size()) {
            auto curr = queue.front();
            queue.pop();

            auto& children = graph[curr];
            for(auto& child : children) {
                if (!seen[child]) {
                    seen[child] = true;
                    queue.push(child);
                }
            }
        }

        for (auto n : seen) {
            if (!n) {
                return false;
            }
        }

        return true;
    }

    bool dfsIterative(std::vector<std::vector<int>>& graph) {
        std::vector<bool> seen(graph.size());
        std::stack<int> stack;

        stack.push(0);
        seen[0] = true;

        while(stack.size()) {
            auto curr = stack.top();
            stack.pop();

            auto& children = graph[curr];
            for(auto& child : children) {
                if (!seen[child]) {
                    seen[child] = true;
                    stack.push(child);
                }
            }
        }

        for (auto n : seen) {
            if (!n) {
                return false;
            }
        }

        return true;
    }

    void dfsRecursive(std::vector<std::vector<int>>& graph, int room, std::vector<bool>& seen) {
        if (!seen[room]) {
            seen[room] = true;
            auto& children = graph[room];
            for(auto& child : children) {
                dfsRecursive(graph, child, seen);
            }
        }
    }

    bool canVisitAllRooms(std::vector<std::vector<int>>& rooms) {
#ifdef BFS
        return bfs(rooms);
#elif defined(DFS_ITERATIVE)
        return dfsIterative(rooms);
#else
        std::vector<bool> seen(rooms.size());
        dfsRecursive(rooms, 0, seen);
        for (auto n : seen) {
            if (!n) {
                return false;
            }
        }

        return true;
#endif /* BFS */
    }
};

TEST_CASE("KeysAndRooms", "algorithm") {
    Solution soln;
    std::vector<std::vector<int>> testCase0{ { 1 }, { 2 }, { 3 }, {} };
    std::vector<std::vector<int>> testCase1{ { 1, 3 }, { 3, 0, 1 }, { 2 }, { 0 } };

    CHECK(soln.canVisitAllRooms(testCase0) == true);
    CHECK(soln.canVisitAllRooms(testCase1) == false);
}
