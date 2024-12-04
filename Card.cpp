#include "Card.h"

Card::Card(int suit, int value) : suit(suit), value(value) {}

int Card::getValue() const { return value; }
int Card::getSuit() const { return suit; }

std::ostream& operator<<(std::ostream& os, const Card& card) {
    card.print(os);
    return os;
}

StandardCard::StandardCard(int suit, int value) : Card(suit, value) {}

void StandardCard::print(std::ostream& os) const {
    std::string valueString = (value == 1 ? "Ace" : value == 11 ? "Jack" : value == 12 ? "Queen" : value == 13 ? "King" : std::to_string(value));
    std::string suitString = (suit == 0 ? "Hearts" : suit == 1 ? "Spades" : suit == 2 ? "Diamonds" : "Clubs");
    os << valueString << " of " << suitString;
}

Card* StandardCard::clone() const { return new StandardCard(*this); }

JokerCard::JokerCard(int value) : Card(4, value) {}

void JokerCard::print(std::ostream& os) const {
    os << (value == 1 ? "Black Joker" : "Red Joker");
}

Card* JokerCard::clone() const { return new JokerCard(*this); }