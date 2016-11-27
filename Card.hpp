#pragma once

#include "enums.h"

#include <string>

class Card
{
private:
    Role role;
    std::string name;
    bool exposed;
public:
    std::string getName();
    bool is(Role _role);
    bool isExposed();
    void expose();

    Card();
    Card(Role card);
};
