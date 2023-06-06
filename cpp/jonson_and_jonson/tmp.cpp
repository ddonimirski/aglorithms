#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_set>
#include <fstream>

// Actor class representing an email account
class EmailAccount {
public:
    explicit EmailAccount(const std::string& address) : address_(address) {}

    void SendMessage(const std::string& recipient, const std::string& message) {
        // Check if the message is suspicious
        if (IsSuspicious(message)) {
            ForwardToSecurityDepartment(message);
            BlockSender(recipient);
            return;
        }

        // Check if the message is spam
        if (IsSpam(message)) {
            return; // Discard the spam message
        }

        // Write normal mails to a log file
        WriteToLogFile(message);

        // Send the message to the recipient
        std::cout << "Message sent from " << address_ << " to " << recipient << ": " << message << std::endl;
    }

    void AddContact(const std::string& address) {
        address_book_.insert(address);
    }

private:
    std::string address_;
    std::unordered_set<std::string> address_book_;

    bool IsSuspicious(const std::string& message) {
        // Check if the message contains a malware pattern
        // Assume the pattern is XOR'ed with 0x42 or 0xE1
        // Perform the necessary checks and return true if suspicious, false otherwise
        return false;
    }

    void ForwardToSecurityDepartment(const std::string& message) {
        // Forward the suspicious email to the Security Department's email address
        std::string securityDepartmentEmail = "security@example.com";
        SendMessage(securityDepartmentEmail, message);
    }

    void BlockSender(const std::string& sender) {
        // Block the sender from sending further messages
        // Implement the necessary logic to block the sender
    }

    bool IsSpam(const std::string& message) {
        // Check if the message contains spam keywords
        std::vector<std::string> spamKeywords = { "discount", "inheritance", "lottery" };
        for (const std::string& keyword : spamKeywords) {
            if (message.find(keyword) != std::string::npos) {
                return true;
            }
        }
        return false;
    }

    void WriteToLogFile(const std::string& message) {
        // Write the normal message to a log file
        std::ofstream logFile("log.txt", std::ios::app);
        if (logFile.is_open()) {
            logFile << message << std::endl;
            logFile.close();
        }
    }
};

int main() {
    // Create email accounts
    std::shared_ptr<EmailAccount> account1 = std::make_shared<EmailAccount>("user1@example.com");
    std::shared_ptr<EmailAccount> account2 = std::make_shared<EmailAccount>("user2@example.com");
    std::shared_ptr<EmailAccount> securityDepartment = std::make_shared<EmailAccount>("security@example.com");

    // Add email addresses to address books
    account1->AddContact("user2@example.com");
    account1->AddContact("security@example.com");

    account2->AddContact("user1@example.com");
    account2->AddContact("security@example.com");

    securityDepartment->AddContact("user1@example.com");
    securityDepartment->AddContact("user2@example.com");

    // Send messages between accounts
    account1->SendMessage("user2@example.com", "Normal message");
    account1->SendMessage("user2@example.com", "Spam message with discount");
    account1->SendMessage("user2@example.com", "Suspicious message with malware pattern");

    return 0;
}

