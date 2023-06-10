#ifndef JJ_MANAGER_ITEM_H_
#define JJ_MANAGER_ITEM_H_

#include <account.h>
#include <account_conf.h>
#include <queue.h>
#include <queue_item.h>
#include <thread>
#include <log.h>
#include <atomic>


namespace jj {

    class Item final : public std::enable_shared_from_this<Item>  {

        std::jthread receiver_;
        std::unique_ptr<Queue<QueueItem>> queue_ = std::make_unique<Queue<QueueItem>>();
        Account account_;

        Item(AccountConf&& conf);
        Item(Item&& item) = delete;
        Item(Item const&) = delete;

        public:

        ~Item();

        [[nodiscard]] static auto create(AccountConf&& conf) -> std::shared_ptr<Item>;

        auto getptr() -> std::shared_ptr<Item> { return shared_from_this(); }

        void push_to_queue(QueueItem&& item) { queue_->push(std::move(item)); }

        void receive_item_from_queue();

        void stop();
    };

} // namespace jj {


#endif // JJ_MANAGER_ITEM_H_
