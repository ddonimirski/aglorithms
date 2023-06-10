#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <account.h>
#include <iostream>

namespace jj
{

    struct MockSender
    {
        // MOCK_METHOD(void, send_to,(Message const&));
        void send_to(Message && msg) {
            ++count_send_to_ ;
            ASSERT_EQ(msg, expected_msg_);
            (void)std::move(msg);
        }
        
        Message expected_msg_ = Message{
            .address_ = Address{"fake@address.com"},
            .from_ = Address{"fake.from@address.com"},
            .body_ = "fake body message"
        };

        int count_send_to_ = 0;
    };


    class AccountTest: public ::testing::Test
    {
        public:

            void prv_conf_AfterSetup() {

            }

        protected:

           void SetUp() {
               account_ = std::make_unique<Account>( AccountConf {
                       .address_ = Address("json@hp.com"),
                       .sender_ = [this](Message&& msg) {
                            mock_.send_to(std::move(msg));
                            } });
           }

           void TearDown() {}


           std::unique_ptr<Account> account_;
           MockSender mock_;

    };
}  // namespace jj {
   // to keep nameing convetion
using test_Account = jj::AccountTest;

