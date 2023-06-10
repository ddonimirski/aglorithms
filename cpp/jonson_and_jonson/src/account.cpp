#include <account.h>
#include <vector>
#include <sec_email.h>
#include <message.h>
#include <utils.h>
#include <log.h>
#include <algorithm>

namespace jj 
{

    template<class ...Args>
    auto to_sec_body(std::string const& title, Message const& msg, Args&& ...args) -> std::string {
        std::stringstream ss;
        ss << title << to_str(msg);
        ((ss << args << ' '), ...);
        return ss.str();
    }


    Account::Account(AccountConf && conf): conf_{std::move(conf)} {
        for (auto const& pattern: conf_.malware_patterns_) { add_pattern(pattern); }
        for (auto const& pattern: conf_.spam_patterns_) { add_spam(pattern); }
    }


    [[nodiscard]] auto Account::create(AccountConf && conf) -> std::shared_ptr<Account> {
        return std::shared_ptr<Account>(new Account{std::move(conf)});
    }

    void Account::raw_send(std::string const& prefix, Message&& msg) const {

        LOG_DBG(prefix, msg);

        if (!conf_.sender_) {
            LOG_ERR("Account ", address()," doesn't have sender");
            throw std::runtime_error("sender not set");
        }

        conf_.sender_(std::move(msg));
    }

    void Account::send(Message && msg) {

        // Discard spam
        if (is_spam(msg)) {
            LOG_DBG("discard spam ", msg);
            return;
        }

        std::string const prefix = "[send]";

        if (is_blocked(msg.address_)) {
            LOG_SEC("blocked address");
            sec_forward(prefix, msg, "|blocked address");
            return;
        }

        if (is_suspicious(msg)) {
            LOG_SEC("suspicious message");
            sec_forward(prefix, msg, "|suspicious message");
            add_blocked(msg.address_);
            return;
        }

        msg.from_ = address();
        raw_send(prefix, std::move(msg));
    }

    void Account::receive(Message && msg) {

        LOG_DBG("receive ", msg);
        // Discard spam or no from address
        if (!msg.from_ || is_spam(msg)) {
            LOG_DBG((msg.from_?"discard spam":"no from address"), msg);
            return;
        }

        std::string const prefix = "[recv]";

        if (is_blocked(*msg.from_)) {
            LOG_SEC("blocked address");
            sec_forward(prefix, msg, "|blocked address");
            return;
        }

        if (is_suspicious(msg)) {
            LOG_SEC("suspicious message");
            sec_forward(prefix, msg, "|suspicious message");
            add_blocked(*msg.from_);
            return;
        }

        LOG_MSG(msg);

        // TODO implement reveive the message or remove ?
        //  send to archive ?
        (void)std::move(msg);
    }

    void Account::forward(Message && msg) const {
        raw_send("[frwd]", std::move(msg));
    }

    void Account::sec_forward(std::string const& prefix, Message const& msg, std::string const& reason) {
        forward(Message{
                .address_ = sec::address(),
                .from_ = address(),
                .body_ = to_sec_body(prefix, msg, reason)
                });
    }

    void Account::add_contact(Address && addr) {
        address_book_.insert(std::move(addr));
    }

    void Account::add_blocked(Address const& addr) {
        if (addr != sec::address()) {
            conf_.blocked_address_.insert(addr);
        }
        else {
            LOG_WAR("sec address can't be blocked");
        }
    }

    auto Account::is_blocked(Address const& addr) -> bool {
        auto account = conf_.blocked_address_.find(addr);
        return account != conf_.blocked_address_.end();
    }

    void Account::add_pattern(std::string const& pattern) {
        LOG_DBG("raw pattern ", pattern);
        for (auto value: { 0x41, 0xE2 }) {
            auto cypher_pattern = cypher_text(pattern, value);
            LOG_DBG("add pattern to trie (", value, ") ", cypher_pattern);
            trie_patterns_.insert(cypher_pattern);
        }
    }

    auto Account::is_suspicious(Message const& msg) -> bool {
        return !trie_patterns_.parse_text(msg.body_).empty();
    }

    void Account::add_spam(std::string const& pattern) {
        trie_spam_patterns_.insert(pattern);
    }

    auto Account::is_spam(Message const& msg) -> bool {
        return !trie_spam_patterns_.parse_text(msg.body_).empty();
    }

    // accessor for Manager
    void Account::receive_item_from_queue() {
        std::visit([this](auto&& item) {
                using T = std::decay_t<decltype(item)>;
                if constexpr (std::is_same_v<T, jj::Pattern>) {
                    LOG_DBG("received pattern ", item.pattern_);
                    add_pattern(item.pattern_);
                }
                else if constexpr (std::is_same_v<T, jj::Blocked>) {
                    LOG_DBG("recieved blocked address ", item.address_);
                    add_blocked(item.address_);
                }
                else {
                    LOG_DBG("recieved msg ", item);
                    receive(std::forward<Message>(item));
                }
         }, conf_.queue_->pop());
    }

} // namespace jj
