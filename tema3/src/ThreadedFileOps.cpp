#include "ThreadedFileOps.h"
#include "Lock.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <mutex>

// ============================================================================
// SYNCHRONIZED FILE OPERATIONS (WITH MUTEX) - CORRECT
// ============================================================================

std::mutex fileMutex; // Global mutex for file synchronization

void writerThreadSync(const std::string& filename, std::mutex& mtx) {
    std::cout << "  [Writer Thread] Starting...\n";
    
    for (int i = 1; i <= 5; ++i) {
        // Use RAII Lock to automatically manage mutex
        Lock lock(mtx);
        
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            std::string line = "Writer: Line " + std::to_string(i) + "\n";
            file << line;
            std::cout << "  [Writer Thread] Wrote: " << line;
            file.close();
        }
        
        // Lock is automatically released here when lock goes out of scope
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    std::cout << "  [Writer Thread] Finished\n";
}

void readerThreadSync(const std::string& filename, std::mutex& mtx) {
    std::cout << "  [Reader Thread] Starting...\n";
    
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Small delay
    
    for (int i = 0; i < 5; ++i) {
        // Use RAII Lock to automatically manage mutex
        Lock lock(mtx);
        
        std::ifstream file(filename);
        if (file.is_open()) {
            std::cout << "  [Reader Thread] Reading file content:\n";
            std::string line;
            while (std::getline(file, line)) {
                std::cout << "    -> " << line << "\n";
            }
            file.close();
        }
        
        // Lock is automatically released here when lock goes out of scope
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    
    std::cout << "  [Reader Thread] Finished\n";
}

void demonstrateSynchronizedFileOps(const std::string& filename) {
    std::cout << "\n=== SYNCHRONIZED FILE OPERATIONS (WITH MUTEX) ===\n";
    std::cout << "Writer thread will write lines, reader thread will read them.\n";
    std::cout << "Mutex ensures proper synchronization - NO race conditions!\n\n";
    
    // Clear file first
    {
        std::ofstream file(filename, std::ios::trunc);
    }
    
    std::mutex localMutex;
    
    // Create threads
    std::thread writer(writerThreadSync, filename, std::ref(localMutex));
    std::thread reader(readerThreadSync, filename, std::ref(localMutex));
    
    // Wait for threads to complete
    writer.join();
    reader.join();
    
    std::cout << "\n✓ Synchronized operations completed successfully!\n";
}

// ============================================================================
// UNSYNCHRONIZED FILE OPERATIONS (WITHOUT MUTEX) - DEMONSTRATES PROBLEMS
// ============================================================================

void writerThreadUnsync(const std::string& filename) {
    std::cout << "  [Writer Thread] Starting (NO MUTEX)...\n";
    
    for (int i = 1; i <= 5; ++i) {
        // NO LOCK - Direct file access (DANGEROUS!)
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            std::string line = "Unsync Writer: Line " + std::to_string(i) + "\n";
            file << line;
            std::cout << "  [Writer Thread] Wrote: " << line;
            file.close();
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    std::cout << "  [Writer Thread] Finished\n";
}

void readerThreadUnsync(const std::string& filename) {
    std::cout << "  [Reader Thread] Starting (NO MUTEX)...\n";
    
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    for (int i = 0; i < 5; ++i) {
        // NO LOCK - Direct file access (DANGEROUS!)
        std::ifstream file(filename);
        if (file.is_open()) {
            std::cout << "  [Reader Thread] Reading file content:\n";
            std::string line;
            while (std::getline(file, line)) {
                std::cout << "    -> " << line << "\n";
            }
            file.close();
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    
    std::cout << "  [Reader Thread] Finished\n";
}

void demonstrateUnsynchronizedFileOps(const std::string& filename) {
    std::cout << "\n=== UNSYNCHRONIZED FILE OPERATIONS (WITHOUT MUTEX) ===\n";
    std::cout << "Writer thread will write lines, reader thread will read them.\n";
    std::cout << "⚠ WARNING: NO MUTEX - potential race conditions and inconsistent reads!\n\n";
    
    // Clear file first
    {
        std::ofstream file(filename, std::ios::trunc);
    }
    
    // Create threads WITHOUT mutex protection
    std::thread writer(writerThreadUnsync, filename);
    std::thread reader(readerThreadUnsync, filename);
    
    // Wait for threads to complete
    writer.join();
    reader.join();
    
    std::cout << "\n⚠ Unsynchronized operations completed - may have race conditions!\n";
    std::cout << "Note: File access might be inconsistent or corrupted.\n";
}


