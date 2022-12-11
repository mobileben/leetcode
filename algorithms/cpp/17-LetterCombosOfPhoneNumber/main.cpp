//
// Created by Benjamin Lee on 12/9/22.
// https://leetcode.com/problems/letter-combinations-of-a-phone-number/
//

/*
 * Due to the limited requirements of this problem (eg. 4 digits max), we can brute force this more easily and just
 * generate all the permutations.
 *
 * We can treat generating the permutations as a simple exericse of counting up the numbers similar to "binary numbers".
 *
 * Another method is to use is backtracking which is a common method to use for generating permutations.
 *
 * Time is dictated by the number of iterations for permutations. We best use 4, which is the max number of digits a
 * number can have.
 *
 * Time Complexity: O(4^n * n)
 * Space Complexity: O(n)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#define BACKTRACKING

class Solution {
public:
    std::vector<std::vector<char>> letters{
            { 'a', 'b', 'c' },   // 2
            { 'd', 'e', 'f' },   // 3
            { 'g', 'h', 'i' },   // 4
            { 'j', 'k', 'l' },   // 5
            { 'm', 'n', 'o' },   // 6
            { 'p', 'q', 'r', 's' }, // 7
            { 't', 'u', 'v' },   // 8
            { 'w', 'x', 'y', 'z'}   // 9
    };

#ifdef BACKTRACKING
    std::vector<std::string> results;

    void backtrack(int index, std::string str, std::string const &digits) {
        if (str.length() >= digits.length()) {
            results.push_back(str);
            return;
        }

        auto idx = digits[index] - '0' - 2;
        auto const &lets = letters[idx];
        for (auto ch : lets) {
            str += ch;
            backtrack(index + 1, str, digits);
            str.pop_back();
        }
    }

    std::vector<std::string> letterCombinations(std::string digits) {
        results.clear();

        if (digits.size()) {
            backtrack(0, "", digits);
        }
        return results;
    }

#else
    std::vector<std::string> letterCombinations(std::string digits) {
        // Trivial rejection
        if (digits.empty()) return {};

        int len = digits.length();
        std::vector<int> counters(len);
        std::vector<int> limits(len);
        int total = 1;

        for (auto i=0;i<len;++i) {
            // Valid range is 2-9, so subtract 2 for index 0
            auto index = digits[i] - '0' - 2;
            limits[i] = letters[index].size();
            total *= limits[i];
        }

        std::vector<std::string> results;

        for (int i=0;i<total;++i) {
            int carry = 1;
            std::string out;
            for (int j=len-1;j>=0;--j) {
                auto& count = counters[j];
                auto index = digits[j] - '0' - 2;

                out.push_back(letters[index][count]);

                count += carry;
                if (count >= limits[j]) {
                    count = 0;
                    carry = 1;
                } else {
                    carry = 0;
                }
            }

            std::reverse(out.begin(), out.end());
            results.push_back(out);
        }

        return results;
    }
#endif /* BACKTRACKING */
};

TEST_CASE("LetterCombinationsOfAPhoneNumber", "algorithm") {
    Solution soln;
    std::string testCase0 = "";
    std::string testCase1 = "2";
    std::string testCase2 = "23";
    std::string testCase3 = "273";
    std::string testCase4 = "9949";

    auto actual1 = soln.letterCombinations(testCase1);
    auto actual3 = soln.letterCombinations(testCase3);
    auto actual0 = soln.letterCombinations(testCase0);
    auto actual2 = soln.letterCombinations(testCase2);
    auto actual4 = soln.letterCombinations(testCase4);

    std::vector<std::string> expected0{};
    std::vector<std::string> expected1{"a", "b", "c"};
    std::vector<std::string> expected2{ "ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf" };
    std::vector<std::string> expected3{ "apd", "ape", "apf", "aqd", "aqe", "aqf", "ard", "are", "arf", "asd",
                                        "ase", "asf", "bpd", "bpe", "bpf", "bqd", "bqe", "bqf", "brd", "bre", "brf",
                                        "bsd", "bse", "bsf", "cpd", "cpe", "cpf", "cqd", "cqe", "cqf", "crd", "cre",
                                        "crf", "csd", "cse", "csf" };
    std::vector<std::string> expected4{ "wwgw", "wwgx", "wwgy", "wwgz", "wwhw", "wwhx", "wwhy", "wwhz", "wwiw",
                                        "wwix", "wwiy", "wwiz", "wxgw", "wxgx", "wxgy", "wxgz", "wxhw", "wxhx",
                                        "wxhy", "wxhz", "wxiw", "wxix", "wxiy", "wxiz", "wygw", "wygx", "wygy",
                                        "wygz", "wyhw", "wyhx", "wyhy", "wyhz", "wyiw", "wyix", "wyiy", "wyiz",
                                        "wzgw", "wzgx", "wzgy", "wzgz", "wzhw", "wzhx", "wzhy", "wzhz", "wziw",
                                        "wzix", "wziy", "wziz", "xwgw", "xwgx", "xwgy", "xwgz", "xwhw", "xwhx",
                                        "xwhy", "xwhz", "xwiw", "xwix", "xwiy", "xwiz", "xxgw", "xxgx", "xxgy",
                                        "xxgz", "xxhw", "xxhx", "xxhy", "xxhz", "xxiw", "xxix", "xxiy", "xxiz",
                                        "xygw", "xygx", "xygy", "xygz", "xyhw", "xyhx", "xyhy", "xyhz", "xyiw",
                                        "xyix", "xyiy", "xyiz", "xzgw", "xzgx", "xzgy", "xzgz", "xzhw", "xzhx",
                                        "xzhy", "xzhz", "xziw", "xzix", "xziy", "xziz", "ywgw", "ywgx", "ywgy",
                                        "ywgz", "ywhw", "ywhx", "ywhy", "ywhz", "ywiw", "ywix", "ywiy", "ywiz",
                                        "yxgw", "yxgx", "yxgy", "yxgz", "yxhw", "yxhx", "yxhy", "yxhz", "yxiw",
                                        "yxix", "yxiy", "yxiz", "yygw", "yygx", "yygy", "yygz", "yyhw", "yyhx",
                                        "yyhy", "yyhz", "yyiw", "yyix", "yyiy", "yyiz", "yzgw", "yzgx", "yzgy",
                                        "yzgz", "yzhw", "yzhx", "yzhy", "yzhz", "yziw", "yzix", "yziy", "yziz",
                                        "zwgw", "zwgx", "zwgy", "zwgz", "zwhw", "zwhx", "zwhy", "zwhz", "zwiw",
                                        "zwix", "zwiy", "zwiz", "zxgw", "zxgx", "zxgy", "zxgz", "zxhw", "zxhx",
                                        "zxhy", "zxhz", "zxiw", "zxix", "zxiy", "zxiz", "zygw", "zygx", "zygy",
                                        "zygz", "zyhw", "zyhx", "zyhy", "zyhz", "zyiw", "zyix", "zyiy", "zyiz",
                                        "zzgw", "zzgx", "zzgy", "zzgz", "zzhw", "zzhx", "zzhy", "zzhz", "zziw",
                                        "zzix", "zziy", "zziz" };

    CHECK(actual0 == expected0);
    CHECK(actual1 == expected1);
    CHECK(actual2 == expected2);
    CHECK(actual3 == expected3);
    CHECK(actual4 == expected4);
}

