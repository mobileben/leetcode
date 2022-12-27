//
// Created by Benjamin Lee on 12/26/22.
// https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks/
//

/*
 * This is a straight forward question.
 * 1. Compute the number of rocks needed to fill a bag. O(n)
 * 2. Sort. O(nlogn)
 * 3. Traverse list to count as well as fill in bags when possible. O(n)
 *
 * Time Complexity: O(nlogn)
 * Space Complexity: O(1) if we cannibalize capacity, else O(n)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
    int maximumBags(std::vector<int>& capacity, std::vector<int>& rocks, int additionalRocks) {
        // We are going to cannibalize capacity
        // O(n)
        for (int i=0;i<capacity.size();++i) {
            capacity[i] -= rocks[i];
        }

        // Now sort
        // O(nlogn)
        std::sort(capacity.begin(), capacity.end());

        // Now iterate (we can do binary search later)
        int count = 0;
        // O(n)
        for (int i=0;i<capacity.size();++i) {
            if (capacity[i] == 0) {
                ++count;
            } else {
                int use = std::min(capacity[i], additionalRocks);
                capacity[i] -= use;
                additionalRocks -= use;

                if (capacity[i] == 0) {
                    ++count;
                } else {
                    break;
                }
            }
        }

        return count;
    }
};

TEST_CASE("MaxBagsWithFullCapacityRocks", "algorithm") {
    Solution soln;
    std::vector<int> capacity0{2, 3, 4, 5};
    std::vector<int> rocks0{1, 2, 4, 4};
    std::vector<int> capacity1{10, 2, 2};
    std::vector<int> rocks1{2, 2, 0};

    CHECK(soln.maximumBags(capacity0, rocks0, 2) == 3);
    CHECK(soln.maximumBags(capacity1, rocks1, 100) == 3);
}

