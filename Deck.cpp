#include "Deck.h"

Deck::Deck() {
    for (int suit = 0; suit < 4; ++suit) {
        for (int value = 1; value <= 13; ++value) {
            cards.push_back(std::make_unique<StandardCard>(suit, value));
        }
    }
    cards.push_back(std::make_unique<JokerCard>(1));
    cards.push_back(std::make_unique<JokerCard>(2));
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

std::unique_ptr<Card> Deck::draw() {
    if (cards.empty()) throw std::runtime_error("No cards left in the deck!");
    auto card = std::move(cards.back());
    cards.pop_back();
    return card;
}