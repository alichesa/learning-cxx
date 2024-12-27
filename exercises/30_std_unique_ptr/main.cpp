#include <memory>      // std::unique_ptr
#include <string>      // std::string
#include <vector>      // std::vector
#include <cstring>     // strcmp
#include <iostream>    // std::cout, std::cerr
#include <cstdlib>     // std::exit

#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion failed: " << (message) << std::endl; \
            std::exit(EXIT_FAILURE); \
        } \
    } while (false)

std::vector<std::string> RECORDS;  // 全局记录容器

class Resource {
public:
    void record(char record) {
        RECORDS.emplace_back(1, record);  // 每次记录一个字符
    }
};

using Unique = std::unique_ptr<Resource>;

Unique reset(Unique ptr) {
    if (!ptr) {
        std::cout << "reset: nullptr received, creating new resource" << std::endl;
        ptr = std::make_unique<Resource>();
        ptr->record('r');  // 记录资源创建
    } else {
        ptr->record('r');
        std::cout << "reset: recorded 'r'" << std::endl;
    }
    return ptr;
}

Unique drop(Unique ptr) {
    if (ptr) {
        ptr->record('d');
        std::cout << "drop: recorded 'd'" << std::endl;
    }
    return nullptr;
}

Unique forward(Unique ptr) {
    if (ptr) {
        ptr->record('f');
        std::cout << "forward: recorded 'f'" << std::endl;
    }
    return ptr;
}

int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    RECORDS.clear();
    drop(reset(nullptr));  // Test 1
    problems[0] = std::move(RECORDS);

    RECORDS.clear();
    forward(drop(reset(forward(forward(reset(nullptr))))));  // Test 2
    problems[1] = std::move(RECORDS);

    RECORDS.clear();
    drop(drop(reset(drop(reset(reset(nullptr))))));  // Test 3
    problems[2] = std::move(RECORDS);

    std::vector<const char *> answers[] {
        {"r", "d"},    // Test 1 结果
        {"r", "f", "d"},   // Test 2 结果
        {"r", "d", "r", "d", "r", "d"},   // Test 3 结果
    };

    for (auto i = 0; i < 3; ++i) {
        std::cout << "Test " << i + 1 << " RECORDS:" << std::endl;
        for (const auto &record : problems[i]) {
            std::cout << "  " << record << std::endl;
        }
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) {
            ASSERT(::strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
        }
    }

    return 0;
}
