#include <manager.h>
#include <cstdio>
#include <queue_item.h>
#include <vector>
#include <iostream>
#include <type_traits>

using namespace jj;

using var_t = std::variant<int, long, std::string>;

template<class ...Ts>
struct overloaded: Ts... { using Ts::operator()...; };

template<class ...Ts>
overloaded(Ts ...) -> overloaded<Ts...>;

int main() {



    std::vector<QueueItem> vec = {
        Pattern{ .pattern_ = "pattern ad;ksljfasd" },
        Blocked{ .address_ = Address("json@t.com") },
        Message{ .address_ = Address("json@t.com"), .body_ = "body message for json" },
    };

    for (auto v: vec) {

        std::visit([](auto&& w) {
                    using T = std::decay_t<decltype(w)>;
                    if constexpr (std::is_same_v<T, jj::Pattern>) {
                        std::cerr << "pattern: " << w.pattern_ << std::endl;
                    }
                    else if constexpr (std::is_same_v<T, jj::Blocked>) {
                        std::cerr << "blocked: " << w.address_ << std::endl;
                    }
                    else {
                        std::cerr << "message: " << w << std::endl;
                    }
                }, v);
    }


    auto const addr1 = Address{"john@example.com"};
    auto const addr2 = Address{"david@example.com"};
    auto const addr3 = Address{"daniel@example.com"};

    create_account(AccountConf{ .address_ = addr1});


    send_to(Message{
            .address_ = addr1,
            .from_ = addr2,
            .body_ = "Hellow world!"
            });

    send_to(Message{
            .address_ = addr1,
            .from_ = addr2,
            .body_ = "Hellow world lottery!"
            });

    send_to(Message{
            .address_ = addr3,
            .body_ = "new message"
            });

    (void)getchar();
}
