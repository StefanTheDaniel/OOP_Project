// Game.cpp
#include "Game.h"
#include "Exception.h"
#include "Factory.h"
#include "Utility.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <limits>

// Free function to rank cards
int cardRank(const Card& c) {
    if (c.getSuit() == 4) { // Joker
        return (c.getValue() == 1) ? 999 : 998; // Black Joker > Red Joker
    }
    return c.getValue(); // Standard cards based on value
}

// Helper function to convert a card to string
std::string Game::cardToString(const Card& card) {
    if (card.getSuit() == 4) { // Joker
        return (card.getValue() == 1 ? "Black Joker" : "Red Joker");
    }
    // Assuming suits: 0-Hearts, 1-Spades, 2-Diamonds, 3-Clubs
    static const std::string suits[] = {"Hearts", "Spades", "Diamonds", "Clubs", "Joker"};
    static const std::string values[] = {"", "Ace", "2", "3", "4", "5", "6", "7",
                                        "8", "9", "10", "Jack", "Queen", "King"};

    std::string cardStr;
    if (card.getValue() >=1 && card.getValue() <=13 && card.getSuit() >=0 && card.getSuit() <=3) {
        cardStr = values[card.getValue()] + " of " + suits[card.getSuit()];
    } else {
        cardStr = "Unknown Card";
    }
    return cardStr;
}

Game::Game() {
    // Initialize players
    players.emplace_back("Player 1");
    players.emplace_back("Player 2");
    players.emplace_back("Player 3");
    players.emplace_back("Player 4");

    // Shuffle deck and deal 13 cards to each player
    deck.shuffle();
    for (auto& player : players) {
        for (int i = 0; i < 13; ++i) {
            player.addCard(deck.draw());
        }
        scores[player.getName()] = 0; // Initialize scores
    }
}

Game::Game(const Game& other)
    : deck(other.deck),
      players(other.players),
      commonerPile(other.commonerPile),
      royaltyPile(other.royaltyPile),
      roundCount(other.roundCount),
      scores(other.scores),
      commonerSum(other.commonerSum),
      currentRoyaltyOwner(other.currentRoyaltyOwner),
      lastCommonerPlayerIndex(other.lastCommonerPlayerIndex),
      highestRoyaltyPlayerIndex(other.highestRoyaltyPlayerIndex),
      highestRoyaltyValue(other.highestRoyaltyValue),
      highestCommonerValue(other.highestCommonerValue),
      highestCommonerPlayerIndex(other.highestCommonerPlayerIndex),
      playedCards(other.playedCards)
{}

Game& Game::operator=(const Game& other) {
    if (this == &other) return *this;
    deck = other.deck;
    players = other.players;
    commonerPile = other.commonerPile;
    royaltyPile = other.royaltyPile;
    roundCount = other.roundCount;
    scores = other.scores;
    commonerSum = other.commonerSum;
    currentRoyaltyOwner = other.currentRoyaltyOwner;
    lastCommonerPlayerIndex = other.lastCommonerPlayerIndex;
    highestRoyaltyPlayerIndex = other.highestRoyaltyPlayerIndex;
    highestRoyaltyValue = other.highestRoyaltyValue;
    highestCommonerValue = other.highestCommonerValue;
    highestCommonerPlayerIndex = other.highestCommonerPlayerIndex;
    playedCards = other.playedCards;
    return *this;
}

void Game::resetPiles() {
    commonerPile.clear();
    royaltyPile.clear();
    commonerSum = 0;
    currentRoyaltyOwner = -1;
    playedCards.clear();
    lastCommonerPlayerIndex = -1;
    highestRoyaltyPlayerIndex = -1;
    highestRoyaltyValue = -1;
    highestCommonerValue = -1;
    highestCommonerPlayerIndex = -1;
}

bool Game::allPlayersEmpty() const {
    for (const auto& player : players) {
        if (player.handSize() > 0) {
            return false;
        }
    }
    return true;
}

void Game::printGameState() const {
    std::cout << "\n--- GAME STATE ---\n";
    std::cout << "Round: " << roundCount << "\n";
    std::cout << "Commoner Sum: " << commonerSum << "\n";

    if (commonerPile.isEmpty()) {
        std::cout << "Commoner Pile: Empty\n";
    } else {
        std::cout << "Commoner Pile:\n";
        PrintContainer(commonerPile.getCards(), std::cout); // Use PrintContainer
    }

    if (royaltyPile.isEmpty()) {
        std::cout << "Royalty Pile: Empty\n";
    } else {
        std::cout << "Royalty Pile:\n";
        PrintContainer(royaltyPile.getCards(), std::cout); // Use PrintContainer
    }
    std::cout << "------------------\n";
}

void Game::printScoreboard() const {
    std::cout << "\n--- SCOREBOARD ---\n";
    for (const auto& [name, score] : scores) {
        std::cout << name << ": " << score << "\n";
    }
    std::cout << "------------------\n";
}

bool Game::checkForWinner() const {
    // Since the game only has one round, this function will be used to check if a winner exists
    // A winner exists if at least one player has a positive score
    for (const auto& [name, score] : scores) {
        if (score > 0) {
            return true;
        }
    }
    return false;
}

int Game::determineRoundWinner() const {
    if (!royaltyPile.isEmpty()) {
        // Top royalty card exists
        const Card* topRoyal = royaltyPile.topCard();
        if (!topRoyal) {
            return -1; // Safety check
        }

        // Handle Jokers
        if (topRoyal->getSuit() == 4) { // Joker
            if (topRoyal->getValue() == 1) {
                // Black Joker beats everything; sum cannot win
                return highestRoyaltyPlayerIndex;
            } else {
                // Red Joker beats everything except the Black Joker; sum cannot win
                return highestRoyaltyPlayerIndex;
            }
        }

        // Compare sum with the top royalty card's value
        if (commonerSum >= topRoyal->getValue()) {
            // Sum wins
            return lastCommonerPlayerIndex;
        }

        // If sum doesn't win, the owner of the top royalty card wins
        return highestRoyaltyPlayerIndex;
    }
    else {
        // Royalty Pile is empty; determine based on highest commoner card
        if (highestCommonerPlayerIndex != -1) {
            return highestCommonerPlayerIndex;
        }
        else {
            return -1; // No winner
        }
    }
}

void Game::playRound() {
    roundCount = 1;
    resetPiles(); // Ensure piles are clear before the round

    for (size_t i = 0; i < players.size(); ++i) {
        Player& player = players[i];

        if (player.handSize() == 0) {
            std::cout << "\n" << player.getName() << " has no cards left and skips the turn.\n";
            continue; // Skip if player has no cards
        }

        std::cout << "\n" << player.getName() << "'s turn.\n";
        PrintContainer(player.getHand().getCards(), std::cout); // Use PrintContainer
        printGameState();

        size_t cardIndex;
        std::cout << "Choose a card to play (index): ";

        // Enhanced Input Validation
        while (!(std::cin >> cardIndex)) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a valid card index: ";
        }

        // Validate input
        if (cardIndex >= static_cast<size_t>(player.handSize())) {
            std::cout << "Invalid index. Skipping your turn...\n";
            continue;
        }

        // Play the card
        std::unique_ptr<Card> playedCard;
        try {
            playedCard = player.playCard(cardIndex);
        }
        catch (const std::exception& e) {
            std::cout << "Error playing card: " << e.what() << "\nSkipping turn...\n";
            continue;
        }

        int val = playedCard->getValue();
        int s = playedCard->getSuit(); // Suits are handled accordingly

        // Track the played card
        playedCards.push_back(PlayedCard{ playedCard.get(), static_cast<int>(i) });

        // Royalty cards (Jack, Queen, King, Jokers)
        if (val >= 11 || s == 4) {
            // Add to royalty pile
            royaltyPile.addCard(std::move(playedCard));

            // Update highest royalty card tracking
            int currentCardRank = cardRank(*royaltyPile.topCard());
            if (currentCardRank > highestRoyaltyValue) {
                highestRoyaltyValue = currentCardRank;
                highestRoyaltyPlayerIndex = static_cast<int>(i);
            }

            std::cout << players[i].getName() << " plays " << cardToString(*royaltyPile.topCard()) << " to the Royalty Pile.\n";
        }
        else {
            // Commoner card
            commonerPile.addCard(std::move(playedCard));
            commonerSum += val;
            lastCommonerPlayerIndex = static_cast<int>(i);
            std::cout << "Added " << cardToString(*commonerPile.topCard()) << " to Commoner Pile. Current Sum: " << commonerSum << "\n";

            // Check and update highest commoner card
            if (val > highestCommonerValue) {
                highestCommonerValue = val;
                highestCommonerPlayerIndex = static_cast<int>(i);
            }

            // Reset sum if it surpasses 13
            if (commonerSum > 13) {
                std::cout << "Commoner Sum exceeded 13. Resetting sum to 0.\n";
                commonerSum = 0;
            }
        }
    }
}

void Game::run() {
    try {
        // Play only one round
        playRound();

        // Determine the winner based on the top royalty card and sum
        int winnerIndex = determineRoundWinner();

        if (winnerIndex == -1) {
            // No winner
            std::cout << "\nNo winner for this round. The game ends in a draw.\n";
        }
        else if (winnerIndex == lastCommonerPlayerIndex) {
            // Sum wins
            std::cout << "\nCommoner Sum (" << commonerSum << ") is higher or equal to the top Royalty card.\n";
            std::cout << "Commoners win the game!\n";
        }
        else if (winnerIndex >=0 && winnerIndex < static_cast<int>(players.size())) {
            // Royalty card wins
            std::cout << "\n" << players[winnerIndex].getName() << " wins the game with the Royalty card: "
                      << cardToString(*royaltyPile.topCard()) << "!\n";
            scores[players[winnerIndex].getName()] += 1;
        }
        else {
            // Safety catch-all
            std::cout << "\nAn unexpected condition occurred. No winner determined.\n";
        }

        printScoreboard();
        std::cout << "\nGame has ended.\n";
    }
    catch (const GameException& e) {
        std::cerr << "GameException: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Standard exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown exception occurred." << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Game& gameObj) {
    os << "--- GAME STATE ---\n";
    os << "Round: " << gameObj.roundCount << "\n";
    os << "Commoner Sum: " << gameObj.commonerSum << "\n";
    os << "Commoner Pile:\n";
    if (gameObj.commonerPile.isEmpty()) {
        os << "Empty\n";
    } else {
        PrintContainer(gameObj.commonerPile.getCards(), os); // Use PrintContainer
    }
    os << "Royalty Pile:\n";
    if (gameObj.royaltyPile.isEmpty()) {
        os << "Empty\n";
    } else {
        PrintContainer(gameObj.royaltyPile.getCards(), os); // Use PrintContainer
    }
    os << "------------------\n";
    return os;
}
