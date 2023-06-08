#ifndef JJ_QUEUE_H_
#define JJ_QUEUE_H_

#include <queue>
#ifdef MUTEX_QUEUE
#include <atomic>
#else
#include <mutex>
#include <condition_variable>
#endif
#include <log.h>

namespace jj {

#ifdef MUTEX_QUEUE

    template<class MSG>
    class Queue
    {
        std::queue<MSG> queue_;
        std::atomic_flag lock_ = ATOMIC_FLAG_INIT;

        public:

        void push(MSG && msg) {

            LOG_DBG(msg);
            while (lock_.test_and_set(std::memory_order_acquire)) ;

            queue_.push(std::move(msg));

            lock_.clear(std::memory_order_release);
        }

        auto pop() -> MSG {

            while (lock_.test_and_set(std::memory_order_acquire)) ;

            auto msg = queue_.front();
            queue_.pop();

            LOG_DBG("poped ", msg);

            lock_.clear(std::memory_order_release);

            return msg;
        }
    };

    //

#else

    template <typename MSG>
    class Queue {
        std::queue<MSG> queue_;
        std::mutex mutex_;
        std::condition_variable cond_;

        public:

        void push(MSG&& msg) {

            LOG_DBG(msg);

            std::lock_guard<std::mutex> lock(mutex_);

            queue_.push(std::move(msg));
            cond_.notify_one();
        }

        auto pop() -> MSG {

            LOG_DBG("pop message");
            std::unique_lock<std::mutex> lock(mutex_);
            cond_.wait(lock, [this] { return !queue_.empty(); });

            auto msg = queue_.front();
            queue_.pop();

            LOG_DBG("poped ", msg);

            return msg;
        }
    };
#endif


}  // namespace jj {
#endif // JJ_QUEUE_H_
