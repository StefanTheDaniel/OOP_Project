// Pile.h
#ifndef PILE_H
#define PILE_H

#include "Card.h"
#include "Exception.h"
#include <vector>
#include <memory>
#include <iostream>

class Pile {
    std::vector<std::unique_ptr<Card>> pile;
public:
    Pile() = default;
    Pile(const Pile& other); // Copy constructor
    Pile& operator=(const Pile& other); // Copy assignment
    Pile(Pile&& other) noexcept = default; // Move constructor
    Pile& operator=(Pile&& other) noexcept = default; // Move assignment
    ~Pile() = default;

    void addCard(std::unique_ptr<Card> card);
    void print(std::ostream& os, const std::string& name) const;
    void clear();
    bool isEmpty() const;

    // The top card in the pile (or nullptr if empty)
    const Card* topCard() const;

    // Accessor for cards
    const std::vector<std::unique_ptr<Card>>& getCards() const {
        return pile;
    }

    // Friend operator<<
    friend std::ostream& operator<<(std::ostream& os, const Pile& pileObj);
};

#endif // PILE_H
