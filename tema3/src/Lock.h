#ifndef LOCK_H
#define LOCK_H

#include <mutex>
#include <memory>

// RAII Lock class - Non-copyable version
// Automatically locks mutex on construction, unlocks on destruction
class Lock {
private:
    std::mutex& mutex_;

public:
    // Constructor - acquires lock
    explicit Lock(std::mutex& m);
    
    // Destructor - releases lock
    ~Lock();
    
    // Delete copy operations (non-copyable)
    Lock(const Lock&) = delete;
    Lock& operator=(const Lock&) = delete;
};

// RAII Lock class - Reference-counted version using shared_ptr
// Multiple Lock objects can share the same mutex
class SharedLock {
private:
    std::shared_ptr<std::mutex> mutexPtr_;
    
public:
    // Constructor - acquires lock
    explicit SharedLock(std::shared_ptr<std::mutex> m);
    
    // Destructor - releases lock when reference count reaches zero
    ~SharedLock();
    
    // Copy operations allowed (reference counting)
    SharedLock(const SharedLock& other);
    SharedLock& operator=(const SharedLock& other);
};

#endif // LOCK_H


