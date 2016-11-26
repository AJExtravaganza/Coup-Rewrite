#pragma once

//#include "Action.hpp"
//#include "Player.hpp"

class Steal: public Action
{
private:
    Player* target;

protected:

public:
    Assassinate(Player* caster);

    void acquireTarget();
    void challenge();
    void block();
    void resolve();

};
