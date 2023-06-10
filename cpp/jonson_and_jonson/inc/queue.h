#ifndef JJ_QUEUE_H_
#define JJ_QUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>
#include <log.h>
#include <atomic>
#include <optional>

namespace jj {


    // simple queue thread safe
    template <typename MSG>
    class Queue {
        std::queue<MSG> queue_;
        std::mutex mutex_;
        std::condition_variable cond_;
        std::atomic_bool stop_ = false;

        public:

        Queue() = default;
        Queue(Queue &&) = delete;
        Queue(Queue const&) = delete;
        ~Queue() = default;

        void push(MSG&& msg) {

            std::lock_guard<std::mutex> lock(mutex_);

            queue_.push(std::move(msg));
            cond_.notify_one();
        }

        auto pop() -> std::optional<MSG> {

            std::unique_lock<std::mutex> lock(mutex_);
            cond_.wait(lock, [this] { return !queue_.empty() || stop_; });

            if (stop_) { return {}; }

            auto msg = queue_.front();
            queue_.pop();

            return msg;
        }

        void stop() {
            stop_ = true;
            cond_.notify_one();
        }

        auto stopped() ->  bool {
            return stop_;
        }
    };


}  // namespace jj {
#endif // JJ_QUEUE_H_
