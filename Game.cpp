#include "Game.h"
#include <iostream>
#include <stdexcept>

Game::Game() {
    players.emplace_back("Player 1");
    players.emplace_back("Player 2");
    players.emplace_back("Player 3");
    players.emplace_back("Player 4");
    deck.shuffle();

    for (auto& player : players) {
        for (int i = 0; i < 13; ++i) {
            player.addCard(deck.draw());
        }
    }
}

std::string Game::suitToString(int suit) {
    switch (suit) {
        case 0: return "Hearts";
        case 1: return "Spades";
        case 2: return "Diamonds";
        case 3: return "Clubs";
        default: return "Unknown";
    }
}

void Game::printGameState() const {
    std::cout << "Current Suit: "
              << (currentSuit == -1 ? "None" : suitToString(currentSuit))
              << "\n";

    commonerPile.print(std::cout, "Commoner Pile");
    royaltyPile.print(std::cout, "Royalty Pile");
}

void Game::playRound() {
    bool isFirstCardPlayed = false;

    for (auto& player : players) {
        std::cout << player.getName() << "'s turn.\n";
        player.printHand(std::cout);
        printGameState();

        size_t cardIndex;
        std::cout << "Choose a card to play: ";
        std::cin >> cardIndex;

        auto card = player.playCard(cardIndex);

        if (card->getValue() >= 11 || card->getSuit() == 4) {
            royaltyPile.addCard(std::move(card));
        } else {
            if (!isFirstCardPlayed) {
                currentSuit = card->getSuit();
                isFirstCardPlayed = true;
            }
            commonerPile.addCard(std::move(card));
        }
        printGameState();
    }
    currentSuit = -1;
}

void Game::run() {
    while (true) {
        playRound();
    }
}