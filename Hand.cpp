// Hand.cpp
#include "Hand.h"
#include "Exception.h"
#include "Utility.h" // For PrintContainer
#include <stdexcept>
#include <iostream>

void Hand::addCard(std::unique_ptr<Card> card) {
    cards.push_back(std::move(card));
}

std::unique_ptr<Card> Hand::removeCard(size_t index) {
    if (index >= cards.size()) {
        throw InvalidCardException();
    }
    auto card = std::move(cards[index]);
    cards.erase(cards.begin() + index);
    return card;
}

void Hand::print(std::ostream& os) const {
    PrintContainer(cards, os); // Use PrintContainer
}

size_t Hand::size() const {
    return cards.size();
}

bool Hand::hasSuit(int suit) const {
    for (const auto& c : cards) {
        if (c->getSuit() == suit) {
            return true;
        }
    }
    return false;
}

bool Hand::hasCard(const Card& c) const {
    for (const auto& cardPtr : cards) {
        if (cardPtr->getSuit() == c.getSuit() &&
            cardPtr->getValue() == c.getValue()) {
            return true;
            }
    }
    return false;
}

Hand::Hand(const Hand& other) {
    cards.reserve(other.cards.size());
    for (const auto& card : other.cards) {
        cards.emplace_back(std::unique_ptr<Card>(card->clone()));
    }
}

Hand& Hand::operator=(const Hand& other) {
    if (this == &other) return *this;
    cards.clear();
    cards.reserve(other.cards.size());
    for (const auto& card : other.cards) {
        cards.emplace_back(std::unique_ptr<Card>(card->clone()));
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Hand& handObj) {
    handObj.print(os);
    return os;
}
