#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Deck.h"
#include "Pile.h"

class Game {
    Deck deck;
    std::vector<Player> players;
    Pile commonerPile;
    Pile royaltyPile;
    int currentSuit = -1;
    static std::string suitToString(int suit);
public:
    Game();
    void printGameState() const;
    void playRound();
    void run();
};

#endif
