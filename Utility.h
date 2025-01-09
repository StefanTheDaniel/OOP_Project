// Utility.h
#ifndef UTILITY_H
#define UTILITY_H

#include "Card.h"
#include <iostream>
#include <vector>
#include <memory>

// Function template to print any container of Cards
template <typename Container>
void PrintContainer(const Container& container, std::ostream& os) {
    for (const auto& card : container) {
        if (card) {
            os << *card << ", ";
        }
    }
    os << "\n";
}

#endif // UTILITY_H
