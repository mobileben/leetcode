//
// Created by Benjamin Lee on 12/14/22.
// https://leetcode.com/problems/search-in-rotated-sorted-array/
//

/*
 * Brute for algorithm will just traverse the whole vector, until we find the first instance of the target. As this
 * is super basic, we will forgo implementing it here.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * However, we are told that our runtime complexity must be O(logn), which hints at us that we should use a binary
 * search. The problem here is that we have a rotated sorted array. It is this rotation that is potentially problematic.
 *
 * We can examine the rotation pattern below for clues on how to approach this.
 *
 * Index: 0 | 1 | 2 | 3 | 4 | 5 | 6
 * ---------|---|---|---|---|---|--
 * Rot 0: 0 | 1 | 2 | 4 | 5 | 6 | 7
 * Rot 1: 7 | 0 | 1 | 2 | 4 | 5 | 6
 * Rot 2: 6 | 7 | 0 | 1 | 2 | 4 | 5
 * Rot 3: 5 | 6 | 7 | 0 | 1 | 2 | 4
 * Rot 4: 4 | 5 | 6 | 7 | 0 | 1 | 2
 * Rot 5: 2 | 4 | 5 | 6 | 7 | 0 | 1
 * Rot 6: 1 | 2 | 4 | 5 | 6 | 7 | 0
 * Rot 7: 0 | 1 | 2 | 4 | 5 | 6 | 7
 *
 * Observations
 * - Size of our array is 7
 * - At rotation % 7, we will always be fully sorted
 * - When fully sorted, nums[left] <= nums[right] for both the left and right sides
 * - When *not* fully sorted, the side with the rotation point will have nums[right] < nums[left]
 * - Our target can be the pivot
 * - Our target can also be at nums[left] or nums[right]. Note that all numbers are unique, so can't have duplicate values
 *
 * First approach is to use a recursive binary approach. The key to my approach is determining whether we want to go
 * left or right. Since we have rotation, we check to see if our left side is sorted. If it is, we then determine
 * if we really want to go left based on of our target is within the range of the left sorted side.
 *
 * Otherwise we check to see if it looks like target should belong on the left.
 *
 * Time Complexity: O(logn)
 * Space Complexity: O(logn) for recursion
 *
 * We could also do a similar method, but without recursion
 *
 * Time Complexity: O(logn)
 * Space Complexity: O(1)
 *
 */

#define CATCH_CONIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
#ifdef RECURSIVE
    int rotatedBinarySearch(int start, int end, std::vector<int>& nums, int target) {
        int mid = start + (end - start) / 2;
        if (end == start) {
            return nums[mid] == target ? mid : -1;
        }

        bool useLeft = false;

        if(nums[start] <= nums[mid]) {
            // Left side is sorted, are we in bounds?
            if (nums[start] <= target && target <= nums[mid]) {
                useLeft = true;
            } else {
                useLeft = false;
            }
        } else {
            // Left side is not sorted
            if (nums[start] <= target || target <= nums[mid]) {
                useLeft = true;
            } else {
                useLeft = false;
            }
        }

        if (useLeft) {
            return rotatedBinarySearch(start, mid, nums, target);
        } else {
            return rotatedBinarySearch(mid + 1, end, nums, target);
        }
    }

    int search(std::vector<int>& nums, int target) {
        return rotatedBinarySearch(0, nums.size() - 1, nums, target);
    }
#else
    int search(std::vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] >= nums[left]) {
                // Left side is sorted
                if (nums[left] <= target && target <= nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                // Left side is not sorted
                if (nums[left] <= target || target <= nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
        }

        return -1;
    }
#endif /* RECURSIVE */
};

TEST_CASE("SearchInRotatedSortedArray") {
    Solution soln;
    std::vector<int> nums0{4, 5, 6, 7, 0, 1, 2};
    int target0 = 0;
    std::vector<int> nums1{4, 5, 6, 7, 0, 1, 2};
    int target1 = 3;
    std::vector<int> nums2{1};
    int target2 = 0;
    std::vector<int> nums3{0, 1, 2, 4, 5, 6, 7};
    int target3 = 4;
    std::vector<int> nums4{7, 0, 1, 2, 4, 5, 6};
    int target4 = 0;
    std::vector<int> nums5{7, 0, 1, 2, 4, 5, 6};
    int target5 = 1;
    std::vector<int> nums6{7, 0, 1, 2, 4, 5, 6};
    int target6 = 2;
    std::vector<int> nums7{7, 0, 1, 2, 4, 5, 6};
    int target7 = 7;

    CHECK(soln.search(nums4, target4) == 1);
    CHECK(soln.search(nums0, target0) == 4);
    CHECK(soln.search(nums1, target1) == -1);
    CHECK(soln.search(nums2, target2) == -1);
    CHECK(soln.search(nums3, target3) == 3);
    CHECK(soln.search(nums5, target5) == 2);
    CHECK(soln.search(nums6, target6) == 3);
    CHECK(soln.search(nums7, target7) == 0);
}