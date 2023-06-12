#include <manager_item.h>

namespace jj {

    Item::Item(AccountConf&& conf): account_{std::move(conf)} {

        LOG_DBG("create item for ", account_.address());

        LOG_DBG("set sender", account_.address());
        auto sender = [this](Message&& msg) -> void { push_to_queue(std::move(msg)); };
        account_.set_sender(sender);

        LOG_DBG("create receiver_ for ", account_.address());
        receiver_ = std::jthread{[this](std::stop_token stoken) {
            while(!stoken.stop_requested()) {
                receive_item_from_queue();
            }
        }};
    }

    [[nodiscard]] auto Item::create(AccountConf&& conf) -> std::shared_ptr<Item> {
        std::shared_ptr<Item> ret(new Item{std::move(conf)});
        return ret;
    }

    Item::~Item() {
        LOG_DBG(account_.address());
        if (!queue_.stopped()) {
            stop();
        }
        receiver_.join();
    }

    void Item::receive_item_from_queue() {

        if (auto msg = queue_.pop(); msg) {
            std::visit([this]([[maybe_unused]]auto&& msg) {
                    using T = std::decay_t<decltype(msg)>;
                    if constexpr (std::is_same_v<T, jj::Pattern>) {
                        account_.add_pattern(msg.pattern_);
                    }
                    else if constexpr (std::is_same_v<T, jj::Blocked>) {
                        account_.add_blocked(msg.address_);
                    }
                    else {
                        account_.receive(std::forward<Message>(msg));
                    }
                }, std::move(*msg));
        }
    }

    void Item::stop() {
        receiver_.request_stop();
        queue_.stop();
    }

} // namespace jj {
