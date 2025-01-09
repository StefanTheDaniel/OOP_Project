// Factory.h
#ifndef FACTORY_H
#define FACTORY_H

#include "Card.h"
#include <memory>

// Factory class template with only Base and Derived as template parameters
template <typename Base, typename Derived>
class Factory {
public:
    // Member function template to create objects with perfect forwarding
    template <typename... Args>
    std::unique_ptr<Base> create(Args&&... args) {
        return std::make_unique<Derived>(std::forward<Args>(args)...);
    }
};

#endif // FACTORY_H
