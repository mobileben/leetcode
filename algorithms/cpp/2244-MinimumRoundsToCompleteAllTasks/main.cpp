//
// Created by Benjamin Lee on 1/3/23.
// https://leetcode.com/problems/minimum-rounds-to-complete-all-tasks/
// Medium
// Topics: Array, Hash Table, Greedy, Counting
//

/*
 * To minimize the count, we want to focus on 3s, as maximizing the number of 3s
 * reduces the total count.
 *
 * Our formula is
 *
 * 3x + 2y = tally, where tally is the frequence count of the task
 *
 * 1 = -1
 * 2 = 3 * 0 + 2 * 1, remainder 2, 2 / 3 = 0
 * 3 = 3 * 1 + 2 * 0, remainder 0, 3 / 3 = 1
 * 4 = 3 * 0 + 2 * 2, remainder 1, 4 / 3 = 1, when remainder is 1, we apply 2 twos
 * 5 = 3 * 1 + 2 * 1, remainder 2, 5 / 3 = 1, when remainder is 2, we apply one two
 * 6 = 3 * 2 + 2 * 0, remainder 0, 6 / 3 = 2
 * 7 = 3 * 1 + 2 * 2, remainder 1, 7 / 3 = 2, when remainder is 1, we apply 2 twos
 * 8 = 3 * 2 + 2 * 1, remainder 2, 7 / 3 = 2, when remainder is 2, we apply one two
 * 9 = 3 * 3 + 2 * 0, remainder 0, 7 / 3 = 3
 * 10 = 3 * 3 + 2 * 2, remainder 1, 7 / 3 = 3, when remainder is 1, we apply 2 twos
 *
 * From this pattern above, we can see that
 *
 * tally % 3 == 0, count = tally / 3
 * tally % 3 == 1, we should subtract one 3 and then add 2 twos
 * tally % 3 == 2, we we only need to add a two.
 *
 * In the case of tally % 3 equaling 1 or 2, count would be tally / 3 + 1
 *
 * We can observe that when tally % 3 has no remainder (== 0), the min count is tally / 3.
 *
 * This can also be simplified down to just (tally + 2) / 3
 *
 * Time Complexity: O(n), O(n) for tallying and O(n) to go through the map
 * Space Complexity: O(n)
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <map>

class Solution {
public:
    int minimumRounds(std::vector<int>& tasks) {
        std::map<int, int> tallies;
        int count = 0;

        for (auto task : tasks) {
            tallies[task]++;
        }

        for (auto it : tallies) {
            auto tally = it.second;
            if (tally == 1) {
                return -1;
            }

#if 0
            if (tally % 3 == 0) {
                count += tally / 3;
            } else {
                count += tally / 3 + 1;
            }
#else
            count += (tally + 2) / 3;
#endif
        }

        return count;
    }
};

TEST_CASE("MinimumRoundsToCompleteAllTasks", "algorithm") {
    Solution soln;
    std::vector<int> testCase0{1};
    std::vector<int> testCase1{1, 1};
    std::vector<int> testCase2{1, 1, 1};
    std::vector<int> testCase3{2, 2, 3, 3, 2, 4, 4, 4, 4, 4};
    std::vector<int> testCase4{2, 3, 3};
    std::vector<int> testCase5{5, 5, 5, 5};
    std::vector<int> testCase6{66, 66, 63, 61, 63, 63, 64, 66, 66, 65, 66, 65, 61, 67, 68, 66, 62, 67, 61, 64, 66, 60, 69, 66, 65, 68, 63, 60, 67, 62, 68, 60, 66, 64, 60, 60, 60, 62, 66, 64, 63, 65, 60, 69, 63, 68, 68, 69, 68, 61};

    CHECK(soln.minimumRounds(testCase6) == 20);
    CHECK(soln.minimumRounds(testCase0) == -1);
    CHECK(soln.minimumRounds(testCase1) == 1);
    CHECK(soln.minimumRounds(testCase2) == 1);
    CHECK(soln.minimumRounds(testCase3) == 4);
    CHECK(soln.minimumRounds(testCase4) == -1);
    CHECK(soln.minimumRounds(testCase5) == 2);
}