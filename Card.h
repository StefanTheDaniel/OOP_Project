// Card.h
#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <memory>

// Base abstract Card class
class Card {
protected:
    int suit;  // 0=Hearts,1=Spades,2=Diamonds,3=Clubs,4=Joker
    int value; // 1-13 for standard, 1 or 2 for jokers, etc.

    static int totalCardsCreated;

public:
    Card(int suit, int value);
    virtual ~Card() = default;

    virtual void print(std::ostream& os) const = 0;
    virtual Card* clone() const = 0;

    int getValue() const;
    int getSuit()  const;

    // Static function to get total cards created
    static int getTotalCardsCreated();

    // Overload operator<<
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
};

class StandardCard : public Card {
public:
    StandardCard(int suit, int value);
    void print(std::ostream& os) const override;
    Card* clone() const override;
};

class JokerCard : public Card {
public:
    // value==1 => Black Joker, value==2 => Red Joker
    JokerCard(int value);
    void print(std::ostream& os) const override;
    Card* clone() const override;
};

#endif // CARD_H
