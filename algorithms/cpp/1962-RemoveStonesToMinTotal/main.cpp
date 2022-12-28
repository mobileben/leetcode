//
// Created by Benjamin Lee on 12/27/22.
// https://leetcode.com/problems/remove-stones-to-minimize-the-total/
// Medium
//

/*
 * A priority heap can be used here, as the highest priority, or pile value in this case, will always be at the top
 * (front).
 *
 * Time Complexity: O(n + klogn)
 * Space Complexity: O(n)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <queue>

class Solution {
public:
    int minStoneSum(std::vector<int>& piles, int k) {
        std::priority_queue<int> queue(piles.begin(), piles.end());
        for (int i=0;i<k;++i) {
            int pile = queue.top();
            queue.pop();
            queue.push(pile - pile / 2);
        }
        int count = 0;
        while (queue.size()) {
            count += queue.top();
            queue.pop();
        }
        return count;
    }
};

TEST_CASE("RemoveStonesToMinTotal", "algorithm") {
    Solution soln;
    std::vector<int> piles0{5, 4, 9};
    std::vector<int> piles1{4, 3, 6, 7};

    CHECK(soln.minStoneSum(piles0, 2) == 12);
    CHECK(soln.minStoneSum(piles1, 3) == 12);
}

