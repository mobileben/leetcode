//
// Created by Benjamin Lee on 12/27/22.
// https://leetcode.com/problems/first-missing-positive/
// Hard
//

/*
 * The brute force method is straight forward, we can sort, then find our missing positive number.
 *
 * Time Complexity: O(nlogn)
 * Space Complexity: O(n)
 *
 * The question, however, requires
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * We need to understand a subtle property of the array, before proceeding.
 *
 * As we are looking for the smallest missing positive number, this value can be in the range of
 * 1 <= x <= n + 1, where n is the length of the array.
 *
 * The min is straight forward, the max we need to see why this is the case. A property must exist where positive values
 * must be successive. In the "best" case, we see an array like the following
 *
 * 1, 2, 3, 4
 * Here the minimum missing positive number is 5
 *
 * If the array is
 * 0, 2, 3, 4
 * We can see that the missing positive number is 1
 *
 * If we use some larger numbers
 * 0, 1, 10, 20
 * We can see that the missing positive number is 2
 *
 * This means that can do some "filtering" to remove numbers <= 0 as well as > n + 1.
 * We can use our existing array to do some bookkeeping as to keep track of if a we have seen our number. We can do this
 * by using the value as the index. In reality is the value - 1, to compensate for the array being zero indexed.
 * To indicate we have a number, we will make that entry negative.
 *
 * Original
 * 1 2 0
 * After correcting for zero or negative numbers
 * 1 2 4
 * Pass 1
 * -1 2 4
 * Pass 2
 * -1 -2 4
 * Pass 3
 * -1 -2 4
 * Result = 3
 *
 * Original
 * 3 4 -1 1
 * After correcting for zero or negative numbers
 * 3 4 5 1
 * Pass 1
 * 3 4 -5 1
 * Pass 2
 * 3 4 -5 -1
 * Pass 3
 * 3 4 -5 -1
 * Pass 4
 * -3 4 -5 -1
 * Result = 2
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
#ifdef BRUTE
    int firstMissingPositive(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int last = 0;
        for (int i=0;i<nums.size();++i) {
            int num = nums[i];
            if (nums[i] > 0) {
                if ((num - last) > 1){
                    return last + 1;
                }
                last = num;
            }

        }
        return last + 1;
    }
#else
    int firstMissingPositive(std::vector<int>& nums) {
        int len = nums.size();
        for (int i=0;i<len;++i) {
            if (nums[i] <= 0) {
                nums[i] = len + 1;
            }
        }
        for (int i=0;i<len;++i) {
            int num = std::abs(nums[i]);
            if (num <= len && nums[num - 1] > 0) {
                nums[num - 1] *= -1;
            }
        }
        for (int i=0;i<len;++i) {
            if (nums[i] > 0) {
                return i + 1;
            }
        }

        return len + 1;
    }
#endif /* BRUTE */
};

TEST_CASE("FirstMissingPositive", "algorithm") {
    Solution soln;
    std::vector<int> testCase0{1, 2, 0};
    std::vector<int> testCase1{3, 4, -1, 1};
    std::vector<int> testCase2{7, 8, 9, 11, 12};
    std::vector<int> testCase3{1, 3, 2, 5};

    CHECK(soln.firstMissingPositive(testCase0) == 3);
    CHECK(soln.firstMissingPositive(testCase1) == 2);
    CHECK(soln.firstMissingPositive(testCase2) == 1);
    CHECK(soln.firstMissingPositive(testCase3) == 4);
}

