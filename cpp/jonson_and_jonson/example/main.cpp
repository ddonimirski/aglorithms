#include <manager.h>
#include <utils.h>

using namespace jj;

int main() {

    Manager manager;

    auto const addr1 = Address("john@examp.com");
    auto const addr2 = Address("david@examp.com");
    auto const addr3 = Address("daniel@examp.com");

    manager.create_account(AccountConf{ .address_ = addr1 });

    manager.send_to(Message{
            .address_ = addr1,
            .from_ = addr2,
            .body_ = "Hellow world!"
            });

    manager.send_to(Message{
            .address_ = addr1,
            .from_ = addr2,
            .body_ = "Hellow world lottery!"
            });

    manager.send_to(Message{
            .address_ = addr3,
            .body_ = "new message"
            });

    std::string malware = "ssdkjj;jzsdf;";

    manager.notify_pattern(malware);

    manager.send_to(Message{
            .address_ = addr1,
            .from_ = addr2,
            .body_ = cypher_text(malware, 0x41)
            });

    (void)getchar();
}
