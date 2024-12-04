#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <random>

class Deck {
    std::vector<std::unique_ptr<Card>> cards;
public:
    Deck();
    void shuffle();
    std::unique_ptr<Card> draw();
};

#endif