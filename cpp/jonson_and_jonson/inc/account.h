#ifndef JJ_ACCOUNT_H_
#define JJ_ACCOUNT_H_

#include <address.h>
#include <message.h>
#include <unordered_set>


namespace jj {

class Account final {

    Address const address_;
    std::unordered_set<Address> address_book_;

    public:

        Account(std::string const& address):address_(address) { }
        Account() = delete;
        Account(Account const&) = default;
        Account(Account &&) = default;
        Account& operator = (Account const&) = default;
        Account& operator = (Account &&) = default;
        ~Account() = default;


        void send(Message &&);
        void send(Message const& msg) { send(Message{msg}); }

        void receive(Message &&);
        void receive(Message const& msg) { receive(Message{msg}); }

        void forward(Message &&);
        void forward(Message const& msg) { forward(Message{msg}); }

        void add_contact(Address &&);
        void add_contact(Address const& addr) { add_contact(Address{addr}); }

};


} // namespace jj

#endif // JJ_ACCOUNT_H_
