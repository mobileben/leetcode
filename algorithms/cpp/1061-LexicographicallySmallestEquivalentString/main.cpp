//
// Created by Benjamin Lee on 1/14/23.
// https://leetcode.com/problems/lexicographically-smallest-equivalent-string/
// Medium
// Topics: String, Union Find

/*
 * There is a brute force method that is truly brutish. This utilizes hash maps and does several passes, building up
 * the associations between them. This requires 4 passes, with the worse pass being roughly O(m^3).
 *
 * This is slow and does not have TLE, but the % Beats is pretty low.
 *
 * Time Complexity: O(m^3), isn't really m^3, since we do have a triple nested loop.
 * Space Complexity: O(n)
 *
 * This turns into a graph problem. We can build an adjacency list representing the relationship between s1 and s2.
 * Then for each letter, we can perform a Depth-First Search (DFS) to find the smallest character for the nodes
 * in a connected section of the graph.
 *
 * Time Complexity: O(N+M+|∑|^2), where N is s1 length, M is baseStr length, and ∑ is the number of unique chars
 * Space Complexity: O(|∑|^2), where ∑ is the number of unique chars. Note DFS will also have recursion stack space
 *
 * The other approach to this problem is to do a Disjoint Set Union
 *
 * Time Complexity: O((N + M)log|∑|), where N is s1 length, M is baseStr length, and ∑ is the number of unique chars
 * Space Complexity: O(|∑|), ∑ is the number of unique characters
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <array>
#include <unordered_map>
#include <unordered_set>

class Solution {
public:
#ifdef BRUTE
    std::string smallestEquivalentString(std::string s1, std::string& s2, std::string baseStr) {
        std::unordered_map<char, std::unordered_set<char>> mapping;
        std::vector<char> m(26);
        std::iota(m.begin(), m.end(), 'a');

        for (int i=0;i<s1.size();++i) {
            char c1 = s1[i];
            char c2 = s2[i];
            mapping[c1].insert(c1);
            mapping[c2].insert(c2);
            mapping[c1].insert(c2);
            mapping[c2].insert(c1);
        }

        for (auto it : mapping) {
            for (auto s : it.second) {
                auto child = mapping[s];
                mapping[it.first].insert(mapping[s].begin(), mapping[s].end());
            }
        }

        for (auto it : mapping) {
            for (auto s : it.second) {
                auto child = mapping[s];
                for (auto t : child) {
                    mapping[it.first].insert(mapping[t].begin(), mapping[t].end());
                }
            }
        }

        for (auto it : mapping) {
            char smallest = 'z';
            for (auto s : it.second) {
                if (s < smallest) {
                    smallest = s;
                }
            }

            m[it.first - 'a'] = smallest;

        }
        for (int i=0;i<baseStr.length();++i) {
            baseStr[i] = m[baseStr[i] - 'a'];
        }

        return baseStr;
    }
#else

    void dfs(char ch, char& min, std::unordered_map<char, std::unordered_set<char>>& adj, std::array<bool, 26>& visited) {
        visited[ch - 'a'] = true;

        min = std::min(min, ch);

        for (auto child : adj[ch]) {
            if (!visited[child - 'a']) {
                dfs(child, min, adj, visited);
            }
        }
    }

    std::string smallestEquivalentString(std::string s1, std::string& s2, std::string baseStr) {
        // Instead of map/set, could use array of length 26 to hold results
        std::unordered_map<char, std::unordered_set<char>> adj;
        std::array<bool, 26> visited;

        for (int i=0;i<s1.size();++i) {
            adj[s1[i]].insert(s2[i]);
            adj[s2[i]].insert(s1[i]);
        }

        std::array<char, 26> lets;
        std::iota(lets.begin(), lets.end(), 'a');

        for (auto& it : adj) {
            visited = {0};
            char ch = it.first;
            dfs(it.first, ch, adj, visited);

            int index = it.first - 'a';
            if (ch < lets[index]) {
                lets[index] = ch;
            }
        }

        for (int i=0;i<baseStr.length();++i) {
            baseStr[i] = lets[baseStr[i] - 'a'];
        }

        return baseStr;
    }
#endif /* BRUTE */
};

TEST_CASE("LexicographicallySmallestEquivalentString", "algorithm") {
    Solution soln;
    std::string s1_0 = "abc";
    std::string s2_0 = "cde";
    std::string baseStr0 = "eed";
    std::string s1_1 = "parker";
    std::string s2_1 = "morris";
    std::string baseStr1 = "parser";
    std::string s1_2 = "hello";
    std::string s2_2 = "world";
    std::string baseStr2 = "hold";
    std::string s1_3 = "leetcode";
    std::string s2_3 = "programs";
    std::string baseStr3 = "sourcecode";
    std::string s1_4 = "aabbbabbbbbabbbbaabaabbaaabbbabaababaaaabbbbbabbaa";
    std::string s2_4 = "aabbaabbbabaababaabaababbbababbbaaaabbbbbabbbaabaa";
    std::string baseStr4 = "buqpqxmnajphtisernebttymtrydomxnwonfhfjlzzrfhosjct";
    std::string s1_5 = "bbbaacaaaaccccbacbbaaccccacbbbccbcbabbbcbcbcaaacac";
    std::string s2_5 = "aabbccbccabcaccbacabcbccaaaaaaccbbabaabbbbabbabaca";
    std::string baseStr5 = "dwbyvrkacqglybdviivynguhfrlffpkcnoeijzddqhbxxeoefz";

    CHECK(soln.smallestEquivalentString(s1_0, s2_0, baseStr0) == "aab");
    CHECK(soln.smallestEquivalentString(s1_1, s2_1, baseStr1) == "makkek");
    CHECK(soln.smallestEquivalentString(s1_2, s2_2, baseStr2) == "hdld");
    CHECK(soln.smallestEquivalentString(s1_3, s2_3, baseStr3) == "aauaaaaada");
    CHECK(soln.smallestEquivalentString(s1_4, s2_4, baseStr4) == "auqpqxmnajphtiserneattymtrydomxnwonfhfjlzzrfhosjct");
    CHECK(soln.smallestEquivalentString(s1_5, s2_5, baseStr5) == "dwayvrkaaqglyadviivynguhfrlffpkanoeijzddqhaxxeoefz");
}
