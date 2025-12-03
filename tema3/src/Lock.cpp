#include "Lock.h"
#include <iostream>

// Non-copyable Lock implementation
Lock::Lock(std::mutex& m) : mutex_(m) {
    mutex_.lock();
    // Uncomment for debugging:
    // std::cout << "  [Lock: Mutex locked]\n";
}

Lock::~Lock() {
    mutex_.unlock();
    // Uncomment for debugging:
    // std::cout << "  [Lock: Mutex unlocked]\n";
}

// Reference-counted SharedLock implementation
SharedLock::SharedLock(std::shared_ptr<std::mutex> m) : mutexPtr_(m) {
    if (mutexPtr_) {
        mutexPtr_->lock();
        std::cout << "  [SharedLock: Mutex locked, ref count = " 
                  << mutexPtr_.use_count() << "]\n";
    }
}

SharedLock::~SharedLock() {
    if (mutexPtr_) {
        mutexPtr_->unlock();
        std::cout << "  [SharedLock: Mutex unlocked, ref count = " 
                  << mutexPtr_.use_count() << "]\n";
    }
}

// Copy constructor
SharedLock::SharedLock(const SharedLock& other) : mutexPtr_(other.mutexPtr_) {
    std::cout << "  [SharedLock: Copied, ref count = " 
              << mutexPtr_.use_count() << "]\n";
}

// Copy assignment
SharedLock& SharedLock::operator=(const SharedLock& other) {
    if (this != &other) {
        mutexPtr_ = other.mutexPtr_;
        std::cout << "  [SharedLock: Assigned, ref count = " 
                  << mutexPtr_.use_count() << "]\n";
    }
    return *this;
}


