#ifndef FILE_DESCRIPTOR_H
#define FILE_DESCRIPTOR_H

#include <string>
#include <fstream>

// RAII wrapper for file operations
class FileDescriptor {
private:
    std::fstream file_;
    std::string filename_;
    bool isOpen_;

public:
    // Constructor - acquires resource
    FileDescriptor(const std::string& filename, std::ios::openmode mode);
    
    // Destructor - releases resource automatically
    ~FileDescriptor();
    
    // Delete copy constructor and copy assignment (non-copyable)
    FileDescriptor(const FileDescriptor&) = delete;
    FileDescriptor& operator=(const FileDescriptor&) = delete;
    
    // Move constructor and move assignment (movable)
    FileDescriptor(FileDescriptor&& other) noexcept;
    FileDescriptor& operator=(FileDescriptor&& other) noexcept;
    
    // Operations
    bool isOpen() const;
    void write(const std::string& data);
    std::string read();
    std::string readLine();
    void close();
};

#endif // FILE_DESCRIPTOR_H


