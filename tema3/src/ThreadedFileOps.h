#ifndef THREADED_FILE_OPS_H
#define THREADED_FILE_OPS_H

#include <string>

// Synchronized file operations (WITH mutex) - CORRECT approach
void demonstrateSynchronizedFileOps(const std::string& filename);

// Unsynchronized file operations (WITHOUT mutex) - Shows race conditions
void demonstrateUnsynchronizedFileOps(const std::string& filename);

#endif // THREADED_FILE_OPS_H


