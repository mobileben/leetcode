//
// Created by Benjamin Lee on 12/7/22.
// https://leetcode.com/problems/longest-palindromic-substring/
//

/*
 * The brute force method for this is going through every possible starting and ending position and verifying that is
 * a palindrome. However this method will result in Time Limit Exceeded (TLE) on LeetCode.
 *
 * Time Complexity: O(n^3)
 * Space Complexity: O(1)
 *
 * Probably the easiest to visual method that won't result in TLE is iterating through the string and for each iteration,
 * expand from that index (and the index to the right) to determine if there is a palindrome.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 *
 * What interviewers are more than likely looking for here is a dynamic programming solution.
 *
 * With dynamic programming, the algorithm can be distilled down to
 *
 * In the examples below
 * len = substring length + 1
 * ends = ending index of substring
 *
 * First row of 0 is substring of length 1, and hence is always 1
 *
 * "babad"
 *       ends
 *     0 1 2 3 4
 *   0 1 1 1 1 1    // substring length 1
 * l 1   0 0 0 0    // substring length 2
 * e 2     1 1 0    // substring length 3
 * n 3       0 0    // substring length 4
 *   4         0    // substring length 5
 *
 * "cabbac"
 *       ends
 *     0 1 2 3 4 5
 *   0 1 1 1 1 1 1  // substring length 1
 * l 1   0 0 1 0 0  // substring length 2
 * e 2     0 0 0 0  // substring length 3
 * n 3       0 1 0  // substring length 4
 *   4         0 0  // substring length 5
 *   5           1  // substring length 6
 *
 * i will be representative of len
 * j will be representative of ends
 *
 * We have a potential substring when the start and end of the substring match and the inner substring is a palindrome
 *
 * dp[i, j] = s[j] == s[j-i] && dp[i-1][j-2]
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 *
 * The fastest way to solve this is to use Manacher's Algorithm, and is considered out of scope for someone to
 * come up with (unless thy already were familiar with or memorized it).
 * https://en.wikipedia.org/wiki/Longest_palindromic_substring#Manacher's_algorithm
 *
 * Time Complexity: O(n)
 *
 */
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#define DP

class Solution {
public:
#ifdef BRUTE
    bool isPalindrome(std::string s, int start, int end) {
        while (start <= end) {
            if (s[start] != s[end]) {
                return false;
            }
            ++start;
            --end;
        }

        return true;
    }

    std::string longestPalindrome(std::string s) {
        // Trivial rejection
        if (s.empty()) return "";

        int longest = 0;
        int li = 0, lj = 0;
        for (int i=0;i<s.length();++i) {
            for (auto j=i;j<s.length();++j) {
                if (isPalindrome(s, i, j)) {
                    auto diff = j - i + 1;
                    if (diff > longest) {
                        longest = diff;
                        li = i;
                        lj = j;
                    }
                }

            }
        }
        return s.substr(li, lj-li+1);
    }
#elif defined(DP)
    std::string longestPalindrome(std::string s) {
        int len = s.length();
        // Trivial rejection
        if (len < 2) {
            return s;
        } else if (len == 2) {
            if (s[0] == s[1]) {
                return s;
            } else {
                return std::string{s[0]};
            }
        }

        std::vector<std::vector<bool>> dp(len, std::vector<bool>(len, false));
        int longest = 0;
        int start = 0;

        // Pre-fill
        for (int i=0;i<len;++i) {
            dp[0][i] = true;
            if (i < len - 1) {
                if (s[i] == s[i + 1]) {
                    dp[1][i + 1] = true;
                    if (!longest) {
                        longest = 1;
                        start = i;
                    }
                }
            }
        }

        for (int i=2;i<len;i++) {
            for (int j=0;j<len-i;j++) {
                auto end = j + i;
                if (s[j] == s[end] && dp[i-2][end-1]) {
                    dp[i][end] = true;
                    if (i > longest) {
                        longest = i;
                        start = j;
                    }
                }
            }
        }

        return s.substr(start, longest+1);
    }
#else
    int expandAroundCenter(std::string s, int start, int end) {
        // We expand from around center
        // We must stop if either our left side (start) or our right side (end) goes out of bounds
        while (start >= 0 && end < s.length() && s[start] == s[end]) {
            --start;
            ++end;
        }
        return end - start - 1;
    }

    std::string longestPalindrome(std::string s) {
        // Trivial rejection
        if (s.empty()) return "";

        int start = 0, end = 0;
        int longest = 0;

        for (int i=0;i<s.length();++i) {
            auto len1 = expandAroundCenter(s, i, i);     // This is for the odd case (eg. aba)
            auto len2 = expandAroundCenter(s, i, i + 1); // This is for the even case (eg. abba)
            auto len = std::max(len1, len2);
            if (len > longest) {
                longest = len;
                start = i - (len - 1) / 2;
                end = i + len / 2;
            }
        }
        return s.substr(start, end - start + 1);
    }
#endif /* BRUTE */
};

TEST_CASE("Longest Palindromic Substring", "algorithm") {
    Solution soln;
    const std::string testCase0 = "babad";
    const std::string testCase1 = "cbbd";
    const std::string testCase2 = "cbbdzabbazjsdkjfd";
    const std::string testCase3 = "a";
    const std::string testCase4 = "bb";
    const std::string testCase5 = "zudfweormatjycujjirzjpyrmaxurectxrtqedmmgergwdvjmjtstdhcihacqnothgttgqfywcpgnuvwglvfiuxteopoyizgehkwuvvkqxbnufkcbodlhdmbqyghkojrgokpwdhtdrwmvdegwycecrgjvuexlguayzcammupgeskrvpthrmwqaqsdcgycdupykppiyhwzwcplivjnnvwhqkkxildtyjltklcokcrgqnnwzzeuqioyahqpuskkpbxhvzvqyhlegmoviogzwuiqahiouhnecjwysmtarjjdjqdrkljawzasriouuiqkcwwqsxifbndjmyprdozhwaoibpqrthpcjphgsfbeqrqqoqiqqdicvybzxhklehzzapbvcyleljawowluqgxxwlrymzojshlwkmzwpixgfjljkmwdtjeabgyrpbqyyykmoaqdambpkyyvukalbrzoyoufjqeftniddsfqnilxlplselqatdgjziphvrbokofvuerpsvqmzakbyzxtxvyanvjpfyvyiivqusfrsufjanmfibgrkwtiuoykiavpbqeyfsuteuxxjiyxvlvgmehycdvxdorpepmsinvmyzeqeiikajopqedyopirmhymozernxzaueljjrhcsofwyddkpnvcvzixdjknikyhzmstvbducjcoyoeoaqruuewclzqqqxzpgykrkygxnmlsrjudoaejxkipkgmcoqtxhelvsizgdwdyjwuumazxfstoaxeqqxoqezakdqjwpkrbldpcbbxexquqrznavcrprnydufsidakvrpuzgfisdxreldbqfizngtrilnbqboxwmwienlkmmiuifrvytukcqcpeqdwwucymgvyrektsnfijdcdoawbcwkkjkqwzffnuqituihjaklvthulmcjrhqcyzvekzqlxgddjoir";
    const std::string testCase6 = "ibvjkmpyzsifuxcabqqpahjdeuzaybqsrsmbfplxycsafogotliyvhxjtkrbzqxlyfwujzhkdafhebvsdhkkdbhlhmaoxmbkqiwiusngkbdhlvxdyvnjrzvxmukvdfobzlmvnbnilnsyrgoygfdzjlymhprcpxsnxpcafctikxxybcusgjwmfklkffehbvlhvxfiddznwumxosomfbgxoruoqrhezgsgidgcfzbtdftjxeahriirqgxbhicoxavquhbkaomrroghdnfkknyigsluqebaqrtcwgmlnvmxoagisdmsokeznjsnwpxygjjptvyjjkbmkxvlivinmpnpxgmmorkasebngirckqcawgevljplkkgextudqaodwqmfljljhrujoerycoojwwgtklypicgkyaboqjfivbeqdlonxeidgxsyzugkntoevwfuxovazcyayvwbcqswzhytlmtmrtwpikgacnpkbwgfmpavzyjoxughwhvlsxsgttbcyrlkaarngeoaldsdtjncivhcfsaohmdhgbwkuemcembmlwbwquxfaiukoqvzmgoeppieztdacvwngbkcxknbytvztodbfnjhbtwpjlzuajnlzfmmujhcggpdcwdquutdiubgcvnxvgspmfumeqrofewynizvynavjzkbpkuxxvkjujectdyfwygnfsukvzflcuxxzvxzravzznpxttduajhbsyiywpqunnarabcroljwcbdydagachbobkcvudkoddldaucwruobfylfhyvjuynjrosxczgjwudpxaqwnboxgxybnngxxhibesiaxkicinikzzmonftqkcudlzfzutplbycejmkpxcygsafzkgudy";
    const std::string testCase7 = "ccd";

    CHECK(soln.longestPalindrome(testCase7) == "cc");
    CHECK(soln.longestPalindrome(testCase0) == "bab");
    CHECK(soln.longestPalindrome(testCase1) == "bb");
    CHECK(soln.longestPalindrome(testCase2) == "zabbaz");
    CHECK(soln.longestPalindrome(testCase3) == "a");
    CHECK(soln.longestPalindrome(testCase4) == "bb");
    CHECK(soln.longestPalindrome(testCase5) == "gykrkyg");
    CHECK(soln.longestPalindrome(testCase6) == "fklkf");
}

