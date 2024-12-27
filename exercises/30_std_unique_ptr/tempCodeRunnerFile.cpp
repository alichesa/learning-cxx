#include "../exercise.h"
#include <memory>
#include <string>
#include <vector>
#include <cstring> // 用于 strcmp
#include <iostream> // 用于调试输出

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        if (!_records.empty()) {
            RECORDS.push_back(_records);
        }
    }
};

using Unique = std::unique_ptr<Resource>;

Unique reset(Unique ptr) {
    if (!ptr) {
        std::cout << "reset: nullptr received, creating new resource" << std::endl;
    } else {
        ptr->record('r');
        std::cout << "reset: recorded 'r'" << std::endl;
    }
    return std::make_unique<Resource>();
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
    drop(forward(reset(nullptr)));
    problems[0] = std::move(RECORDS);

    RECORDS.clear();
    forward(drop(reset(forward(forward(reset(nullptr))))));
    problems[1] = std::move(RECORDS);

    RECORDS.clear();
    drop(drop(reset(drop(reset(reset(nullptr))))));
    problems[2] = std::move(RECORDS);

    std::vector<const char *> answers[] {
        {"fd"},    // Test 1
        {"ffr"},   // Test 2
        {"rdd"},   // Test 3
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
