//
// Created by Benjamin Lee on 12/1/22.
// https://leetcode.com/problems/two-sum/
//

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <unordered_map>

namespace TwoSum {
    class Solution {
    public:
        static std::vector<int> twoSumBrute(std::vector<int>& nums, int target) {
            // N^2
            for (auto i=0;i<nums.size();++i) {
                for (auto j=i+1;j<nums.size();++j) {
                    if ((nums[i] + nums[j]) == target) {
                        return std::vector<int>{i, j};
                    }
                }
            }
            return std::vector<int>{0, 0};
        }

        static std::vector<int> twoSumBetter(std::vector<int>& nums, int target) {
            std::unordered_map<int, int> lookup;
            // N
            for (auto i=0;i<nums.size();++i) {
                auto val = nums[i];
                lookup.insert({val, i});
            }

            // N
            for (auto i=0;i<nums.size();++i) {
                auto value = nums[i];
                auto diff = target - value;
                auto second = lookup.find(diff);
                if (second != lookup.end() && second->second != i) {
                    return std::vector({i, second->second});
                }
            }
            return std::vector<int>{0, 0};
        }

        static std::vector<int> twoSumBest(std::vector<int>& nums, int target) {
            std::unordered_map<int, int> lookup;

            // N, one pass since eventually, we will encounter both addends
            for (auto i=0;i<nums.size();++i) {
                auto value = nums[i];
                auto diff = target - value;
                auto second = lookup.find(diff);
                if (second != lookup.end()) {
                    return std::vector{i, second->second};
                }
                lookup.insert({value, i});
            }
            return std::vector<int>{0, 0};
        }
    };

    TEST_CASE("Two Sum", "algorithm") {
        std::vector<int> testCase0{2, 7, 11, 15};
        std::vector<int> testCase1{3, 2, 4};
        std::vector<int> testCase2{3, 3};
        std::vector<int> testCase3{-1, -2, -3, -4, -5};

        SECTION("Brute Force") {
            auto results0 = Solution::twoSumBrute(testCase0, 9);
            auto results1 = Solution::twoSumBrute(testCase1, 6);
            auto results2 = Solution::twoSumBrute(testCase2, 6);
            auto results3 = Solution::twoSumBrute(testCase3, -8);

            CHECK((results0 == std::vector<int>{0, 1} || results0 == std::vector<int>{1, 0}));
            CHECK((results1 == std::vector<int>{1, 2} || results1 == std::vector<int>{2, 1}));
            CHECK((results2 == std::vector<int>{0, 1} || results2 == std::vector<int>{1, 0}));
            CHECK((results3 == std::vector<int>{2, 4} || results3 == std::vector<int>{4, 2}));
        }

        SECTION("Better") {
            auto results0 = Solution::twoSumBetter(testCase0, 9);
            auto results1 = Solution::twoSumBetter(testCase1, 6);
            auto results2 = Solution::twoSumBetter(testCase2, 6);
            auto results3 = Solution::twoSumBetter(testCase3, -8);

            CHECK((results0 == std::vector<int>{0, 1} || results0 == std::vector<int>{1, 0}));
            CHECK((results1 == std::vector<int>{1, 2} || results1 == std::vector<int>{2, 1}));
            CHECK((results2 == std::vector<int>{0, 1} || results2 == std::vector<int>{1, 0}));
            CHECK((results3 == std::vector<int>{2, 4} || results3 == std::vector<int>{4, 2}));
        }

        SECTION("Best") {
            auto results0 = Solution::twoSumBest(testCase0, 9);
            auto results1 = Solution::twoSumBest(testCase1, 6);
            auto results2 = Solution::twoSumBest(testCase2, 6);
            auto results3 = Solution::twoSumBest(testCase3, -8);

            CHECK((results0 == std::vector<int>{0, 1} || results0 == std::vector<int>{1, 0}));
            CHECK((results1 == std::vector<int>{1, 2} || results1 == std::vector<int>{2, 1}));
            CHECK((results2 == std::vector<int>{0, 1} || results2 == std::vector<int>{1, 0}));
            CHECK((results3 == std::vector<int>{2, 4} || results3 == std::vector<int>{4, 2}));
        }
    }
}