#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"
#include <string>

class Player {
    std::string name;
    Hand hand;
public:
    explicit Player(const std::string& name);
    void addCard(std::unique_ptr<Card> card);
    std::unique_ptr<Card> playCard(size_t index);
    void printHand(std::ostream& os) const;
    const std::string& getName() const;
};

#endif