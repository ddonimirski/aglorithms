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


    void Account::sec_forward(std::string const& prefix, Message const& msg, std::string const& reason) {
        forward(Message{
                .address_ = sec::address(),
                .from_ = conf_.address_,
                .body_ = to_sec_body(prefix, msg, reason)
                });
    }

    void Account::raw_send(std::string const& prefix, Message&& msg) const {
        // TODO ? msg.from_ = conf_.address_;
        LOG_DBG(prefix, msg);
        if (conf_.send_) {
            conf_.send_(std::move(msg));
        }
    }

    void Account::send(Message && msg) {

        // Discard spam
        if (is_spam(msg)) {
            return;
        }

        std::string const prefix = "[send]";

        if (is_blocked(msg.address_)) {
            sec_forward(prefix, msg, "|blocked address");
            return;
        }

        if (is_suspicious(msg)) {
            sec_forward(prefix, msg, "|suspicious message");
            add_blocked(msg.address_);
            return;
        }

        msg.from_ = conf_.address_;
        raw_send(prefix, std::move(msg));
    }

    void Account::receive(Message && msg) {

        LOG_DBG("start ", msg);
        // Discard spam or no from address
        if (!msg.from_ || is_spam(msg)) {
            LOG_DBG("discard spam", msg);
            return;
        }

        std::string const prefix = "[recv]";

        if (is_blocked(*msg.from_)) {
            LOG_DBG("blocked ", msg);
            sec_forward(prefix, msg, "|blocked address");
            return;
        }

        if (is_suspicious(msg)) {
            LOG_DBG("suspicious ", msg);
            sec_forward(prefix, msg, "|suspicious message");
            add_blocked(*msg.from_);
            return;
        }

        LOG_MSG(msg);

        // TODO implement reveive the message or remove
        (void)std::move(msg);
    }

    void Account::forward(Message && msg) const {
        raw_send("[frwd]", std::move(msg));
    }

    void Account::add_contact(Address && addr) {
        address_book_.insert(std::move(addr));
    }

    void Account::add_blocked(Address const& addr) {
        if (addr != sec::address()) {
            conf_.blocked_address_.insert(addr);
        }
    }

    auto Account::is_blocked(Address const& addr) -> bool {
        auto account = conf_.blocked_address_.find(addr);
        return account != conf_.blocked_address_.end();
    }

    void Account::add_pattern(std::string const& pattern) {
        for (auto value: { 0x41, 0xE2 }) {
            auto cypher_pattern = cypher_text(pattern, value);
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


} // namespace jj
