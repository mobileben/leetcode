//
// Created by Benjamin Lee on 1/11/23.
// https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/
// Medium
// Topics: Hash Table, Tree, Depth-First Search, Breadth-First Search, Counting
//

/*
 * This is a graph traversal problem. We'll choose Depth-First Search as the search to use. A key detail to note
 * is that these are undirected graphs. This becomes important because a graph with edges defined as follows:
 *
 * {{0, 2}, {0, 3}, {1, 2}}
 *
 * if one was ignoring the unidirection, would look like
 *
 * 1   0
 *  \ / \
 *   2   3
 *
 * which is wrong, it actually looks like this
 *
 *     0
 *    / \
 *   2   3
 *  /
 * 1
 *
 * As we build our adjacency list, we need to add both edges to the adjacency list.
 *
 * Time Complexity: O(n), O(26n) -> O(n)
 * Space Complexity: O(n), O(26n) -> O(n)
 *
 * Breadth-First Search may also be employed here. When used, we will be moving bottom up, as opposed to top to bottom, as we traditionally do.
 * This way, as we move upwards, we can populate the results. To do this, we need to isolate all leafs. As we work upwards, we will be pruning our
 * leafs, which in turn will create more leafs that we will need to process.
 *
 * Time Complexity: O(n), O(26n) -> O(n)
 * Space Complexity: O(n), O(26n) -> O(n)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <map>
#include <set>
#include <queue>

#define BFS

class Solution {
public:
#ifdef DFS
std::vector<int> dfs(int node, int parent, std::map<int, std::vector<int>>& adj, std::string& labels, std::vector<int>& results) {
        std::vector<int> counts(26);

        // Our current node always has at least itself
        counts[labels[node] - 'a'] = 1;

        for (auto child : adj[node]) {
            if (child == parent) {
                continue;
            }
            auto totals = dfs(child, node, adj, labels, results);
            for (int i=0;i<26;++i) {
                counts[i] += totals[i];
            }
        }

        results[node] = counts[labels[node] - 'a'];
        return counts;
    }

    std::vector<int> countSubTrees(int n, std::vector<std::vector<int>>& edges, std::string labels) {
        std::map<int, std::vector<int>> adj;
        std::vector<int> results(n);

        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        dfs(0, -1, adj, labels, results);
        return results;
    }
#elifdef BFS
    std::vector<int> countSubTrees(int n, std::vector<std::vector<int>>& edges, std::string labels) {
        std::map<int, std::vector<int>> adj;
        std::queue<int> queue;
        std::vector<std::vector<int>> counts(n, std::vector<int>(26));

        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // Find all initial leafs. Leafs are nodes with only 1 item in its adjacency list
        for (int i=0;i<n;++i) {
            counts[i][labels[i] - 'a'] = 1;
            if (i != 0 and adj[i].size() == 1) {
                queue.push(i);
            }
        }

        while (queue.size()) {
            auto curr = queue.front();
            queue.pop();

            // These are leafs, so they will only have one item
            int parent = *adj[curr].begin();

            // prune
            auto& plist = adj[parent];
            auto it = std::find(plist.begin(), plist.end(), curr);
            adj[parent].erase(it);

            for (int i=0;i<26;++i) {
                counts[parent][i] += counts[curr][i];
            }

            // If our parent has turned into a leaf, add it to the queue
            if (parent != 0 and adj[parent].size() == 1) {
                queue.push(parent);
            }
        }

        std::vector<int> results(n);
        for (int i=0;i<n;++i) {
            results[i] = counts[i][labels[i] - 'a'];
        }
        return results;
    }
#endif /* DFS_RECURSIVE */
};

TEST_CASE("NumNodesInSubTreeWithSameLabel", "algorithm") {
    Solution soln;
    std::vector<std::vector<int>> edges0{{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}};
    std::string labels0 = "abaedcd";
    std::vector<std::vector<int>> edges1{{0, 1}, {1, 2}, {0, 3}};
    std::string labels1 = "bbbb";
    std::vector<std::vector<int>> edges2{{0, 2}, {0, 3}, {1, 2}};
    std::string labels2 = "aeed";

    CHECK(soln.countSubTrees(7, edges0, labels0) == std::vector<int>{2, 1, 1, 1, 1, 1, 1});
    CHECK(soln.countSubTrees(4, edges1, labels1) == std::vector<int>{4, 2, 1, 1});
    CHECK(soln.countSubTrees(4, edges2, labels2) == std::vector<int>{1, 1, 2, 1});
}