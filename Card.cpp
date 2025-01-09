// Card.cpp
#include "Card.h"

// Initialize static member
int Card::totalCardsCreated = 0;

// =====================
//       Base Card
// =====================
Card::Card(int suit, int value) : suit(suit), value(value) {
    ++totalCardsCreated;
}

int Card::getValue() const { return value; }
int Card::getSuit()  const { return suit; }

std::ostream& operator<<(std::ostream& os, const Card& card) {
    card.print(os);
    return os;
}

// =====================
//    StandardCard
// =====================
StandardCard::StandardCard(int suit, int value)
    : Card(suit, value) {}

void StandardCard::print(std::ostream& os) const {
    std::string valueStr;
    switch (value) {
        case 1:  valueStr = "Ace";   break;
        case 11: valueStr = "Jack";  break;
        case 12: valueStr = "Queen"; break;
        case 13: valueStr = "King";  break;
        default: valueStr = std::to_string(value); break;
    }
    std::string suitStr;
    switch (suit) {
        case 0: suitStr = "Hearts";   break;
        case 1: suitStr = "Spades";   break;
        case 2: suitStr = "Diamonds"; break;
        case 3: suitStr = "Clubs";    break;
        default: suitStr = "Unknown"; break;
    }
    os << valueStr << " of " << suitStr;
}

Card* StandardCard::clone() const {
    return new StandardCard(*this);
}

// =====================
//     JokerCard
// =====================
JokerCard::JokerCard(int value)
    : Card(4, value) {}

void JokerCard::print(std::ostream& os) const {
    // 1 => Black Joker, 2 => Red Joker
    os << (value == 1 ? "Black Joker" : "Red Joker");
}

Card* JokerCard::clone() const {
    return new JokerCard(*this);
}

int Card::getTotalCardsCreated() {
    return totalCardsCreated;
}
