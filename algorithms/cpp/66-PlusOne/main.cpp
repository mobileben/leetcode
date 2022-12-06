//
// Created by Benjamin Lee on 12/5/22.
// https://leetcode.com/problems/plus-one/
//

/*
 * The key item here is handling the value 9 and whether or not we will need to add a new digit.
 *
 * We have to increase the vector if our first most digit (ie. index == 0) is 9 *and* there is a carry.
 *
 * The instructions are not clear on if we can overwrite the incoming argument digits. So we'll implement one that
 * creates a new vector (NEW_VECTOR) and one that will overwrite.
 *
 * We can further optimize the in place variant by finishing early if there is no carry. This cannot be applied to
 * NEW_VECTOR as we are copying over the contents.
 *
 * NEW_VECTOR
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * Overwriting
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * Note I am indicating that space complexity will still remain O(n). This is because in theory, the insert we use can
 * cause memory allocation
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
#ifdef NEW_VECTOR
    std::vector<int> plusOne(std::vector<int>& digits) {
        std::vector<int> out;
        out.resize(digits.size());

        int sum = digits.back() + 1;
        int carry = sum > 9 ? 1 : 0;
        out[digits.size() - 1] = carry ? 0 : sum;
        for (int i=digits.size() - 2;i>=0;--i) {
            sum = digits[i] + carry;
            carry = sum > 9 ? 1 : 0;
            out[i]  = carry ? 0 : sum;
        }

        if (carry) {
            out.insert(out.begin(), 1);
        }
        return out;
    }
#else
    std::vector<int> plusOne(std::vector<int>& digits) {
        int sum, carry = 1;
        for (int i=digits.size() - 1;i>=0;--i) {
            sum = digits[i] + carry;
            carry = sum > 9 ? 1 : 0;
            if (!carry) {
                digits[i] = sum;
                break;
            } else {
                digits[i] = 0;
            }
        }

        if (carry) {
            digits.insert(digits.begin(), 1);
        }
        return digits;
    }
#endif /* BRUTE */
};

TEST_CASE("PlusOne", "algorithm") {
    Solution soln;
    std::vector<int> testCase0{1};
    std::vector<int> testCase1{9};
    std::vector<int> testCase2{1, 9};
    std::vector<int> testCase3{1, 9, 1};
    std::vector<int> testCase4{9, 9};
    std::vector<int> testCase5{9, 8, 9};
    std::vector<int> testCase6{1, 2, 3};
    std::vector<int> testCase7{4, 3, 2, 1};

    auto result0 = soln.plusOne(testCase0);
    auto result1 = soln.plusOne(testCase1);
    auto result2 = soln.plusOne(testCase2);
    auto result3 = soln.plusOne(testCase3);
    auto result4 = soln.plusOne(testCase4);
    auto result5 = soln.plusOne(testCase5);
    auto result6 = soln.plusOne(testCase6);
    auto result7 = soln.plusOne(testCase7);

    std::vector<int> expected0{2};
    std::vector<int> expected1{1, 0};
    std::vector<int> expected2{2, 0};
    std::vector<int> expected3{1, 9, 2};
    std::vector<int> expected4{1, 0, 0};
    std::vector<int> expected5{9, 9, 0};
    std::vector<int> expected6{1, 2, 4};
    std::vector<int> expected7{4, 3, 2, 2};

    CHECK(result0 == expected0);
    CHECK(result1 == expected1);
    CHECK(result2 == expected2);
    CHECK(result3 == expected3);
    CHECK(result4 == expected4);
    CHECK(result5 == expected5);
    CHECK(result6 == expected6);
    CHECK(result7 == expected7);
}