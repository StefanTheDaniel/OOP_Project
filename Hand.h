// Hand.h
#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include "Exception.h"
#include <vector>
#include <memory>
#include <iostream>

class Hand {
    std::vector<std::unique_ptr<Card>> cards;

public:
    Hand() = default;
    Hand(const Hand& other); // Copy constructor
    Hand& operator=(const Hand& other); // Copy assignment
    Hand(Hand&& other) noexcept = default; // Move constructor
    Hand& operator=(Hand&& other) noexcept = default; // Move assignment
    ~Hand() = default;

    void addCard(std::unique_ptr<Card> card);
    std::unique_ptr<Card> removeCard(size_t index);

    void print(std::ostream& os) const;
    size_t size() const;

    // Check if we have a certain suit
    bool hasSuit(int suit) const;

    // Check if we contain the same suit/value as a certain card
    bool hasCard(const Card& c) const;

    // Accessor for cards
    const std::vector<std::unique_ptr<Card>>& getCards() const {
        return cards;
    }

    // Friend operator<<
    friend std::ostream& operator<<(std::ostream& os, const Hand& handObj);
};

#endif // HAND_H
