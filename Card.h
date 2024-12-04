#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <memory>

class Card {
protected:
    int suit;
    int value;
public:
    Card(int suit, int value);
    virtual ~Card() = default;
    virtual void print(std::ostream& os) const = 0;
    virtual Card* clone() const = 0;

    int getValue() const;
    int getSuit() const;

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
    JokerCard(int value);
    void print(std::ostream& os) const override;
    Card* clone() const override;
};

#endif
