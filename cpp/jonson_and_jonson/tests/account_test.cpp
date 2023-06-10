#include "account_test.h"

using namespace jj;

TEST_F(test_Account, create)
{
    auto msg = Message{
                    .address_ = Address{"json@ext.com"},
                    .body_ = "simple body"
                };

    msg.from_ = account_->address();
    mock_.expected_msg_ = msg;
    account_->send(msg);

    //EXPECT_CALL(mock_, send_to(msg));
    ASSERT_EQ(mock_.count_send_to_, 1);
}
