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

add_executable(palindrome-number 9-PalindromeNumber/main.cpp)
target_link_libraries(palindrome-number PRIVATE Catch2::Catch2WithMain)

add_executable(roman-to-integer 13-RomanToInteger/main.cpp)
target_link_libraries(roman-to-integer PRIVATE Catch2::Catch2WithMain)

add_executable(longest-common-prefix 14-LongestCommonPrefix/main.cpp 20-ValidParentheses/main.cpp)
target_link_libraries(longest-common-prefix PRIVATE Catch2::Catch2WithMain)

add_executable(valid-parentheses 20-ValidParentheses/main.cpp)
target_link_libraries(valid-parentheses PRIVATE Catch2::Catch2WithMain)

add_executable(merge-two-sorted-lists 21-MergeTwoSortedLists/main.cpp)
target_link_libraries(merge-two-sorted-lists PRIVATE Catch2::Catch2WithMain)

add_executable(remove-duplicates-from-sorted-array 26-RemoveDuplicatesFromSortedArray/main.cpp)
target_link_libraries(remove-duplicates-from-sorted-array PRIVATE Catch2::Catch2WithMain)

add_executable(remove-element 27-RemoveElement/main.cpp)
target_link_libraries(remove-element PRIVATE Catch2::Catch2WithMain)

add_executable(search-insert-position 35-SearchInsertPosition/main.cpp)
target_link_libraries(search-insert-position PRIVATE Catch2::Catch2WithMain)

add_executable(length-of-last-word 58-LengthOfLastWord/main.cpp)
target_link_libraries(length-of-last-word PRIVATE Catch2::Catch2WithMain)

add_executable(plus-one 66-PlusOne/main.cpp)
target_link_libraries(plus-one PRIVATE Catch2::Catch2WithMain)

add_executable(add-binary 67-AddBinary/main.cpp)
target_link_libraries(add-binary PRIVATE Catch2::Catch2WithMain)

add_executable(odd-even-linked-list 328-OddEvenLinkedList/main.cpp)
target_link_libraries(odd-even-linked-list PRIVATE Catch2::Catch2WithMain)

add_executable(leaf-similar-trees 872-LeafSimilarTrees/main.cpp)
target_link_libraries(leaf-similar-trees PRIVATE Catch2::Catch2WithMain)

add_executable(middle-of-the-linked-list 876-MiddleOfTheLinkedList/main.cpp)
target_link_libraries(middle-of-the-linked-list PRIVATE Catch2::Catch2WithMain)

add_executable(range-sum-of-bst 938-RangeSumOfBST/main.cpp)
target_link_libraries(range-sum-of-bst PRIVATE Catch2::Catch2WithMain)

add_executable(string-halves-alike 1704-StringHalvesAlike/main.cpp 9-PalindromeNumber/main.cpp)
target_link_libraries(string-halves-alike PRIVATE Catch2::Catch2WithMain)
