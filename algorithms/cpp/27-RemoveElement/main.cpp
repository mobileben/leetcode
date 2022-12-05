//
// Created by Benjamin Lee on 12/4/22.
// https://leetcode.com/problems/remove-element/
//

/*
 * This is similar to 26 Remove Duplicates From Sorted Array.
 * We have a pointer which acts as both the counter as well as where to write.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * There is an optimization that can be done, in the case when val is rare. If this is the case, one want to minimize
 * the amount of copies. This can be done, by "shrinking" the vector by one from the right. Eventually, the index
 * pointer and the end pointer will converge.
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
#ifdef BRUTE
    int removeElement(std::vector<int>& nums, int val) {
        int count = 0;
        for (auto n : nums) {
            if (n != val) {
                nums[count++] = n;
            }
        }
        return count;
    }
#else
    int removeElement(std::vector<int>& nums, int val) {
        int i = 0;
        int n = nums.size();
        while (i < n) {
            if (nums[i] == val) {
                // Reduce size of vector, copying over last element into current slot
                nums[i] = nums[n - 1];
                --n;
            } else {
                ++i;
            }
        }
        return n;
    }
#endif /* BRUTE */
};

TEST_CASE("RemoveElement", "algorithm") {
    Solution soln;
    std::vector<int> testCase0{};
    std::vector<int> testCase1{0};
    std::vector<int> testCase2{0, 1};
    std::vector<int> testCase3{0, 1};
    std::vector<int> testCase4{0, 2, 1};
    std::vector<int> testCase5{2, 1, 0};
    std::vector<int> testCase6{3, 2, 2, 3};
    std::vector<int> testCase7{0, 1, 1, 1, 2, 4, 1, 1, 3};
    std::vector<int> testCase8{0, 1, 2, 2, 3, 0, 4, 2};

    CHECK(soln.removeElement(testCase0, 1) == 0);
    CHECK(soln.removeElement(testCase1, 0) == 0);
    CHECK(soln.removeElement(testCase2, 0) == 1);
    CHECK(soln.removeElement(testCase3, 2) == 2);
    CHECK(soln.removeElement(testCase4, 2) == 2);
    CHECK(soln.removeElement(testCase5, 0) == 2);
    CHECK(soln.removeElement(testCase6, 3) == 2);
    CHECK(soln.removeElement(testCase7, 1) == 4);
    CHECK(soln.removeElement(testCase8, 2) == 5);
}