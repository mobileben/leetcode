//
// Created by Benjamin Lee on 1/15/23.
// https://leetcode.com/problems/moving-average-from-data-stream/
// Easy
// Topics: Array, Design, Queue, Data Stream
//

/*
 * One can use a queue to solve this
 *
 * Time Complexity: O(1)
 * Space Complexity: O(n), where n is the size of the moving average
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <cassert>
#include <queue>

class MovingAverage {
public:
    static std::vector<std::string> execute(std::vector<std::string>& commands, std::vector<std::vector<int>>& args) {
        assert(commands.size() == args.size());

        std::vector<std::string> results;
        MovingAverage *moving = nullptr;

        for (int i=0;i<commands.size();++i) {
            auto cmd = commands[i];
            auto arg = args[i];

            if (cmd == "MovingAverage") {
                moving = new MovingAverage(arg.front());
                results.push_back("null");
            } else if (cmd == "next") {
                if (moving) {
                    results.push_back(std::to_string(moving->next(arg.front())));
                }
            } else {
                assert(false);
            }
        }
        if (moving) {
            delete moving;
        }
        return results;
    }

    int size;
    std::queue<int> queue;
    int sum = 0;

    MovingAverage(int size) : size(size) {
    }

    double next(int val) {
        if (queue.size() == size) {
            auto top = queue.front();
            queue.pop();
            sum -= top;
        }
        queue.push(val);
        sum += val;
        return static_cast<double>(sum) / static_cast<double>(queue.size());
    }
};

TEST_CASE("MovingAverageFromDataStream", "algorithm") {
    std::vector<std::string> cmds0{"MovingAverage", "next", "next", "next", "next"};
    std::vector<std::vector<int>> args0{{3}, {1}, {10}, {3}, {5}};

    CHECK(MovingAverage::execute(cmds0, args0) == std::vector<std::string>{"null", "1.0", "5.5", "4.66667", "6.0"});
}
