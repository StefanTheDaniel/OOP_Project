// main.cpp
#include "Game.h"
#include "Exception.h"
#include <iostream>

int main() {
    try {
        Game game;
        game.run();
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
    return 0;
}
