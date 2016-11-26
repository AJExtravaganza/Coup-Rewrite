#pragma once

//#include "Action.hpp"
//#include "Player.hpp"

class Exchange: public Action
{
private:

protected:

public:
    Assassinate(Player* caster);

    void challenge();
    void resolve();

};
