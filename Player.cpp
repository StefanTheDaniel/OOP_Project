// Player.cpp
#include "Player.h"
#include "Exception.h"
#include "Utility.h" // For PrintContainer
#include <stdexcept>
#include <iostream>

// Constructor
Player::Player(const std::string& name) : name(name) {}

// Copy constructor
Player::Player(const Player& other) : name(other.name), hand(other.hand) {}

// Copy assignment operator
Player& Player::operator=(const Player& other) {
    if (this == &other) return *this;
    name = other.name;
    hand = other.hand;
    return *this;
}

void Player::addCard(std::unique_ptr<Card> card) {
    hand.addCard(std::move(card));
}

std::unique_ptr<Card> Player::playCard(size_t index) {
    return hand.removeCard(index);
}

void Player::printHand(std::ostream& os) const {
    PrintContainer(hand.getCards(), os); // Use PrintContainer
}

const std::string& Player::getName() const {
    return name;
}

size_t Player::handSize() const {
    return hand.size();
}

bool Player::hasSuit(int suit) const {
    return hand.hasSuit(suit);
}

bool Player::hasCard(const Card& c) const {
    return hand.hasCard(c);
}

std::ostream& operator<<(std::ostream& os, const Player& playerObj) {
    playerObj.printHand(os);
    return os;
}
