//
// Created by Benjamin Lee on 12/27/22.
// https://leetcode.com/problems/count-and-say/
//

/*
 * I'm not a real fan of how this question is phrased.
 *
 * Initial condition is n=1, which is just "1"
 * We look at the previous Count and Say value after this.
 * n = 2, the previous string is "1" which is one "1" == "11"
 * n = 3, the previous string is "11" which is two "1"s == "21"
 * n = 4, the previous string is "21" which is one "2" and one "1" == "1211"
 * n = 5, the previous string is "1211" which is one "1", one "2", and two "1"s == "111221"
 * n = 6, the previous string is "111221" which is three "1"s, two "2"s, and one "1" == "312211"
 *
 * We can also start to see a pattern here. We will need to use recursion
 *
 * For better info on Time/Space complexity, check this.
 * https://leetcode.com/problems/count-and-say/solutions/2506186/count-and-say/?orderBy=most_votes
 *
 * Time Complexity: O(4^(n/3))
 * Space Complexity: O(4^(n/3))
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
    std::string countAndSay(std::string str) {
        std::string results;
        char last = 0;
        int count = 0;

        for (int i=0;i<str.size();++i) {
            auto ch = str[i];
            if (last != ch) {
                if (count) {
                    results += std::to_string(count);
                    results += last;
                }
                last = ch;
                count = 1;
            } else {
                ++count;
            }
        }
        results += std::to_string(count);
        results += last;

        return results;
    }

    std::string countAndSay(int n) {
        std::string str = "1";
        for (int i=1;i<n;++i) {
            str = countAndSay(str);
        }
        return str;
    }
};

TEST_CASE("CountAndSay", "algorithm") {
    Solution soln;

    CHECK(soln.countAndSay(4) == "1211");
    CHECK(soln.countAndSay(1) == "1");
    CHECK(soln.countAndSay(2) == "11");
    CHECK(soln.countAndSay(3) == "21");
    CHECK(soln.countAndSay(5) == "111221");
    CHECK(soln.countAndSay(6) == "312211");
}

