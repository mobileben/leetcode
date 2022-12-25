//
// Created by Benjamin Lee on 12/24/22.
// https://leetcode.com/problems/longest-subsequence-with-limited-sum/
//

/*
 * We will first need to sort our array, which will take O(nlogn) time.
 *
 * There a more brute force method would be to do the sort, then, for each query, go through all the values,
 * adding them up (or subtracting from query, which is what I am doing) to find out the max count. This relies on
 * using a sorted array and then aggregating values from min to max, which will maximize the subsequence length.
 *
 * Considering n as the number of numbers and m as the number of queries
 *
 * Time Complexity: O(mn + nlogn)
 * Space Complexity: O(n) for sorting
 *
 * Another alternative is to use prefix sum and then using a binary search to find the insertion point.
 *
 * Sort: O(nlogn)
 * Binary Search: O(logn)
 *
 * n * logn for sort
 * m * logn for searching all queries
 * n for prefix sum
 *
 * n + m * logn + n * logn => (m + n)logn
 *
 * Time Complexity: O((m + n)logn)
 * Space Complexity: O(n) for sorting
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
#ifdef BURTE
    std::vector<int> answerQueries(std::vector<int>& nums, std::vector<int>& queries) {
        std::vector<int> results;

        // First sort the nums
        std::sort(nums.begin(), nums.end());

        for (auto query : queries) {
            // Now binary search to find a value that is
            int count = 0;
            for (auto num : nums) {
                if (num <= query) {
                    query -= num;
                    ++count;
                }
            }
            results.push_back(count);
        }
        return results;
    }
#else
    int binarySearch(std::vector<int>& nums, int query) {
        // Binary search (though could use std::upper_bound)
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (query == nums[mid]) {
                return mid + 1;
            }
            if (query <= nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return right + 1;
    }

    std::vector<int> answerQueries(std::vector<int>& nums, std::vector<int>& queries) {
        std::vector<int> results;

        // First sort the nums
        std::sort(nums.begin(), nums.end());

        // Prefix sum (in-place)
        for (int i=0;i<nums.size() - 1;++i) {
            nums[i+1] += nums[i];
        }

        for (auto query : queries) {
            results.push_back(binarySearch(nums, query));
        }

        return results;
    }
#endif /* BRUTE */
};

TEST_CASE("LongestSubsequenceWithLimitedSum", "algorithm") {
    Solution soln;
    std::vector<int> nums0{4, 5, 2, 1};
    std::vector<int> queries0{3, 10, 21};
    std::vector<int> nums1{2, 3, 4, 5};
    std::vector<int> queries1{1};

    CHECK(soln.answerQueries(nums0, queries0) == std::vector<int>{2, 3, 4});
    CHECK(soln.answerQueries(nums1, queries1) == std::vector<int>{0});
}


