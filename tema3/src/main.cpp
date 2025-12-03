#include <iostream>
#include <memory>
#include <vector>
#include "Investment.h"
#include "FileDescriptor.h"
#include "Lock.h"
#include "ThreadedFileOps.h"

void printSeparator(const std::string& title) {
    std::cout << "\n";
    std::cout << "================================================================\n";
    std::cout << title << "\n";
    std::cout << "================================================================\n";
}

void printSubSection(const std::string& title) {
    std::cout << "\n--- " << title << " ---\n";
}

// ============================================================================
// SECTION 1: unique_ptr Examples (Exclusive Ownership)
// ============================================================================
void demonstrateUniquePtr() {
    printSeparator("SECTION 1: unique_ptr - EXCLUSIVE OWNERSHIP");
    
    printSubSection("1.1: Basic unique_ptr usage");
    {
        std::cout << "Creating investment with unique_ptr:\n";
        std::unique_ptr<Investment> investment = createInvestmentSmart(0);
        investment->printInfo();
        std::cout << "\n✓ Investment will be automatically deleted when out of scope\n";
    } // investment destroyed here automatically
    
    printSubSection("1.2: unique_ptr - Transfer of Ownership (Move Semantics)");
    {
        std::cout << "Creating first unique_ptr:\n";
        std::unique_ptr<Investment> inv1 = createInvestmentSmart(1);
        
        std::cout << "\nTransferring ownership to inv2 using std::move:\n";
        std::unique_ptr<Investment> inv2 = std::move(inv1);
        
        std::cout << "\nAfter move:\n";
        std::cout << "  inv1 is " << (inv1 ? "valid" : "null (ownership transferred)") << "\n";
        std::cout << "  inv2 is " << (inv2 ? "valid (now owns the resource)" : "null") << "\n";
        
        if (inv2) {
            std::cout << "\ninv2's investment:\n";
            inv2->printInfo();
        }
    } // inv2 destroyed here
    
    printSubSection("1.3: unique_ptr in Vector");
    {
        std::cout << "Creating a portfolio with vector of unique_ptr:\n";
        std::vector<std::unique_ptr<Investment>> portfolio;
        
        portfolio.push_back(createInvestmentSmart(0));
        portfolio.push_back(createInvestmentSmart(1));
        
        std::cout << "\nPortfolio contents:\n";
        for (const auto& investment : portfolio) {
            investment->printInfo();
            std::cout << "\n";
        }
        
        std::cout << "✓ All investments will be automatically deleted when vector goes out of scope\n";
    } // All investments destroyed here
}

// ============================================================================
// SECTION 2: shared_ptr Examples (Reference Counting)
// ============================================================================
void demonstrateSharedPtr() {
    printSeparator("SECTION 2: shared_ptr - REFERENCE COUNTING");
    
    printSubSection("2.1: Basic shared_ptr usage");
    {
        std::cout << "Creating investment with shared_ptr:\n";
        std::shared_ptr<Investment> investment = createInvestmentShared(0);
        std::cout << "Reference count: " << investment.use_count() << "\n";
        investment->printInfo();
    }
    
    printSubSection("2.2: shared_ptr - Shared Ownership");
    {
        std::cout << "Creating first shared_ptr (sp1):\n";
        std::shared_ptr<Investment> sp1 = createInvestmentShared(1);
        std::cout << "Reference count after sp1: " << sp1.use_count() << "\n";
        
        {
            std::cout << "\nCreating second shared_ptr (sp2) pointing to same object:\n";
            std::shared_ptr<Investment> sp2 = sp1; // Copy, not move!
            std::cout << "Reference count after sp2: " << sp1.use_count() << "\n";
            
            {
                std::cout << "\nCreating third shared_ptr (sp3):\n";
                std::shared_ptr<Investment> sp3 = sp2;
                std::cout << "Reference count after sp3: " << sp1.use_count() << "\n";
                
                std::cout << "\nAll three pointers point to the same object:\n";
                sp3->printInfo();
                
                std::cout << "\nsp3 going out of scope...\n";
            }
            std::cout << "Reference count after sp3 destroyed: " << sp1.use_count() << "\n";
            
            std::cout << "\nsp2 going out of scope...\n";
        }
        std::cout << "Reference count after sp2 destroyed: " << sp1.use_count() << "\n";
        
        std::cout << "\nsp1 going out of scope - object will be deleted now...\n";
    }
    
    printSubSection("2.3: shared_ptr in Vector (Multiple Owners)");
    {
        std::cout << "Creating shared investment:\n";
        std::shared_ptr<Investment> sharedInvestment = createInvestmentShared(0);
        std::cout << "Initial reference count: " << sharedInvestment.use_count() << "\n";
        
        std::cout << "\nAdding to multiple portfolios:\n";
        std::vector<std::shared_ptr<Investment>> portfolio1;
        std::vector<std::shared_ptr<Investment>> portfolio2;
        
        portfolio1.push_back(sharedInvestment);
        std::cout << "After adding to portfolio1: " << sharedInvestment.use_count() << "\n";
        
        portfolio2.push_back(sharedInvestment);
        std::cout << "After adding to portfolio2: " << sharedInvestment.use_count() << "\n";
        
        std::cout << "\n✓ Same investment object shared between multiple portfolios!\n";
        std::cout << "It will only be deleted when ALL references are gone.\n";
    }
}

// ============================================================================
// SECTION 3: File Descriptor RAII
// ============================================================================
void demonstrateFileDescriptor() {
    printSeparator("SECTION 3: FileDescriptor RAII - AUTOMATIC RESOURCE CLEANUP");
    
    printSubSection("3.1: Automatic File Closure");
    {
        std::cout << "Opening file with FileDescriptor:\n";
        FileDescriptor fd("test_raii.txt", std::ios::out);
        
        std::cout << "\nWriting to file:\n";
        fd.write("Line 1: RAII ensures files are closed automatically!\n");
        fd.write("Line 2: No manual cleanup needed.\n");
        fd.write("Line 3: Destructor handles it.\n");
        
        std::cout << "\nFile is still open: " << (fd.isOpen() ? "Yes" : "No") << "\n";
        std::cout << "\nLeaving scope - file will close automatically...\n";
    } // File automatically closed here by destructor!
    
    printSubSection("3.2: Reading with FileDescriptor");
    {
        std::cout << "Opening file for reading:\n";
        FileDescriptor fd("test_raii.txt", std::ios::in);
        
        std::cout << "\nReading file content:\n";
        std::string line;
        while (!(line = fd.readLine()).empty()) {
            std::cout << "  " << line << "\n";
        }
    } // File automatically closed
    
    printSubSection("3.3: Move Semantics (FileDescriptor is movable)");
    {
        std::cout << "Creating FileDescriptor fd1:\n";
        FileDescriptor fd1("test_move.txt", std::ios::out);
        fd1.write("Original file descriptor\n");
        
        std::cout << "\nMoving fd1 to fd2:\n";
        FileDescriptor fd2 = std::move(fd1);
        
        std::cout << "fd1 is now: " << (fd1.isOpen() ? "still open" : "invalid (moved)") << "\n";
        std::cout << "fd2 is now: " << (fd2.isOpen() ? "valid (owns resource)" : "invalid") << "\n";
        
        fd2.write("Writing through moved descriptor\n");
    }
}

// ============================================================================
// SECTION 4 & 5: Threaded File Operations
// ============================================================================
void demonstrateThreadedOperations() {
    // WITH MUTEX - Correct synchronization
    demonstrateSynchronizedFileOps("test_sync.txt");
    
    std::cout << "\n\nPress Enter to continue to unsynchronized example...";
    std::cin.get();
    
    // WITHOUT MUTEX - Shows problems
    demonstrateUnsynchronizedFileOps("test_unsync.txt");
}

// ============================================================================
// MAIN
// ============================================================================
int main() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║         C++ RESOURCE MANAGEMENT DEMONSTRATION                  ║\n";
    std::cout << "║         RAII, Smart Pointers, and Thread Synchronization       ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════╝\n";
    
    try {
        // Section 1: unique_ptr
        demonstrateUniquePtr();
        
        // Section 2: shared_ptr
        demonstrateSharedPtr();
        
        // Section 3: FileDescriptor RAII
        demonstrateFileDescriptor();
        
        // Section 4 & 5: Threaded operations
        demonstrateThreadedOperations();
        
        printSeparator("ALL DEMONSTRATIONS COMPLETED SUCCESSFULLY!");
        std::cout << "\nKey Takeaways:\n";
        std::cout << "  1. unique_ptr: Exclusive ownership, move-only, zero overhead\n";
        std::cout << "  2. shared_ptr: Shared ownership, reference counting\n";
        std::cout << "  3. RAII: Resources acquired in constructor, released in destructor\n";
        std::cout << "  4. Mutex with RAII Lock: Automatic synchronization, exception-safe\n";
        std::cout << "  5. Without synchronization: Race conditions and data corruption\n";
        std::cout << "\n✓ Always use RAII for resource management!\n";
        
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}


