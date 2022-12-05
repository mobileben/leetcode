cmake_minimum_required(VERSION 3.21)
project(leetcode)

set(CMAKE_CXX_STANDARD 17)

find_package(Catch2 3 REQUIRED)

include_directories(/usr/local/include)

add_executable(two-sum 1-TwoSum/main.cpp)
target_link_libraries(two-sum PRIVATE Catch2::Catch2WithMain)

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

add_executable(string-halves-alike 1704-StringHalvesAlike/main.cpp 9-PalindromeNumber/main.cpp)
target_link_libraries(string-halves-alike PRIVATE Catch2::Catch2WithMain)
