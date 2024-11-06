#include <algorithm> //for engine
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

class Card
{
    int suit;
    int value;
public:
    Card(int suit, int value) : suit(suit), value(value) {}

    void print() const
    {
        if (suit == 4) //for the jokers
        {
            std::cout<<(value == 1 ? "Black Joker" : "Red Joker")<<std::endl;
        }
        else //for the royal cards, ace is treated as value=1
        {
            std::string SpecialValue;
            switch(value)
            {
            case 1:SpecialValue="Ace"; break;
            case 11:SpecialValue="Jack"; break;
            case 12:SpecialValue="Queen"; break;
            case 13:SpecialValue="King"; break;
            default:SpecialValue=std::to_string(value); break;
            }
            std::string suitString;
            switch (suit)
            {
            case 0: suitString = "Hearts";break;
            case 1: suitString = "Spades";break;
            case 2: suitString = "Diamonds";break;
            case 3: suitString = "Clubs";break;
            default: suitString = "Other Suit"; break;
            }
            std::cout << SpecialValue<<" of "<<suitString<<std::endl;
        }
    }
    int getValue() const{return value;}
    int getSuit() const{return suit;}
};

class Hand
{
    std::vector<Card> cards;
    public:
    void addCard(const Card& card)
    {
        cards.push_back(card);
    }
    void removeCard(const Card& card)
    {
        for(auto i=cards.begin(); i!=cards.end(); i++)
        {
            if(i->getSuit()==card.getSuit() && i->getValue()==card.getValue())
            {
                cards.erase(i);
                break;
            }
        }
    }
    void printCards() const
    {
        for(const auto& card : cards)
        {
            card.print();
        }
    }
    int getHandSize() const
    {
        return cards.size();
    }
};

class Deck
{
    std::vector<Card> cards;
public:
    Deck()
    {
        for(int suit=0;suit<4;suit++)
        {
            for(int value=1; value<=13; value++)
            {
                cards.push_back(Card(suit, value));
            }
        }
        cards.push_back(Card(4, 1)); // Black Joker
        cards.push_back(Card(4, 2)); // Red Joker
    }

    void printDeck() const
    {
        for (const auto& card : cards)
            card.print();
    }

    std::vector<Card> getDeck() const
    {
        return cards;
    }
};

class Player
{
    std::string name;
    int score;
    Hand hand; //o mana pt jucator
public:
    Player(const std::string name) : name(name), score(0) {}

    void addCardHand(const Card& card)
    {
        hand.addCard(card);
    }
    void removeCardHand(const Card& card)
    {
        hand.removeCard(card);
    }
    void printHand() const
    {
        std::cout<<"Hand of "<<name<<std::endl;
        hand.printCards();
    }
    void addScore(int score)
    {
        score += score;
    }
    int getScore() const
    {
        return score;
    }
    const std::string getName() const
    {
        return name;
    }
};

class Shuffle
{
    std::vector<Card> deck;
    public:
    Shuffle(const Deck& d)
    {
        deck=d.getDeck();
    }
    void shuffle()
    {
        std::random_device rd;//random number generator
        std::mt19937 g(rd());//mersenne twister engine
        std::shuffle(deck.begin(), deck.end(),g);
    }

    void dealCards(Player &player1, Player &player2, Player &player3, Player &player4)
    {
        int i = 0;
        while (i < 52) // Deal 13 cards to each player, total of 52 cards in a standard deck
        {
            if (i < 13) {
                player1.addCardHand(deck[i]);
            } else if (i < 26) {
                player2.addCardHand(deck[i]);
            } else if (i < 39) {
                player3.addCardHand(deck[i]);
            } else {
                player4.addCardHand(deck[i]);
            }
            i++;
        }
    }
};



int main()
{
    Deck D1;

    Shuffle shuffle(D1);
    shuffle.shuffle();

    Player player1("Player 1");
    Player player2("Player 2");
    Player player3("Player 3");
    Player player4("Player 4");

    shuffle.dealCards(player1, player2, player3, player4);

    player1.printHand();
    player2.printHand();
    player3.printHand();
    player4.printHand();

    return 0;
}