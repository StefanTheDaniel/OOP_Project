#include "Player.h"

Player::Player(const std::string& name) : name(name) {}

void Player::addCard(std::unique_ptr<Card> card) {
    hand.addCard(std::move(card));
}

std::unique_ptr<Card> Player::playCard(size_t index) {
    return hand.removeCard(index);
}

void Player::printHand(std::ostream& os) const {
    os << name << "'s Hand:\n";
    hand.print(os);
}

const std::string& Player::getName() const { return name; }
