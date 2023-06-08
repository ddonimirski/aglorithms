#include <message.h>
#include <sstream>
#include <vector>
//#include <format>
#include <aho_corasick/aho_corasick.hpp>


namespace jj {

     auto to_str(Message const& msg) -> std::string {
        std::stringstream ss;
        ss << "{ address: " << msg.address_;
        if (msg.from_) {
            ss << ", from: " << *msg.from_;
        }
        ss << ", body: " << msg.body_ << " }";
        return ss.str();
    }

    auto is_spam(Message const& msg) -> bool {

        static auto trie_spam = []() {
            aho_corasick::trie trie;
            trie.insert("discount");
            trie.insert("inheritance");
            trie.insert("lottery");

            return trie;
        }();

        return !trie_spam.parse_text(msg.body_).empty();
    }

    auto operator << (std::ostream& os, Message const& msg) -> std::ostream& {
        return os << to_str(msg);
    }

} // namespace jj
