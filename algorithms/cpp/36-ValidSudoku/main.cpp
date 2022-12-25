//
// Created by Benjamin Lee on 12/25/22.
// https://leetcode.com/problems/valid-sudoku/
//

/*
 * There are 3 main criteria for this as well as multiple methods to attack this.
 * 1. Each row must contain the digits 1-9 without repetition
 * 2. Each col must contain the digits 1-9 without repetition
 * 3. Each 3x3 sub-boxes must contain the digits 1-9 without repetition
 *
 * In this problem, we are not seeing if the sudoku is solvable, but rather if it is "valid" in the sense that all
 * 3 cases are valid.
 *
 * Our approaches can be to use different containers
 *
 * 1. Hash Map
 * 2. Array (this will be a 9 element array, where each element represents the digit)
 * 3. Bitmasks
 *
 * Additionally, we can also optimize by minimizing passes. This can be done going through all values once and properly
 * defining which container.
 *
 * For this we would need to use
 * 9 containers for sub-boxes
 * 9 containers for rows
 * 9 containers for cols
 *
 * The trick here is properly mapping the col/row into the proper sub-box index. And for this, we simply use division
 *
 * For hashmaps and arrays
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 *
 * With bitmaps, we can "compress" our space
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <map>

class Solution {
public:
#ifdef BRUTE
    bool valid3x3(std::vector<std::vector<char>>& board, int offx, int offy) {
        std::map<char, int> counts;
        for (int i=offy;i<offy + 3;++i) {
            for (int j=offx;j<offx + 3;++j) {
                auto ch = board[i][j];
                if (ch >= '0') {
                    if (counts[ch]++) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool isValidSudoku(std::vector<std::vector<char>>& board) {
        // Brute force will check each 3x3
        for (int i=0;i<3;++i) {
            for (int j=0;j<3;++j) {
                if (!valid3x3(board, i * 3, j * 3)) {
                    return false;
                }
            }
        }

        // Now we have to test each row and col
        for (int i=0;i<9;++i) {
            std::map<char, int> counts;
            for (int j=0;j<9;++j) {
                auto ch = board[i][j];
                if (ch >= '0') {
                    if (counts[ch]++) {
                        return false;
                    }
                }
            }
        }

        for (int j=0;j<9;++j) {
            std::map<char, int> counts;
            for (int i=0;i<9;++i) {
                auto ch = board[i][j];
                if (ch >= '0') {
                    if (counts[ch]++) {
                        return false;
                    }
                }
            }
        }

        return true;
    }
#else
    bool isValidSudoku(std::vector<std::vector<char>>& board) {
        std::vector<std::map<char, int>> rows(board.size());
        std::vector<std::map<char, int>> cols(board.size());
        std::vector<std::map<char, int>> boxes(board.size());

        for (int i=0;i<9;++i) {
            for (int j = 0;j < 9;++j) {
                auto ch = board[i][j];
                if (ch >= '0') {
                    // Rows
                    if (rows[i][ch]++) {
                        return false;
                    }

                    // Cols
                    if (cols[j][ch]++) {
                        return false;
                    }

                    // Boxes
                    int index = j / 3 + (i / 3) * 3;
                    if (boxes[index][ch]++) {
                        return false;
                    }
                }
            }
        }

        return true;
    }
#endif /* BRUTE */
};

TEST_CASE("ValidSudoku", "algorithm") {
    Solution soln;
    std::vector<std::vector<char>> board0{
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}};
    std::vector<std::vector<char>> board1{
        {'8','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}};
    std::vector<std::vector<char>> board2{
        {'.','.','.','.','5','.','.','1','.'},
        {'.','4','.','3','.','.','.','.','.'},
        {'.','.','.','.','.','3','.','.','1'},
        {'8','.','.','.','.','.','.','2','.'},
        {'.','.','2','.','7','.','.','.','.'},
        {'.','1','5','.','.','.','.','.','.'},
        {'.','.','.','.','.','2','.','.','.'},
        {'.','2','.','9','.','.','.','.','.'},
        {'.','.','4','.','.','.','.','.','.'}};

    CHECK(soln.isValidSudoku(board2) == false);
    CHECK(soln.isValidSudoku(board0) == true);
    CHECK(soln.isValidSudoku(board1) == false);
}

