// Deck.h
#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "Exception.h"
#include "Factory.h"
#include <vector>
#include <memory>
#include <iostream>

class Deck {
    std::vector<std::unique_ptr<Card>> cards;

public:
    Deck();
    Deck(const Deck& other); // Copy constructor
    Deck& operator=(const Deck& other); // Copy assignment
    Deck(Deck&& other) noexcept = default; // Move constructor
    Deck& operator=(Deck&& other) noexcept = default; // Move assignment
    ~Deck() = default;

    void shuffle();
    std::unique_ptr<Card> draw();

    // Friend operator<<
    friend std::ostream& operator<<(std::ostream& os, const Deck& deck);
};

#endif // DECK_H
