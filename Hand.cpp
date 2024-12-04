#include "Hand.h"
#include <stdexcept>

void Hand::addCard(std::unique_ptr<Card> card) {
    cards.push_back(std::move(card));
}

std::unique_ptr<Card> Hand::removeCard(size_t index) {
    if (index >= cards.size()) throw std::out_of_range("Invalid card index!");
    auto card = std::move(cards[index]);
    cards.erase(cards.begin() + index);
    return card;
}

void Hand::print(std::ostream& os) const {
    for (size_t i = 0; i < cards.size(); ++i) {
        os << i << ": " << *cards[i] << std::endl;
    }
}

size_t Hand::size() const { return cards.size(); }
