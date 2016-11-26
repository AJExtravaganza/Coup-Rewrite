#pragma once

//#include "Action.hpp"
//#include "Player.hpp"

class Tax: public Action
{
private:

protected:

public:
    Tax(Player* caster);

    void challenge();
    void resolve();

};

