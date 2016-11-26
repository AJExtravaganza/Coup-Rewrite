#pragma once

//#include "Action.hpp"
//#include "Player.hpp"

class ForeignAid: public Action
{
private:

protected:

public:
    ForeignAid(Player* caster);

    void block();
    void resolve();

};
