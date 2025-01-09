// Pile.cpp
#include "Pile.h"
#include "Exception.h"
#include "Utility.h" // For PrintContainer
#include <iostream>

void Pile::addCard(std::unique_ptr<Card> card) {
    pile.push_back(std::move(card));
}

void Pile::print(std::ostream& os, const std::string& name) const {
    os << name << ": ";
    if (pile.empty()) {
        os << "Empty\n";
    } else {
        PrintContainer(pile, os); // Use PrintContainer
    }
}

void Pile::clear() {
    pile.clear();
}

bool Pile::isEmpty() const {
    return pile.empty();
}

const Card* Pile::topCard() const {
    if (pile.empty()) return nullptr;
    return pile.back().get();
}

Pile::Pile(const Pile& other) {
    pile.reserve(other.pile.size());
    for (const auto& card : other.pile) {
        pile.emplace_back(std::unique_ptr<Card>(card->clone()));
    }
}

Pile& Pile::operator=(const Pile& other) {
    if (this == &other) return *this;
    pile.clear();
    pile.reserve(other.pile.size());
    for (const auto& card : other.pile) {
        pile.emplace_back(std::unique_ptr<Card>(card->clone()));
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Pile& pileObj) {
    pileObj.print(os, "");
    return os;
}
