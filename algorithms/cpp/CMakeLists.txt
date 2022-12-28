cmake_minimum_required(VERSION 3.21)
project(leetcode)

set(CMAKE_CXX_STANDARD 17)

find_package(Catch2 3 REQUIRED)

include_directories(/usr/local/include)

add_executable(two-sum 1-TwoSum/main.cpp)
target_link_libraries(two-sum PRIVATE Catch2::Catch2WithMain)

add_executable(add-two-numbers 2-AddTwoNumbers/main.cpp)
target_link_libraries(add-two-numbers PRIVATE Catch2::Catch2WithMain)

add_executable(longest-substring-without-repeating-chars 3-LongestSubstringWithoutRepeatingChars/main.cpp)
target_link_libraries(longest-substring-without-repeating-chars Catch2::Catch2WithMain)

add_executable(median-of-two-sorted-arrays 4-MedianOfTwoSortedArrays/main.cpp)
target_link_libraries(median-of-two-sorted-arrays Catch2::Catch2WithMain)

add_executable(longest-palindromic-substring 5-LongestPalindromicSubstring/main.cpp)
target_link_libraries(longest-palindromic-substring Catch2::Catch2WithMain)

add_executable(reverse-integer 7-ReverseInteger/main.cpp)
target_link_libraries(reverse-integer Catch2::Catch2WithMain)

add_executable(string-to-integer 8-StringToInteger/main.cpp)
target_link_libraries(string-to-integer PRIVATE Catch2::Catch2WithMain)

add_executable(palindrome-number 9-PalindromeNumber/main.cpp)
target_link_libraries(palindrome-number PRIVATE Catch2::Catch2WithMain)

add_executable(regular-pattern-matching 10-RegularExpressionMatching/main.cpp)
target_link_libraries(regular-pattern-matching PRIVATE Catch2::Catch2WithMain)

add_executable(container-with-most-water 11-ContainerWithMostWater/main.cpp)
target_link_libraries(container-with-most-water PRIVATE Catch2::Catch2WithMain)

add_executable(roman-to-integer 13-RomanToInteger/main.cpp)
target_link_libraries(roman-to-integer PRIVATE Catch2::Catch2WithMain)

add_executable(longest-common-prefix 14-LongestCommonPrefix/main.cpp)
target_link_libraries(longest-common-prefix PRIVATE Catch2::Catch2WithMain)

add_executable(3sum 15-3Sum/main.cpp)
target_link_libraries(3sum PRIVATE Catch2::Catch2WithMain)

add_executable(letter-combos-phone-num 17-LetterCombosOfPhoneNumber/main.cpp)
target_link_libraries(letter-combos-phone-num PRIVATE Catch2::Catch2WithMain)

add_executable(remove-nth-node-from-end 19-RemoveNthNodeFromEndOfList/main.cpp)
target_link_libraries(remove-nth-node-from-end PRIVATE Catch2::Catch2WithMain)

add_executable(valid-parentheses 20-ValidParentheses/main.cpp)
target_link_libraries(valid-parentheses PRIVATE Catch2::Catch2WithMain)

add_executable(merge-two-sorted-lists 21-MergeTwoSortedLists/main.cpp)
target_link_libraries(merge-two-sorted-lists PRIVATE Catch2::Catch2WithMain)

add_executable(generate-parentheses 22-GenerateParentheses/main.cpp)
target_link_libraries(generate-parentheses PRIVATE Catch2::Catch2WithMain)

add_executable(merge-k-sorted-lists 23-MergeKSortedLists/main.cpp)
target_link_libraries(merge-k-sorted-lists PRIVATE Catch2::Catch2WithMain)

add_executable(remove-duplicates-from-sorted-array 26-RemoveDuplicatesFromSortedArray/main.cpp)
target_link_libraries(remove-duplicates-from-sorted-array PRIVATE Catch2::Catch2WithMain)

add_executable(remove-element 27-RemoveElement/main.cpp)
target_link_libraries(remove-element PRIVATE Catch2::Catch2WithMain)

add_executable(find-index-first-occurrence-in-string 28-FindIndexOfFirstOccurrenceInString/main.cpp)
target_link_libraries(find-index-first-occurrence-in-string PRIVATE Catch2::Catch2WithMain)

add_executable(divide-two-integers 29-DivideTwoIntegers/main.cpp)
target_link_libraries(divide-two-integers PRIVATE Catch2::Catch2WithMain)

add_executable(search-in-rotated-sorted-array 33-SearchInRotatedSortedArray/main.cpp)
target_link_libraries(search-in-rotated-sorted-array PRIVATE Catch2::Catch2WithMain)

add_executable(find-first-and-last-pos-of-elem-in-sorted-array 34-FindFirstLastPosOfElemInSortedArray/main.cpp)
target_link_libraries(find-first-and-last-pos-of-elem-in-sorted-array PRIVATE Catch2::Catch2WithMain)

add_executable(search-insert-position 35-SearchInsertPosition/main.cpp)
target_link_libraries(search-insert-position PRIVATE Catch2::Catch2WithMain)

add_executable(valid-sudoku 36-ValidSudoku/main.cpp)
target_link_libraries(valid-sudoku PRIVATE Catch2::Catch2WithMain)

add_executable(count-and-say 38-CountAndSay/main.cpp)
target_link_libraries(count-and-say PRIVATE Catch2::Catch2WithMain)

add_executable(first-missing-positive 41-FirstMissingPositive/main.cpp)
target_link_libraries(first-missing-positive PRIVATE Catch2::Catch2WithMain)

add_executable(jump-game 55-JumpGame/main.cpp)
target_link_libraries(jump-game PRIVATE Catch2::Catch2WithMain)

add_executable(length-of-last-word 58-LengthOfLastWord/main.cpp)
target_link_libraries(length-of-last-word PRIVATE Catch2::Catch2WithMain)

add_executable(plus-one 66-PlusOne/main.cpp)
target_link_libraries(plus-one PRIVATE Catch2::Catch2WithMain)

add_executable(add-binary 67-AddBinary/main.cpp)
target_link_libraries(add-binary PRIVATE Catch2::Catch2WithMain)

add_executable(climbing-stairs 70-ClimbingStairs/main.cpp)
target_link_libraries(climbing-stairs PRIVATE Catch2::Catch2WithMain)

add_executable(valid-palindrome 125-ValidPalindrome/main.cpp)
target_link_libraries(valid-palindrome PRIVATE Catch2::Catch2WithMain)

add_executable(evaluate-reverse-polish-notation 150-EvaluateReversePolishNotation/main.cpp)
target_link_libraries(evaluate-reverse-polish-notation PRIVATE Catch2::Catch2WithMain)

add_executable(house-robber 198-HouseRobber/main.cpp)
target_link_libraries(house-robber PRIVATE Catch2::Catch2WithMain)

add_executable(implement-queue-using-stacks 232-ImplementQueueUsingStacks/main.cpp)
target_link_libraries(implement-queue-using-stacks PRIVATE Catch2::Catch2WithMain)

add_executable(odd-even-linked-list 328-OddEvenLinkedList/main.cpp)
target_link_libraries(odd-even-linked-list PRIVATE Catch2::Catch2WithMain)

add_executable(daily-temperatures 739-DailyTemperatures/main.cpp)
target_link_libraries(daily-temperatures PRIVATE Catch2::Catch2WithMain)

add_executable(keys-and-rooms 841-KeysAndRooms/main.cpp)
target_link_libraries(keys-and-rooms PRIVATE Catch2::Catch2WithMain)

add_executable(leaf-similar-trees 872-LeafSimilarTrees/main.cpp)
target_link_libraries(leaf-similar-trees PRIVATE Catch2::Catch2WithMain)

add_executable(middle-of-the-linked-list 876-MiddleOfTheLinkedList/main.cpp)
target_link_libraries(middle-of-the-linked-list PRIVATE Catch2::Catch2WithMain)

add_executable(possible-bipartition 886-PossibleBipartition/main.cpp)
target_link_libraries(possible-bipartition PRIVATE Catch2::Catch2WithMain)

add_executable(minimum-falling-path-sum 931-MinimumFallingPathSum/main.cpp)
target_link_libraries(minimum-falling-path-sum PRIVATE Catch2::Catch2WithMain)

add_executable(range-sum-of-bst 938-RangeSumOfBST/main.cpp)
target_link_libraries(range-sum-of-bst PRIVATE Catch2::Catch2WithMain)

add_executable(maximum-difference-between-node-and-ancestor 1026-MaximumDifferenceBetweenNodeAndAncestor/main.cpp)
target_link_libraries(maximum-difference-between-node-and-ancestor PRIVATE Catch2::Catch2WithMain)

add_executable(longest-common-subsequence 1143-LongestCommonSubsequence/main.cpp)
target_link_libraries(longest-common-subsequence PRIVATE Catch2::Catch2WithMain)

add_executable(string-halves-alike 1704-StringHalvesAlike/main.cpp)
target_link_libraries(string-halves-alike PRIVATE Catch2::Catch2WithMain)

add_executable(remove-stones-to-minimize-the-total 1962-RemoveStonesToMinTotal/main.cpp)
target_link_libraries(remove-stones-to-minimize-the-total PRIVATE Catch2::Catch2WithMain)

add_executable(find-if-path-exists-in-graph 1971-FindIfPathExistsInGraph/main.cpp)
target_link_libraries(find-if-path-exists-in-graph PRIVATE Catch2::Catch2WithMain)

add_executable(max-bags-with-full-capacity-rocks 2279-MaxBagsWithFullCapacityRocks/main.cpp)
target_link_libraries(max-bags-with-full-capacity-rocks PRIVATE Catch2::Catch2WithMain)

add_executable(longest-subsequence-with-limited-sum 2389-LongestSubsequenceWithLimitedSum/main.cpp)
target_link_libraries(longest-subsequence-with-limited-sum PRIVATE Catch2::Catch2WithMain)
