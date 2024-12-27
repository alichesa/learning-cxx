#include "../exercise.h"
#include <memory>
#include <iostream>

int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10); 
    std::shared_ptr<int> ptrs[]{shared, shared, shared}; // shared_ptr 数组，初始引用计数为 4

    std::weak_ptr<int> observer = shared; 
    ASSERT(observer.use_count() == 4, "Initial use count should be 4 (3 in array + shared)");

    // 第一次操作：重置 ptrs[0]
    ptrs[0].reset(); 
    ASSERT(observer.use_count() == 3, "After resetting ptrs[0], use count should be 3");

    // 第二次操作：将 ptrs[1] 设置为 nullptr
    ptrs[1] = nullptr; 
    ASSERT(observer.use_count() == 2, "After setting ptrs[1] to nullptr, use count should be 2");

    // 第三次操作：为 ptrs[2] 分配一个新的 shared_ptr
    ptrs[2] = std::make_shared<int>(*shared); 
    ASSERT(observer.use_count() == 1, "After reassigning ptrs[2], use count should be 1");

    // 恢复所有权
    ptrs[0] = shared; 
    ptrs[1] = shared; 
    ptrs[2] = std::move(shared); 
    ASSERT(observer.use_count() == 3, "After reassigning all ptrs to shared, use count should be 3");

    // 重置所有 shared_ptr
    ptrs[0].reset(); 
    ptrs[1].reset();
    ptrs[2].reset(); 
    ASSERT(observer.use_count() == 0, "After resetting all ptrs, use count should be 0");

    // 尝试从 weak_ptr 锁定 shared_ptr
    shared = observer.lock(); 
    if (shared == nullptr) {
        ASSERT(observer.use_count() == 0, "Observer.lock() returned nullptr, use count should be 0");
    } else {
        ASSERT(observer.use_count() == 1, "Observer.lock() succeeded, use count should be 1");
    }

    // 释放所有权
    shared = nullptr; 
    for (auto &ptr : ptrs) ptr = nullptr; 
    ASSERT(observer.use_count() == 0, "After releasing all shared_ptrs, use count should be 0");

    // 再次尝试锁定过期的 weak_ptr
    shared = observer.lock(); 
    ASSERT(shared == nullptr, "shared should be nullptr after locking expired weak_ptr");
    ASSERT(observer.use_count() == 0, "After locking expired weak_ptr, use count should still be 0");

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
