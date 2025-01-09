// Game.h
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Deck.h"
#include "Pile.h"
#include "Card.h"
#include "Exception.h"
#include "Factory.h"
#include "Utility.h"
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

// Struct to track each played card and its owner
struct PlayedCard {
    const Card* card;   // Pointer to the card (owned by Pile)
    int playerIndex;    // Index of the player who played the card
};

// Forward declaration of the cardRank function
int cardRank(const Card& c);

// Game class
class Game {
private:
    Deck deck;
    std::vector<Player> players;

    Pile commonerPile;
    Pile royaltyPile;

    int roundCount = 0;                // Number of rounds played (will be 1)
    std::map<std::string, int> scores;  // Scoreboard: playerName -> score

    int commonerSum = 0;               // Sum of values in the commoner pile
    int currentRoyaltyOwner = -1;      // Index of the player who owns the top royalty card

    // Tracking variables
    int lastCommonerPlayerIndex = -1;    // Last player to add to the commoner pile before sum reset
    int highestRoyaltyPlayerIndex = -1;  // Player who played the highest royalty card
    int highestRoyaltyValue = -1;        // Value of the highest royalty card

    int highestCommonerValue = -1;        // Value of the highest commoner card
    int highestCommonerPlayerIndex = -1;  // Player who played the highest commoner card

    // To track all played cards in the current round
    std::vector<PlayedCard> playedCards;

    // Helper functions
    static std::string cardToString(const Card& card);
    void printScoreboard() const;
    bool checkForWinner() const;
    bool allPlayersEmpty() const;

    void resetPiles();

    // Determines the winner of the current round
    int determineRoundWinner() const;

public:
    Game();
    Game(const Game& other); // Copy constructor
    Game& operator=(const Game& other); // Copy assignment
    Game(Game&& other) noexcept = default; // Move constructor
    Game& operator=(Game&& other) noexcept = default; // Move assignment
    ~Game() = default;

    void printGameState() const;
    void playRound();
    void run();

    // Friend operator<<
    friend std::ostream& operator<<(std::ostream& os, const Game& gameObj);
};

#endif // GAME_H
