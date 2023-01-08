//
// Created by Benjamin Lee on 1/7/23.
// https://leetcode.com/problems/gas-station/
// Medium
// Topics:
//

/*
 * The brute force is to simply iterate through and for each case, try and make the round trip.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 *
 * Another way of looking at this is to understand that we can compute the difference between gas
 * and cost at each step. For example:
 *
 * gas:   1  2  3 4 5
 * cost:  3  4  5 1 2
 * diff: -2 -2 -2 3 3
 *
 * What we can observe here is that when we can make a round trip, the cumulative sum from our
 * starting point will be >= 0. We can see that if we create a vector that is the diff repeated once
 * we can easily traverse this. Repeating it once allows us to naturally iterate and have one loop.
 * As we can see below, our start is index 3. We can see with our repeated vector, we can go
 * clockwise where the total sum is >= 0.
 *          v -    -  -  - v
 * -2 -2 -2 3 3 | -2 -2 -2 3 3
 *
 * If we wanted we could use logic to reduce the space complexity by only using a diff vector the
 * size of gas.size()
 *
 * Time Complexity: O(n), really O(4n) => O(n)
 * Space Complexity: O(n), really O(2n) => O(n)
 *
 * We can further refine this to a more optimal solution by observing some more details on the maths.
 * An observation we can see is that the summation of the differential of gas and cost must be >= 0.
 * Otherwise, it is not possible to do a round trip. We are left with the question of what is our starting
 * position. For that, we only have to check if our current tank levels are enough.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
#ifdef BRUTE
    int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
        int size = gas.size();
        for (int i=0;i<size;++i) {
            int tank = gas[i];
            int needed = cost[i];
            for (int j=1;j<size+1;j++) {
                int index = i + j;
                if (index >= size) {
                    index -= size;
                }
                if (tank >= needed) {
                    tank = tank - needed + gas[index];
                    needed = cost[index];
                    if (j == size) {
                        return i;
                    }
                } else {
                    break;
                }
            }
        }
        return -1;
    }
#elifdef BETTER
    int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
        int size = gas.size();
        std::vector<int> diff(size * 2);
        int start = 0;
        int stop = 0;
        int tank = 0;

        for (int i=0;i<size;++i) {
            diff[size + i] = diff[i] = gas[i] - cost[i];
        }

        for (int i=0;i<diff.size();++i) {
            if (stop == size) {
                return start;
            }
            tank += diff[i];
            if (tank < 0) {
                start = i + 1;
                tank = 0;
                stop = 0;
                if (start >= size) {
                    return -1;
                }
            } else {
                ++stop;
            }
        }
        return -1;
    }
#else
    int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
        int totalTank = 0;
        int tank = 0;
        int start = 0;

        for (int i=0;i<gas.size();++i) {
            totalTank += gas[i] - cost[i];
            tank += gas[i] - cost[i];

            if (tank < 0) {
                start = i + 1;
                tank = 0;
            }
        }

        return totalTank >= 0 ? start : -1;
    }
#endif /* BRUTE */
};

TEST_CASE("GasStation", "algorithm") {
    Solution soln;
    std::vector<int> gas0{1, 2, 3, 4, 5};
    std::vector<int> cost0{3, 4, 5, 1, 2};
    std::vector<int> gas1{2, 3, 4};
    std::vector<int> cost1{3, 4, 3};

    CHECK(soln.canCompleteCircuit(gas0, cost0) == 3);
    CHECK(soln.canCompleteCircuit(gas1, cost1) == -1);
}