//
// Created by Benjamin Lee on 12/16/22.
// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
//

/*
 * The brute force method iterates through, finding the first and last positions.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * As this is a sorted array and we are looking for a runtime complexity of O(logn), we know we will need to apply a
 * binary search algorthm. The trick here, however, is that the target may be duplicated, and we need to identify
 * the first and last positions of target.
 *
 * The way to manage this is to keep halving until we no longer equal our target value.
 *
 * Note that one could mix linear and binary searches by first finding target, then doing a linear search to find the
 * first and last positions.
 *
 * Additionally, one could solve this with recursive or iterative approaches.
 *
 * Time Complexity: O(logn)
 * Space Complexity: O(1)
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#define RECURSIVE

class Solution {
public:
#ifdef RECURSIVE
    void binarySearch(int start, int end, std::vector<int>& nums, int target, std::vector<int>& soln) {
        if (start > end) {
            return;
        }

        int mid = start + (end - start) / 2;

        if (nums[mid] == target) {
            if (mid < soln.front()) {
                soln[0] = mid;
            }
            if (mid > soln.back()) {
                soln[1] = mid;
            }

            // We need to go both left and right
            int before = mid - 1;
            int after = mid + 1;
            if (before >= 0 && nums[before] == target) {
                binarySearch(start, mid-1, nums, target, soln);
            }
            if (after < nums.size() && nums[after] == target) {
                binarySearch(mid+1, end, nums, target, soln);
            }
        } else if (target < nums[mid]) {
            binarySearch(start, mid-1, nums, target, soln);
        } else {
            binarySearch(mid+1, end, nums, target, soln);
        }
    }

    std::vector<int> searchRange(std::vector<int>& nums, int target) {
        std::vector<int> soln{INT_MAX, INT_MIN};    // min set to max, max set to min

        binarySearch(0, nums.size() - 1, nums, target, soln);

        if (soln.front() == INT_MAX) {
            soln[0] = -1;
            soln[1] = -1;
        }
        return soln;
    }
#else

    int findPosition(int start, int end, std::vector<int>& nums, int target, bool isLower) {
        while (start <= end) {
            int mid = start + (end - start) /2;

            if (nums[mid] == target) {
                // We need to go both left and right
                if (isLower) {
                    int before = mid - 1;
                    if (before >= 0 && nums[before] == target) {
                        end = mid - 1;
                    } else {
                        return mid;
                    }
                } else {
                    int after = mid + 1;
                    if (after < nums.size() && nums[after] == target) {
                        start = mid + 1;
                    } else {
                        return mid;
                    }
                }
            } else if (target < nums[mid]) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
        return -1;
    }

    std::vector<int> searchRange(std::vector<int>& nums, int target) {
        std::vector<int> soln{INT_MAX, INT_MIN};    // min set to max, max set to min
        int start = 0, end = nums.size() - 1;

        soln[0] = findPosition(start, end, nums, target, true);
        soln[1] = findPosition(start, end, nums, target, false);

        return soln;
    }
#endif /* RECURSIVE */
};

TEST_CASE("FindFirstAndLastPositionOfElementInSortedArray", "algorithm") {
    Solution soln;
    std::vector<int> nums0{0, 1, 2};
    int target0 = 0;
    std::vector<int> nums1{0, 1, 2};
    int target1 = 1;
    std::vector<int> nums2{0, 1, 2};
    int target2 = 2;
    std::vector<int> nums3{0, 0, 1, 2};
    int target3 = 0;
    std::vector<int> nums4{0, 1, 1, 2};
    int target4 = 1;
    std::vector<int> nums5{0, 1, 2, 2};
    int target5 = 2;
    std::vector<int> nums6{2, 2, 2, 2, 2, 2, 2};
    int target6 = 2;
    std::vector<int> nums7{0, 2, 2, 2, 2, 2, 3};
    int target7 = 2;
    std::vector<int> nums8{5, 7, 7, 8, 8, 10};
    int target8 = 8;
    std::vector<int> nums9{5, 7, 7, 8, 8, 10};
    int target9 = 6;
    std::vector<int> nums10{};
    int target10 = 0;
    std::vector<int> nums11{1, 1, 3, 4, 5, 5, 5, 5, 5};
    int target11 = 3;

    CHECK(soln.searchRange(nums0, target0) == std::vector<int>{0, 0});
    CHECK(soln.searchRange(nums1, target1) == std::vector<int>{1, 1});
    CHECK(soln.searchRange(nums2, target2) == std::vector<int>{2, 2});
    CHECK(soln.searchRange(nums3, target3) == std::vector<int>{0, 1});
    CHECK(soln.searchRange(nums4, target4) == std::vector<int>{1, 2});
    CHECK(soln.searchRange(nums5, target5) == std::vector<int>{2, 3});
    CHECK(soln.searchRange(nums6, target6) == std::vector<int>{0, 6});
    CHECK(soln.searchRange(nums7, target7) == std::vector<int>{1, 5});
    CHECK(soln.searchRange(nums8, target8) == std::vector<int>{3, 4});
    CHECK(soln.searchRange(nums9, target9) == std::vector<int>{-1, -1});
    CHECK(soln.searchRange(nums10, target10) == std::vector<int>{-1, -1});
    CHECK(soln.searchRange(nums11, target11) == std::vector<int>{2, 2,});
}
