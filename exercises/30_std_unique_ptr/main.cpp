#include "../exercise.h"
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr>

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        RECORDS.push_back(_records);
    }
};

using Unique = std::unique_ptr<Resource>;
Unique reset(Unique ptr) {
    if (ptr) ptr->record('r');
    return std::make_unique<Resource>();
}
Unique drop(Unique ptr) {
    if (ptr) ptr->record('d');
    return nullptr;
}
Unique forward(Unique ptr) {
    if (ptr) ptr->record('f');
    return ptr;
}

int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    drop(forward(reset(nullptr)));
    problems[0] = std::move(RECORDS);
    
    // Output problems[0] for debugging
    std::cout << "problems[0]:\n";
    for (const auto &record : problems[0]) {
        std::cout << record << std::endl;
    }

    forward(drop(reset(forward(forward(reset(nullptr))))));
    problems[1] = std::move(RECORDS);
    
    // Output problems[1] for debugging
    std::cout << "problems[1]:\n";
    for (const auto &record : problems[1]) {
        std::cout << record << std::endl;
    }

    drop(drop(reset(drop(reset(reset(nullptr))))));
    problems[2] = std::move(RECORDS);
    
    // Output problems[2] for debugging
    std::cout << "problems[2]:\n";
    for (const auto &record : problems[2]) {
        std::cout << record << std::endl;
    }

    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[]{
        {"fd"},
        {"ffr", "d"},
        {"r", "d", "d"},
    };

    // ---- 不要修改以下代码 ----

    for (auto i = 0; i < 3; ++i) {
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) {
            ASSERT(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
        }
    }

    return 0;
}
