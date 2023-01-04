//
// Created by Benjamin Lee on 12/29/22.
// https://leetcode.com/problems/single-threaded-cpu/
// Medium
// Topics: Array, Sorting, Priority Queue
//

/*
 * First create a vector holding the indices, then sort. One could use a std::pair instead to hold duration and index
 * For each task, figure out the current time, then add the next tasks
 *
 * Time Complexity: O(nlogn) = O(n) for filling in the vector, O(nlogn) for the initial sort, and N * O(logn) for
 * priority queue == O(n + nlogn + nlogn) == O(nlogn)
 * Space Complexity: O(n)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <queue>

class Solution {
public:
    std::vector<int> getOrder(std::vector<std::vector<int>>& tasks) {
        // Trivial rejection
        if (tasks.empty()) {
            return {};
        } else if (tasks.size() == 1) {
            return {0};
        }

        std::vector<int> v(tasks.size());
        std::iota(v.begin(), v.end(), 0);

        std::sort(v.begin(), v.end(), [&](int i, int j) {
            if (tasks[i][0] < tasks[j][0]) {
                return true;
            } else if (tasks[i][0] == tasks[j][0]) {
                return tasks[i][1] <= tasks[j][1];
            } else {
                return false;
            }
        });

        int index = 0;
        // First element is our first one
        uint64_t time = tasks[v[index]].front();
        auto comp = [&](int lhs, int rhs) {
            if (tasks[lhs][1] > tasks[rhs][1]) {
                return true;
            } else if (tasks[lhs][1] == tasks[rhs][1]) {
                return lhs > rhs;
            } else {
                return false;
            }
        };
        std::priority_queue<int, std::vector<int>, decltype(comp)> queue(comp);
        std::vector<int> results;

        queue.push(v[index++]);

        while (queue.size()) {
            auto curr = queue.top();
            queue.pop();

            results.push_back(curr);
            time += tasks[curr].back();

            if (index >= tasks.size()) continue;

            if (queue.empty()) {
                auto first = tasks[v[index]][0];
                if (first > time) time = first;
            }
            while (index < tasks.size() && tasks[v[index]][0] <= time) {
                queue.push(v[index++]);
            }
        }

        return results;
    }
};

TEST_CASE("SingleThreadedCPU", "algorithm") {
    Solution soln;
    std::vector<std::vector<int>> testCase0{{1, 2}, {2, 4}, {3, 2}, {4, 1}};
    std::vector<std::vector<int>> testCase1{{7, 10}, {7, 12}, {7, 5}, {7, 4}, {7, 2}};
    std::vector<std::vector<int>> testCase2{{19,13},{16,9},{37,4},{2,15},{33,6},{12,24}};
    std::vector<std::vector<int>> testCase3{{19,13},{16,9},{21,10},{32,25},{37,4},{49,24},{2,15},{38,41},{37,34},{33,6},{45,4},{18,18},{46,39},{12,24}};
    std::vector<std::vector<int>> testCase4{{100000, 100000}};
    std::vector<std::vector<int>> testCase5{{5,2},{7,2},{9,4},{6,3},{5,10},{1,1}};
    std::vector<std::vector<int>> testCase6{{35,36},{11,7},{15,47},{34,2},{47,19},{16,14},{19,8},{7,34},{38,15},{16,18},{27,22},{7,15},{43,2},{10,5},{5,4},{3,11}};

    CHECK(soln.getOrder(testCase6) == std::vector<int>{15, 14, 13, 1, 6, 3, 5, 12, 8, 11, 9, 4, 10, 7, 0, 2});
    CHECK(soln.getOrder(testCase0) == std::vector<int>{0, 2, 3, 1});
    CHECK(soln.getOrder(testCase1) == std::vector<int>{4, 3, 2, 0, 1});
    CHECK(soln.getOrder(testCase2) == std::vector<int>{3, 1, 0, 2, 4, 5});
    CHECK(soln.getOrder(testCase3) == std::vector<int>{6, 1, 2, 9, 4, 10, 0, 11, 5, 13, 3, 8, 12, 7});
    CHECK(soln.getOrder(testCase4) == std::vector<int>{0});
CHECK(soln.getOrder(testCase5) == std::vector<int>{5, 0, 1, 3, 2, 4});
}

