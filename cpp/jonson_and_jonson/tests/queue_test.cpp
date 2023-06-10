#include <gtest/gtest.h>
#include <queue.h>
#include <utils.h>
#include <thread>
#include <chrono>

using namespace jj;

TEST(test_Queue, push_and_pop)
{
    Queue<int> queue;

    std::vector<int> const arr = {1,2,3,4,5};

    std::vector<int> result;

    auto consum = std::thread([&result,&queue, s = arr.size()]() mutable {
                while (s--) {
                    if (auto msg = queue.pop(); msg) {
                        result.push_back(std::move(*msg));
                    }
                }
            });
    

    for(auto v: arr) {
        queue.push(std::move(v));
    }

    consum.join();

    ASSERT_EQ(result.size(), arr.size());
    for (auto i = 0u; i < arr.size(); ++i) {
        ASSERT_EQ(arr[i], result[i]);
    }
}

TEST(test_Queue, stop)
{
    Queue<int> queue;

    std::vector<int> result;
    constexpr size_t END = 3;

    auto consum = std::thread([&]() {
                while (!queue.stopped()) {
                    if (auto msg = queue.pop(); msg) {
                        result.push_back(std::move(*msg));
                    }
                }
            });

    while(result.size() != END) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        queue.push(1);
    }
    
    queue.stop();

    consum.join();

    ASSERT_EQ(result.size(),END);
}
