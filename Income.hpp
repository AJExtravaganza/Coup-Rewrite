#pragma once

//#include "Action.hpp"
//#include "Player.hpp"

class Income: public Action
{
private:

protected:

public:
    Income(Player* caster);

    void resolve();

};
