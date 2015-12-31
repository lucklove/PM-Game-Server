#pragma once
#include <exception>

class LuaException : public std::exception
{
public:
    LuaException(const std::string& msg) : msg_{msg} {}

    const char* what() const noexcept override
    {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

struct StorageException : LuaException
{
    using LuaException::LuaException;
};

struct UnknownLuaException : LuaException
{
    using LuaException::LuaException;
};
