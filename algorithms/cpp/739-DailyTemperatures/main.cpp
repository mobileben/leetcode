//
// Created by Benjamin Lee on 12/17/22.
// https://leetcode.com/problems/daily-temperatures/
//

/*
 * Brute force methods iterate through all permutations, trying to find if for each index, there the first rise in
 * temperature. This is time intensive and will TLE.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 *
 * We can use a stack to the indices of days that are not warmer. This type of stack is called a monotomic stack.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <stack>

class Solution {
public:
#ifdef BRUTE
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
        std::vector<int> results(temperatures.size());

        for (int i=0;i<temperatures.size();++i) {
            int days = 0;
            for (int j=i+1;j<temperatures.size();++j) {
               if (temperatures[j] > temperatures[i]) {
                   results[i] = days + 1;
                   break;
               } else {
                   ++days;
               }
            }
        }

        return results;
    }
#else
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
        std::vector<int> results(temperatures.size());
        std::stack<int> stack;

        for (int i=0;i<temperatures.size();++i) {
            int temp = temperatures[i];
            while (stack.size() && temperatures[stack.top()] < temp) {
                auto index = stack.top();
                auto diff = i - index;
                results[index] =  diff;
                stack.pop();
            }
            stack.push(i);
        }

        return results;
    }
#endif /* BRUTE */
};

TEST_CASE("DailyTemperatures", "algorithm") {
    Solution soln;
    std::vector<int> testCase0{70};
    std::vector<int> testCase1{70, 70};
    std::vector<int> testCase2{70, 80};
    std::vector<int> testCase3{73, 74, 75, 71, 69, 72, 76, 73};
    std::vector<int> testCase4{30, 40, 50, 60};
    std::vector<int> testCase5{30, 60, 90};
    std::vector<int> testCase6{55, 38, 53, 81, 61, 93, 97, 32, 43, 78};

    CHECK(soln.dailyTemperatures(testCase0) == std::vector<int>{0});
    CHECK(soln.dailyTemperatures(testCase1) == std::vector<int>{0, 0});
    CHECK(soln.dailyTemperatures(testCase2) == std::vector<int>{1, 0});
    CHECK(soln.dailyTemperatures(testCase3) == std::vector<int>{1, 1, 4, 2, 1, 1, 0, 0});
    CHECK(soln.dailyTemperatures(testCase4) == std::vector<int>{1, 1, 1, 0});
    CHECK(soln.dailyTemperatures(testCase5) == std::vector<int>{1, 1, 0});
    CHECK(soln.dailyTemperatures(testCase6) == std::vector<int>{3, 1, 1, 2, 1, 1, 0, 1, 1, 0});
}

