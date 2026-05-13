#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class RacingException : public std::exception {
protected:
    std::string message;
public:
    explicit RacingException(const std::string& msg) : message("Racing Error: " + msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class InvalidAttributeException : public RacingException {
public:
    explicit InvalidAttributeException(const std::string& attr) 
        : RacingException("Invalid value for: " + attr) {}
};

class InsufficientFundsException : public RacingException {
public:
    explicit InsufficientFundsException(int req) 
        : RacingException("Insuffiecient funds. Minimum: " + std::to_string(req)) {}
};

class CarNotReadyException : public RacingException {
public:
    explicit CarNotReadyException() : RacingException("Car not configured properly!") {}
};

#endif