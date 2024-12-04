#ifndef PILE_H
#define PILE_H

#include "Card.h"
#include <vector>
#include <memory>

class Pile {
    std::vector<std::unique_ptr<Card>> pile;
public:
    void addCard(std::unique_ptr<Card> card);
    void print(std::ostream& os, const std::string& name) const;
};

#endif
