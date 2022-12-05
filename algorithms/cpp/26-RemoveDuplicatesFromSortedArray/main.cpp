//
// Created by Benjamin Lee on 12/4/22.
// https://leetcode.com/problems/remove-duplicates-from-sorted-array/
//

/*
 * A brute force/naive way would be to have a pointer tha moves to the next valid spot to fill. This would be done
 * when our value is not a duplicate. This essentially results in having two indices. One for iterating through the
 * vector and the other indicating where to write.
 *
 * However, we can make this a bit cleaner by using a range based loop and copying over the right value as well as
 * incrementing the count when we are not at the first element and our current number is greater than the previous.
 *
 * Note that if we were allowed to use extra space, we could have used a map to get all the unique elements in the list.
 *
 * Time Complexity(n)
 * Space Complexity(1)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
#ifdef BRUTE
    int removeDuplicates(std::vector<int>& nums) {
        int pointer = 1;
        int curr = nums.front();

        for (auto i=1;i<nums.size();++i) {
            if (nums[i] != curr) {
                curr = nums[i];
                nums[pointer++] = nums[i];
            }
        }
        return pointer;
    }
#else
    int removeDuplicates(std::vector<int>& nums) {
        int count = 0;
        for (auto n : nums) {
            if (!count || n != nums[count - 1]) {
                nums[count++] = n;
            }
        }
        return count;
    }
#endif /* BRUTE */
};

TEST_CASE("RemoveDuplicatesFromSortedArray", "algorithm") {
    Solution soln;
    std::vector<int> testCase0{0};
    std::vector<int> testCase1{0, 0};
    std::vector<int> testCase2{0, 0, 1};
    std::vector<int> testCase3{0, 1, 2};
    std::vector<int> testCase4{0, 1, 1, 2};
    std::vector<int> testCase5{0, 1, 1, 1};
    std::vector<int> testCase6{0, 2, 2, 3, 3, 3, 3};
    std::vector<int> testCase7{0, 0, 1, 1, 1, 2, 2, 3, 3, 4};

    CHECK(soln.removeDuplicates(testCase0) == 1);
    CHECK(soln.removeDuplicates(testCase1) == 1);
    CHECK(soln.removeDuplicates(testCase2) == 2);
    CHECK(soln.removeDuplicates(testCase3) == 3);
    CHECK(soln.removeDuplicates(testCase4) == 3);
    CHECK(soln.removeDuplicates(testCase5) == 2);
    CHECK(soln.removeDuplicates(testCase6) == 3);
    CHECK(soln.removeDuplicates(testCase7) == 5);
}