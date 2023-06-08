#include <gtest/gtest.h>
#include <sec_email.h>
#include <message.h>
#include <utils.h>
#include <sstream>

using namespace jj;

namespace tt {
    auto to_msg(Message const& msg) -> std::string {
        std::stringstream ss;
        ss << "{ address: " << msg.address_ << ", body: " << msg.body_ << " }";
        return ss.str();
    }
} // namespace tt

TEST(test_Message, to_str)
{
    Message const msgs[] = {
        { .address_ = sec::address(), .body_ = "message for secuirity"},
        { .address_ = "john.nash@example.com", .body_ = "message for john" }
    };

    std::string const expected[] {
        tt::to_msg({ .address_ = sec::address(), .body_ = "message for secuirity"}),
        tt::to_msg({ .address_ = "john.nash@example.com", .body_ = "message for john" })
    };

    for (int i = 0; i < size(msgs); ++i) {
        ASSERT_EQ(to_str(msgs[i]), expected[i]);
    }
}
