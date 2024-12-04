#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <vector>
#include <memory>

class Hand {
    std::vector<std::unique_ptr<Card>> cards;
public:
    void addCard(std::unique_ptr<Card> card);
    std::unique_ptr<Card> removeCard(size_t index);
    void print(std::ostream& os) const;
    size_t size() const;
};

#endif
