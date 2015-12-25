#pragma once
#include <exception>

class StorageException : public std::exception
{
public:
    StorageException(const std::string& msg) : msg_{msg} {}

    const char* what() const noexcept override
    {
        return msg_.c_str();
    }
    
private:
    std::string msg_;
};
