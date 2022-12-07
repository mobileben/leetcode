//
// Created by Benjamin Lee on 12/6/22.
// https://leetcode.com/problems/median-of-two-sorted-arrays/
//

/*
 * The special requirements indicate that the time complexity must be O(log(m+n))
 *
 * Brute for method would be to first combine the two arrays and then to sort and then find the median
 *
 * Time Complexity: O(m + n)
 * Space Complexity: O(m + n)
 *
 * The special requirement for this problem indicates that time complexity must be O(log(m+n)). log(m+n) implies using
 * binary search. At this particular point in time, I don't know how to solve this, but will refer to the solutions and
 * will return
 *
 */
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#define BRUTE_WITHOUT_STDLIB

class Solution {
public:
#ifdef BRUTE
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        double median = 0;
        // This is using C++ stdlib
        nums1.insert(nums1.end(), nums2.begin(), nums2.end());
        std::sort(nums1.begin(), nums1.end());

        auto half = nums1.size() / 2;
        if (nums1.size() & 1) {
            median = nums1[half];
        } else {
            median = (nums1[half-1] + nums1[half]) / 2.0;
        }

        return median;
    }
#elif defined(BRUTE_WITHOUT_STDLIB)
    static double computeMedian(std::vector<int>& v) {
        auto half = v.size() / 2;
        if (v.size() & 1) {
            return v[half];
        } else {
            return (v[half-1] + v[half]) / 2.0;
        }
    }

    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::vector<int> merged(nums1.size() + nums2.size());
        int nums1Index = 0, nums2Index = 0;

        // Trivial cases
        if (nums1.empty()) {
            return computeMedian(nums2);
        } else if (nums2.empty()) {
            return computeMedian(nums1);
        }

        // We know we will start with both nums1 and nums2 having a length of at least 1
        int index = 0;
        while (nums1Index < nums1.size() || nums2Index < nums2.size()) {
            if (nums1[nums1Index] <= nums2[nums2Index]) {
                merged[index++] = nums1[nums1Index];
                ++nums1Index;
            } else {
                merged[index++] = nums2[nums2Index];
                ++nums2Index;
            }

            // Determine if we are out, and if we are splice the remainder
            if (nums1Index == nums1.size()) {
                std::copy(nums2.begin() + nums2Index, nums2.end(), merged.begin() + index);
                break;
            }
            if (nums2Index == nums2.size()) {
                std::copy(nums1.begin() + nums1Index, nums1.end(), merged.begin() + index);
                break;
            }
        }

        return computeMedian(merged);
    }
#endif /* BRUTE */
};

TEST_CASE("MedianOfTwoSortedArrays", "algorithm") {
    Solution soln;
    std::vector<int> testCase1_0{0};
    std::vector<int> testCase2_0{};
    std::vector<int> testCase1_1{0};
    std::vector<int> testCase2_1{};
    std::vector<int> testCase1_2{1};
    std::vector<int> testCase2_2{2};
    std::vector<int> testCase1_3{1, 3};
    std::vector<int> testCase2_3{2};
    std::vector<int> testCase1_4{1, 2};
    std::vector<int> testCase2_4{3, 4};
    std::vector<int> testCase1_5{0};
    std::vector<int> testCase2_5{};
    std::vector<int> testCase1_6{0};
    std::vector<int> testCase2_6{};

    auto actual2 = soln.findMedianSortedArrays(testCase1_2, testCase2_2);
    auto actual0 = soln.findMedianSortedArrays(testCase1_0, testCase2_0);
    auto actual1 = soln.findMedianSortedArrays(testCase1_1, testCase2_1);
    auto actual3 = soln.findMedianSortedArrays(testCase1_3, testCase2_3);
    auto actual4 = soln.findMedianSortedArrays(testCase1_4, testCase2_4);
    auto actual5 = soln.findMedianSortedArrays(testCase1_5, testCase2_5);
    auto actual6 = soln.findMedianSortedArrays(testCase1_6, testCase2_6);

    double expected0 = 0;
    double expected1 = 0;
    double expected2 = 1.5;
    double expected3 = 2;
    double expected4 = 2.5;
    double expected5 = 0;
    double expected6 = 0;

    CHECK(actual0 == expected0);
    CHECK(actual1 == expected1);
    CHECK(actual2 == expected2);
    CHECK(actual3 == expected3);
    CHECK(actual4 == expected4);
    CHECK(actual5 == expected5);
    CHECK(actual6 == expected6);
}

