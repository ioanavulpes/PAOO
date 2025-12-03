#include "FileDescriptor.h"
#include <iostream>
#include <sstream>

FileDescriptor::FileDescriptor(const std::string& filename, std::ios::openmode mode)
    : filename_(filename), isOpen_(false) {
    file_.open(filename, mode);
    if (file_.is_open()) {
        isOpen_ = true;
        std::cout << "  [FileDescriptor: Opened file '" << filename_ << "']\n";
    } else {
        std::cerr << "  [FileDescriptor: Failed to open file '" << filename_ << "']\n";
    }
}

FileDescriptor::~FileDescriptor() {
    if (isOpen_ && file_.is_open()) {
        file_.close();
        std::cout << "  [FileDescriptor: Automatically closed file '" << filename_ << "']\n";
    }
}

// Move constructor
FileDescriptor::FileDescriptor(FileDescriptor&& other) noexcept
    : file_(std::move(other.file_)), 
      filename_(std::move(other.filename_)),
      isOpen_(other.isOpen_) {
    other.isOpen_ = false;
}

// Move assignment
FileDescriptor& FileDescriptor::operator=(FileDescriptor&& other) noexcept {
    if (this != &other) {
        if (isOpen_ && file_.is_open()) {
            file_.close();
        }
        file_ = std::move(other.file_);
        filename_ = std::move(other.filename_);
        isOpen_ = other.isOpen_;
        other.isOpen_ = false;
    }
    return *this;
}

bool FileDescriptor::isOpen() const {
    return isOpen_ && file_.is_open();
}

void FileDescriptor::write(const std::string& data) {
    if (isOpen()) {
        file_ << data;
        file_.flush();
    }
}

std::string FileDescriptor::read() {
    if (!isOpen()) {
        return "";
    }
    
    std::stringstream buffer;
    buffer << file_.rdbuf();
    return buffer.str();
}

std::string FileDescriptor::readLine() {
    if (!isOpen()) {
        return "";
    }
    
    std::string line;
    std::getline(file_, line);
    return line;
}

void FileDescriptor::close() {
    if (isOpen_ && file_.is_open()) {
        file_.close();
        isOpen_ = false;
        std::cout << "  [FileDescriptor: Manually closed file '" << filename_ << "']\n";
    }
}


