// Exception.h
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

// Base GameException
class GameException : public std::exception {
protected:
    std::string message;
public:
    explicit GameException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

// Derived exceptions
class DeckEmptyException : public GameException {
public:
    DeckEmptyException() : GameException("Deck is empty! Cannot draw more cards.") {}
};

class InvalidCardException : public GameException {
public:
    InvalidCardException() : GameException("Invalid card index selected.") {}
};

class PlayerNotFoundException : public GameException {
public:
    PlayerNotFoundException() : GameException("Player not found.") {}
};

#endif // EXCEPTION_H
