#pragma once

//#include "Action.hpp"
//#include "Player.hpp"

class Coup: public Action
{
private:
    Action* target;

protected:

public:
    Coup(Player* caster);

    void resolve();

};
