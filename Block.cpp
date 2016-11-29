#include "Block.hpp"

Block::Block(Player* _caster, std::vector<Player>& availablePlayers, Action* _targetAction): Action(_caster), targetAction(_targetAction)
{
    switch(targetAction->getActionID())
    {
    case FOREIGN_AID:
        isBluff = !(caster->hasInfluenceOver(DUKE));
        break;
    case STEAL:
        isBluff = !(caster->hasInfluenceOver(CAPTAIN) || caster->hasInfluenceOver(AMBASSADOR));
        break;
    case ASSASSINATE:
        isBluff = !(caster->hasInfluenceOver(CONTESSA));
        break;
    default:
        //throw exception
        break;
    }

    checkForChallenge(availablePlayers);

    if (status == VALID && caster->hasUnexposedCards())
    {
        resolve();
    }
}

Block::Block(const Block& other): Action(other), targetAction(other.targetAction) //N.B This is how to correctly call a base-class constructor in a derived-class constructor.
{

}


Block& Block::operator=(const Block& other)
{
    Action::operator=(other); //N.B This is how to correctly call the base-class assignment operator in a derived-class assignment operator.
    targetAction = other.targetAction;

    return *this;
}

Block::~Block()
{

}

void Block::checkForChallenge(std::vector<Player>& availablePlayers)
{
    Player * challenger = nullptr;

    for (int targetPlayer = 0; targetPlayer < availablePlayers.size()  && !challenger; targetPlayer++)
    {
        if (&availablePlayers[targetPlayer] != caster)
        {
            challenger = offerChallenge(&availablePlayers[targetPlayer]);
        }
    }

    if (challenger)
    {
        challenge(challenger);
}
    }

Player* Block::offerChallenge(Player* prospectiveChallenger)
{
    *prospectiveChallenger->uiOut << prospectiveChallenger->getName() << ", would you like to challenge " << caster->getName() << "'s claim to the ";
    bool willChallenge = false;

    switch(targetAction->getActionID())
    {
    case FOREIGN_AID:
        *globalComms << "Duke? ";
        break;
    case STEAL:
        *globalComms << "Captain/Ambassador? ";
        break;
    case ASSASSINATE:
        *globalComms << "Contessa? ";
        break;
    default:
        //throw exception
        break;
    }

    willChallenge = getSelection(*prospectiveChallenger->uiIn, *prospectiveChallenger->uiOut);

    return (willChallenge ? prospectiveChallenger : nullptr);
}

void Block::challenge(Player* challenger)
{
    *globalComms << challenger->getName() << " challenges " << caster->getName() << "'s claim to the ";

        switch(targetAction->getActionID())
        {
        case FOREIGN_AID:
            *globalComms << "Duke!\n";
            break;
        case STEAL:
            *globalComms << "Captain/Ambassador!\n";
            break;
        case ASSASSINATE:
            *globalComms << "Contessa!\n";
            break;
        default:
            //throw exception
            break;
        }

    if (isBluff)
    {
        *globalComms << caster->getName() << " was bluffing!\n";
        caster->sacrifice();
        status = CHALLENGED;
    }
    else
    {
        *globalComms << caster->getName() << " was not bluffing!\n";
        challenger->sacrifice();
    }
}



void Block::resolve()
{
    *globalComms << caster->getName() << " successfully blocks " << targetAction->getCasterName() << "'s ";

        switch(targetAction->getActionID())
        {
        case FOREIGN_AID:
            *globalComms << "foreign aid!\n";
            break;
        case STEAL:
            *globalComms << "attempted theft!\n";
            break;
        case ASSASSINATE:
            *globalComms << "assassination attempt!\n";
            break;
        default:
            //throw exception
            break;
        }

    targetAction->block();
}
