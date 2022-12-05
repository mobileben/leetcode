//
// Created by Benjamin Lee on 12/5/22.
// https://leetcode.com/problems/search-insert-position/
//

/*
 * We are given a sorted list and the requirements are for the runtime complexity to be O(log n). These are the signs
 * that we must use a binary search.
 *
 * This can be done recursively and iteratively. The recursive way may be a little easier to approach
 *
 * Recursive
 * With the recursive version the space complexity will be O(log n), as we do have stack frames which occupy space
 * Time Complexity: O(log n)
 * Space Complexity: O(log n)
 *
 * Iterative
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
#ifdef RECURSIVE
    int searchInsert(std::vector<int>& nums, int target) {
        return bsearch(nums, 0, nums.size() - 1, target);
    }
#else
    int searchInsert(std::vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int mid;
        while (left <= right) {
            mid = left + ((right - left) >> 1);
            if (target == nums[mid]) {
                return mid;
            } else if (target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
#endif /* RECURSIVE */

private:
#ifdef RECURSIVE
    int bsearch(std::vector<int>& nums, int left, int right, int target) {
        auto mid = left + (right - left) / 2;
        if (target == nums[mid]) {
            return mid;
        } else if (target < nums[mid]) {
            if (left == right) {
                return left;
            }
            return bsearch(nums, left, mid, target);
        } else {
            if (left == right) {
                return left + 1;
            }
            return bsearch(nums, mid+1, right, target);
        }
    }
#endif /* RECURSIVE */
};

TEST_CASE("SearchInsertPosition", "algorithm") {
    Solution soln;
    std::vector<int> testCase0{0};
    int target0 = 1;
    std::vector<int> testCase1{3};
    int target1 = 1;
    std::vector<int> testCase2{0};
    int target2 = 0;
    std::vector<int> testCase3{1, 2};
    int target3 = 2;
    std::vector<int> testCase4{1, 3, 5};
    int target4 = 1;
    std::vector<int> testCase5{1, 3, 5};
    int target5 = 2;
    std::vector<int> testCase6{1, 3, 5};
    int target6 = 3;
    std::vector<int> testCase7{1, 3, 5};
    int target7 = 4;
    std::vector<int> testCase8{1, 3, 5};
    int target8 = 5;
    std::vector<int> testCase9{1, 3, 5, 6};
    int target9 = 5;
    std::vector<int> testCase10{1, 3, 5, 6};
    int target10 = 2;
    std::vector<int> testCase11{1, 3, 5, 6};
    int target11 = 7;

    CHECK(soln.searchInsert(testCase0, target0) == 1);
    CHECK(soln.searchInsert(testCase1, target1) == 0);
    CHECK(soln.searchInsert(testCase2, target2) == 0);
    CHECK(soln.searchInsert(testCase3, target3) == 1);
    CHECK(soln.searchInsert(testCase4, target4) == 0);
    CHECK(soln.searchInsert(testCase5, target5) == 1);
    CHECK(soln.searchInsert(testCase6, target6) == 1);
    CHECK(soln.searchInsert(testCase7, target7) == 2);
    CHECK(soln.searchInsert(testCase8, target8) == 2);
    CHECK(soln.searchInsert(testCase9, target9) == 2);
    CHECK(soln.searchInsert(testCase10, target10) == 1);
    CHECK(soln.searchInsert(testCase11, target11) == 4);
}
