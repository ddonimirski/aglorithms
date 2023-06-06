#include <account.h>
#include <vector>
#include <sec_patterns.h>


namespace jj 
{
    void Account::send(Message && msg) {

        if (sec::is_suspicious(msg)) {
            forward(Message{
                    .address_ = sec::address(),
                    .body_ = to_str(msg)});
        }

    }


    void Account::receive(Message && msg) {

    }

    void Account::forward(Message && msg) {

    }

    void Account::add_contact(Address && addr) {
        address_book_.insert(std::move(addr));
    }


} // namespace jj
