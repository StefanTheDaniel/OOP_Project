#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <random>

class GameException : public std::exception {
protected:
    std::string message;
public:
    explicit GameException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class InvalidCardException : public GameException {
public:
    InvalidCardException() : GameException("Card invalid selectat!") {}
};

class InvalidPlayerException : public GameException {
public:
    InvalidPlayerException() : GameException("Jucător invalid!") {}
};

class EmptyDeckException : public GameException {
public:
    EmptyDeckException() : GameException("Nu mai sunt cărți în pachet!") {}
};

class Card {
protected:
    int suit;  // 0 = Hearts, 1 = Spades, 2 = Diamonds, 3 = Clubs, 4 = Joker
    int value; // 1-13 pentru cărți standard, 1 sau 2 pentru jokers
public:
    Card(int suit, int value) : suit(suit), value(value) {}
    virtual ~Card() = default;
    virtual void print(std::ostream& os) const = 0;
    virtual Card* clone() const = 0;

    int getValue() const { return value; }
    int getSuit() const { return suit; }
    friend std::ostream& operator<<(std::ostream& os, const Card& card) {
        card.print(os);
        return os;
    }
};

class StandardCard : public Card {
public:
    StandardCard(int suit, int value) : Card(suit, value) {}
    void print(std::ostream& os) const override {
        std::string valueString;
        switch (value) {
            case 1: valueString = "Ace"; break;
            case 11: valueString = "Jack"; break;
            case 12: valueString = "Queen"; break;
            case 13: valueString = "King"; break;
            default: valueString = std::to_string(value); break;
        }
        std::string suitString;
        switch (suit) {
            case 0: suitString = "Hearts"; break;
            case 1: suitString = "Spades"; break;
            case 2: suitString = "Diamonds"; break;
            case 3: suitString = "Clubs"; break;
        }
        os << valueString << " of " << suitString;
    }
    Card* clone() const override { return new StandardCard(*this); }
};

class JokerCard : public Card {
public:
    JokerCard(int value) : Card(4, value) {}
    void print(std::ostream& os) const override {
        os << (value == 1 ? "Black Joker" : "Red Joker");
    }
    Card* clone() const override { return new JokerCard(*this); }
};

class Deck {
    std::vector<std::unique_ptr<Card>> cards;
public:
    Deck() {
        for (int suit = 0; suit < 4; ++suit) {
            for (int value = 1; value <= 13; ++value) {
                cards.push_back(std::make_unique<StandardCard>(suit, value));
            }
        }
        cards.push_back(std::make_unique<JokerCard>(1)); // Black Joker
        cards.push_back(std::make_unique<JokerCard>(2)); // Red Joker
    }
    void shuffle() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }
    std::unique_ptr<Card> draw() {
        if (cards.empty()) throw EmptyDeckException();
        auto card = std::move(cards.back());
        cards.pop_back();
        return card;
    }
};

class Hand {
    std::vector<std::unique_ptr<Card>> cards;
public:
    void addCard(std::unique_ptr<Card> card) {
        cards.push_back(std::move(card));
    }
    std::unique_ptr<Card> removeCard(size_t index) {
        if (index >= cards.size()) throw InvalidCardException();
        auto card = std::move(cards[index]);
        cards.erase(cards.begin() + index);
        return card;
    }
    void print(std::ostream& os) const {
        for (size_t i = 0; i < cards.size(); ++i) {
            os << i << ": " << *cards[i] << std::endl;
        }
    }
    size_t size() const { return cards.size(); }
};

class Player {
    std::string name;
    Hand hand;
public:
    explicit Player(const std::string& name) : name(name) {}
    void addCard(std::unique_ptr<Card> card) {
        hand.addCard(std::move(card));
    }
    std::unique_ptr<Card> playCard(size_t index) {
        return hand.removeCard(index);
    }
    void printHand(std::ostream& os) const {
        os << name << "'s Hand:\n";
        hand.print(os);
    }
    const std::string& getName() const { return name; }
};

class Pile {
    std::vector<std::unique_ptr<Card>> pile;
public:
    void addCard(std::unique_ptr<Card> card) {
        pile.push_back(std::move(card));
    }
    void print(std::ostream& os, const std::string& name) const {
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
};

class Game {
    Deck deck;
    std::vector<Player> players;
    Pile commonerPile;
    Pile royaltyPile;
    int currentSuit = -1; // No suit selected initially

    static std::string suitToString(int suit) {
        switch (suit) {
            case 0: return "Hearts";
            case 1: return "Spades";
            case 2: return "Diamonds";
            case 3: return "Clubs";
            default: return "Unknown";
        }
    }

public:
    Game() {
        players.emplace_back("Player 1");
        players.emplace_back("Player 2");
        players.emplace_back("Player 3");
        players.emplace_back("Player 4");
        deck.shuffle();

        // Deal 13 cards to each player
        for (auto& player : players) {
            for (int i = 0; i < 13; ++i) {
                player.addCard(deck.draw());
            }
        }
    }

    void printGameState() const {
        std::cout << "Current Suit: "
                  << (currentSuit == -1 ? "None" : suitToString(currentSuit))
                  << "\n";

        std::cout << "Commoner Pile:\n";
        commonerPile.print(std::cout, "Commoner Pile");

        std::cout << "Royalty Pile:\n";
        royaltyPile.print(std::cout, "Royalty Pile");
    }


    void playRound() {
        bool isFirstCardPlayed = false; // Track if it's the first card of the round

        for (auto& player : players) {
            std::cout << player.getName() << "'s turn.\n";
            player.printHand(std::cout);
            printGameState();

            size_t cardIndex;
            std::cout << "Choose a card to play: ";
            std::cin >> cardIndex;

            auto card = player.playCard(cardIndex);

            if (card == nullptr) {
                std::cerr << "Invalid card choice. Skipping turn.\n";
                continue;
            }

            // Check if the card is a Royalty or Commoner and update piles
            if (card->getValue() >= 11 || card->getSuit() == 4) { // Royalty or Joker
                royaltyPile.addCard(std::move(card));
            } else { // Commoner
                // Update the current suit only on the first player's card
                if (!isFirstCardPlayed) {
                    currentSuit = card->getSuit();
                    isFirstCardPlayed = true;
                }
                commonerPile.addCard(std::move(card));
            }

            printGameState(); // Show game state after each player's turn
        }

        // Reset the current suit for the next round
        currentSuit = -1;
    }

    void run() {
        while (true) {
            playRound();
        }
    }
};

int main() {
    try {
        Game game;
        game.run();
    } catch (const GameException& e) {
        std::cerr << "Game Error: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Unknown Error: " << e.what() << "\n";
    }

    return 0;
}
