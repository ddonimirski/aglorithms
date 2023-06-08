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

    class Account final : public std::enable_shared_from_this<Account>  {

        AccountConf conf_;
        std::unordered_set<Address> address_book_;
        aho_corasick::trie trie_patterns_;
        aho_corasick::trie trie_spam_patterns_;

        Account(AccountConf && conf);
        Account() = delete;

        void forward(Message &&) const;

        void sec_forward(std::string const& prefix, Message const& msg, std::string const& reason);

        void raw_send(std::string const& prefix, Message&& msg) const;

        auto is_blocked(Address const& addr) -> bool;

        auto is_suspicious(Message const& msg) -> bool;

        auto is_spam(Message const& msg) -> bool;

        void add_spam(std::string const& pattern);

        public:

        Account(Account const&) = default;
        Account(Account &&) = default;
        Account& operator = (Account const&) = default;
        Account& operator = (Account &&) = default;
        ~Account() = default;

        [[nodiscard]] static auto create(AccountConf && conf) -> std::shared_ptr<Account> ;

        auto getptr() -> std::shared_ptr<Account> { return shared_from_this(); }

        void send(Message &&);
        void send(Message const& msg) { send(Message{msg}); }
        void send(std::string const& addr, std::string const& msg);

        void receive(Message &&);

        void add_contact(Address &&);
        void add_contact(Address const& addr) { add_contact(Address{addr}); }
        void add_contact(std::string const& addr) { add_contact(Address{addr}); }

        void add_blocked(Address const& addr);
        void add_blocked(Blocked const& addr);

        void add_pattern(std::string const& pattern);
        void add_pattern(Pattern const& pattern);
    };


} // namespace jj

#endif // JJ_ACCOUNT_H_
