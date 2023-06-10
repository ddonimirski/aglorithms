#ifndef JJ_ACCOUNT_H_
#define JJ_ACCOUNT_H_

#include <address.h>
#include <message.h>
#include <unordered_set>
#include <memory>
#include <functional>
#include <aho_corasick/aho_corasick.hpp>
#include <account_conf.h>


namespace jj {

    // class Account final : public std::enable_shared_from_this<Account>  {
    class Account final {

        // for withebox testing fixture
        friend class AccountTest;

        AccountConf conf_;
        std::unordered_set<Address> address_book_;
        aho_corasick::trie trie_patterns_;
        aho_corasick::trie trie_spam_patterns_;

        void forward(Message &&) const;

        void sec_forward(std::string const& prefix, Message const& msg, std::string const& reason);

        void raw_send(std::string const& prefix, Message&& msg) const;

        auto is_blocked(Address const& addr) -> bool;

        auto is_suspicious(Message const& msg) -> bool;

        auto is_spam(Message const& msg) -> bool;

        // protected:
        // // TODO consider use inheritance to avoid sync protection
        public:

        void add_spam(std::string const& pattern);

        void receive(Message &&);

        void add_blocked(Address const& addr);

        void add_pattern(std::string const& pattern);

        void set_sender(std::function<void(Message&&)> sender) {
            conf_.sender_ = sender;
        }

        public:

        Account() = delete;
        Account(AccountConf && conf);
        Account(Account const&) = delete;
        Account(Account &&) = delete;
        Account& operator = (Account const&) = delete;
        Account& operator = (Account &&) = delete;
        ~Account() = default;

        void send(Message &&);
        void send(Message const& msg) { send(Message{msg}); }
        void send(std::string const& addr, std::string const& body) {
            send(Message{ .address_ = Address{addr}, .body_ = body });
        }

        void add_contact(Address &&);
        void add_contact(Address const& addr) { add_contact(Address{addr}); }
        void add_contact(std::string const& addr) { add_contact(Address{addr}); }

        auto address() const -> Address const& { return conf_.address_; }
    };

} // namespace jj

#endif // JJ_ACCOUNT_H_
