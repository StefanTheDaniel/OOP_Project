// Deck.cpp
#include "Deck.h"
#include "Exception.h"
#include "Factory.h" // Include Factory
#include "Utility.h"
#include <algorithm>
#include <random>
#include <stdexcept>
#include <iostream>

Deck::Deck() {
    // Instantiate Factory objects
    Factory<Card, StandardCard> standardCardFactory;
    Factory<Card, JokerCard> jokerCardFactory;

    // Initialize deck with StandardCards
    for (int s = 0; s < 4; ++s) { // Suits 0-3
        for (int v = 1; v <= 13; ++v) { // Values 1-13
            cards.emplace_back(standardCardFactory.create(s, v));
        }
    }
    // Add Jokers
    cards.emplace_back(jokerCardFactory.create(1)); // Black Joker
    cards.emplace_back(jokerCardFactory.create(2)); // Red Joker
}

Deck::Deck(const Deck& other) {
    cards.reserve(other.cards.size());
    for (const auto& card : other.cards) {
        cards.emplace_back(std::unique_ptr<Card>(card->clone()));
    }
}

Deck& Deck::operator=(const Deck& other) {
    if (this == &other) return *this;
    cards.clear();
    cards.reserve(other.cards.size());
    for (const auto& card : other.cards) {
        cards.emplace_back(std::unique_ptr<Card>(card->clone()));
    }
    return *this;
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

std::unique_ptr<Card> Deck::draw() {
    if (cards.empty()) {
        throw DeckEmptyException();
    }
    auto top = std::move(cards.back());
    cards.pop_back();
    return top;
}

std::ostream& operator<<(std::ostream& os, const Deck& deckObj) {
    os << "Deck contains:\n";
    PrintContainer(deckObj.cards, os); // Use PrintContainer
    return os;
}
