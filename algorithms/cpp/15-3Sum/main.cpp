//
// Created by Benjamin Lee on 12/10/22.
// https://leetcode.com/problems/3sum/
//

/*
 * One of the key requirements here is that there cannot be duplicate triplets.
 *
 * To brute force, one can go through all permutations, though this will result in TLE.
 *
 * Time Complexity: O(n^3)
 * Space Complexity: O(n)
 *
 * Another brute force method would be to iterate though the digits, but then use two pointers to find the other two
 * addends. If we sort the list, we can skip over items which will result in duplicates.
 *
 * Time Complexity: O(nlogn) + O(n^2) == O(n^2)
 * Space Complexity: O(n)
 *
 * One also can use hash tables to solve this as well. The data can be pre-sorted or more optimally, not pre-sorted.
 *
 * Hash table variants seem to perform slower in the test cases in LeetCode, occassionally TLE.
 *
 * Hash tables with pre-sort
 * Time Complexity: O(nlogn) + O(n^2) == O(n^2)
 * Space Complexity: O(n)
 *
 * Hash tables without pre-sort (this will be slower than without the pre-sort due to usage of both the hashset and
 * hashmap)
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 *
 */
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <set>

#define TWO_POINTERS

class Solution {
public:
    static bool isPermutation(std::vector<std::vector<int>>& results, std::vector<std::vector<int>>& compare) {
        if (results.size() != compare.size()) {
            return false;
        }

        for (auto elem : results) {
            bool found = false;
            for (auto compareElem : compare) {
                if (elem.size() != compareElem.size()) {
                    break;
                }
                if (std::is_permutation(elem.begin(), elem.end(), compareElem.begin())) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                return false;
            }
        }
        return true;
    }

#ifdef BRUTE
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::set<std::vector<int>> tresults;

        for (int i=0;i<nums.size();++i) {
            for (int j=i+1;j<nums.size();++j) {
                for (int k=j+1;k<nums.size();++k) {
                    if ((nums[i] + nums[j] + nums[k]) == 0) {
                        std::vector<int> v{nums[i], nums[j], nums[k]};
                        std::sort(v.begin(), v.end());
                        tresults.insert(v);
                    }
                }
            }
        }

        return std::vector<std::vector<int>>(tresults.begin(), tresults.end());
    }
#elif defined(TWO_POINTERS)
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<std::vector<int>> results;
        int lo = 0, hi = nums.size() - 1;

        std::sort(nums.begin(), nums.end());

        for (int i=0;i<nums.size();++i) {
            if (i == 0 || nums[i - 1] != nums[i]) {
                lo = i + 1;
                hi = nums.size() - 1;
                while(lo < hi) {
                    int sum = nums[i] + nums[lo] + nums[hi];
                    if (sum < 0) {
                        // sum < 0 means our numbers are too small, so move right
                        ++lo;
                    } else if (sum > 0) {
                        // sum > 0 means our numbers are too large, so move left
                        --hi;
                    } else {
                        results.push_back({nums[i], nums[lo], nums[hi]});
                        ++lo;
                        --hi;
                        // Skip dupes
                        while (lo < hi && nums[lo] == nums[lo - 1]) {
                            ++lo;
                        }
                        // Skip dupes
                        while (lo < hi && nums[hi] == nums[hi + 1]) {
                            --hi;
                        }
                    }
                }
            }
        }

        return results;
    }
#else
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<std::vector<int>> results;

        std::sort(nums.begin(), nums.end());

        for (int i=0;i<nums.size();++i) {
            if (i == 0 || nums[i - 1] != nums[i]) {
                std::set<int> hits;

                for (int j=i+1;j<nums.size();++j) {
                    int complement = -nums[i] - nums[j];
                    if (hits.count(complement)) {
                        results.push_back({nums[i], nums[j], complement});
                        // Skip dupes
                        while (j+1 < nums.size() && nums[j] == nums[j + 1]) {
                            ++j;
                        }
                    }
                    hits.insert(nums[j]);
                }
            }
        }

        return results;
    }
#endif /* BRUTE */
};

TEST_CASE("3Sum", "algorithm") {
    Solution soln;
    auto testCase0 = std::vector<int>{-1, 0, 1, 2, -1, -4};
    auto testCase1 = std::vector<int>{0, 1, 1};
    auto testCase2 = std::vector<int>{0, 0, 0};
    auto testCase3 = std::vector<int>{-12,4,12,-4,3,2,-3,14,-14,3,-12,-7,2,14,-11,3,-6,6,4,-2,-7,8,8,10,1,3,10,-9,8,5,11,3,-6,0,6,12,-13,-11,12,10,-1,-15,-12,-14,6,-15,-3,-14,6,8,-9,6,1,7,1,10,-5,-4,-14,-12,-14,4,-2,-5,-11,-10,-7,14,-6,12,1,8,4,5,1,-13,-3,5,10,10,-1,-13,1,-15,9,-13,2,11,-2,3,6,-9,14,-11,1,11,-6,1,10,3,-10,-4,-12,9,8,-3,12,12,-13,7,7,1,1,-7,-6,-13,-13,11,13,-8};

    auto soln0 = std::vector<std::vector<int>>{{-1, -1, 2}, {-1, 0, 1}};
    auto soln1 = std::vector<std::vector<int>>{};
    auto soln2 = std::vector<std::vector<int>>{{0, 0, 0}};
    auto soln3 = std::vector<std::vector<int>>{{-15,1,14},{-15,2,13},{-15,3,12},{-15,4,11},{-15,5,10},{-15,6,9},{-15,7,8},{-14,0,14},{-14,1,13},{-14,2,12},{-14,3,11},{-14,4,10},{-14,5,9},{-14,6,8},{-14,7,7},{-13,-1,14},{-13,0,13},{-13,1,12},{-13,2,11},{-13,3,10},{-13,4,9},{-13,5,8},{-13,6,7},{-12,-2,14},{-12,-1,13},{-12,0,12},{-12,1,11},{-12,2,10},{-12,3,9},{-12,4,8},{-12,5,7},{-12,6,6},{-11,-3,14},{-11,-2,13},{-11,-1,12},{-11,0,11},{-11,1,10},{-11,2,9},{-11,3,8},{-11,4,7},{-11,5,6},{-10,-4,14},{-10,-3,13},{-10,-2,12},{-10,-1,11},{-10,0,10},{-10,1,9},{-10,2,8},{-10,3,7},{-10,4,6},{-10,5,5},{-9,-5,14},{-9,-4,13},{-9,-3,12},{-9,-2,11},{-9,-1,10},{-9,0,9},{-9,1,8},{-9,2,7},{-9,3,6},{-9,4,5},{-8,-6,14},{-8,-5,13},{-8,-4,12},{-8,-3,11},{-8,-2,10},{-8,-1,9},{-8,0,8},{-8,1,7},{-8,2,6},{-8,3,5},{-8,4,4},{-7,-7,14},{-7,-6,13},{-7,-5,12},{-7,-4,11},{-7,-3,10},{-7,-2,9},{-7,-1,8},{-7,0,7},{-7,1,6},{-7,2,5},{-7,3,4},{-6,-6,12},{-6,-5,11},{-6,-4,10},{-6,-3,9},{-6,-2,8},{-6,-1,7},{-6,0,6},{-6,1,5},{-6,2,4},{-6,3,3},{-5,-5,10},{-5,-4,9},{-5,-3,8},{-5,-2,7},{-5,-1,6},{-5,0,5},{-5,1,4},{-5,2,3},{-4,-4,8},{-4,-3,7},{-4,-2,6},{-4,-1,5},{-4,0,4},{-4,1,3},{-4,2,2},{-3,-3,6},{-3,-2,5},{-3,-1,4},{-3,0,3},{-3,1,2},{-2,-2,4},{-2,-1,3},{-2,0,2},{-2,1,1},{-1,-1,2},{-1,0,1}};

    auto results0 = soln.threeSum(testCase0);
    auto results1 = soln.threeSum(testCase1);
    auto results2 = soln.threeSum(testCase2);
    auto results3 = soln.threeSum(testCase3);

    CHECK(soln.isPermutation(results0, soln0));
    CHECK(soln.isPermutation(results1, soln1));
    CHECK(soln.isPermutation(results2, soln2));
    CHECK(soln.isPermutation(results3, soln3));
}
