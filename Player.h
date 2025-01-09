// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"
#include <string>
#include <iostream>

class Player {
    std::string name;
    Hand hand;

public:
    explicit Player(const std::string& name);
    Player(const Player& other); // Copy constructor
    Player& operator=(const Player& other); // Copy assignment
    Player(Player&& other) noexcept = default; // Move constructor
    Player& operator=(Player&& other) noexcept = default; // Move assignment
    ~Player() = default;

    void addCard(std::unique_ptr<Card> card);
    std::unique_ptr<Card> playCard(size_t index);
    void printHand(std::ostream& os) const;

    const std::string& getName() const;
    size_t handSize() const;

    bool hasSuit(int suit) const;
    bool hasCard(const Card& c) const;

    // Accessor for hand
    const Hand& getHand() const {
        return hand;
    }

    // Friend operator<<
    friend std::ostream& operator<<(std::ostream& os, const Player& playerObj);
};

#endif // PLAYER_H
