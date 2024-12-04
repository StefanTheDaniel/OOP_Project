#include "Pile.h"

void Pile::addCard(std::unique_ptr<Card> card) {
    pile.push_back(std::move(card));
}

void Pile::print(std::ostream& os, const std::string& name) const {
    os << name << ": ";
    if (pile.empty()) {
        os << "Empty\n";
    } else {
        for (const auto& card : pile) {
            os << *card << ", ";
        }
        os << "\n";
    }
}